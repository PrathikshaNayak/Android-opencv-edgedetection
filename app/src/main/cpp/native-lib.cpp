#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <cmath>
#include <cstdint>

#define LOG_TAG "native-edge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

/*
 * Java signature:
 * public native Bitmap detectEdges(Bitmap inputBitmap);
 * in package com.example.assessment.MainActivity
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_assessment_MainActivity_detectEdges(JNIEnv *env, jobject /* thiz */, jobject inputBitmap) {
    if (inputBitmap == nullptr) {
        LOGE("inputBitmap == null");
        return nullptr;
    }

    AndroidBitmapInfo inInfo;
    if (AndroidBitmap_getInfo(env, inputBitmap, &inInfo) != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("Failed to get input bitmap info");
        return nullptr;
    }
    if (inInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGI("Input bitmap format is not RGBA_8888. Attempting to continue.");
    }

    // Lock input pixels
    void *inPixels = nullptr;
    if (AndroidBitmap_lockPixels(env, inputBitmap, &inPixels) != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("Failed to lock input bitmap pixels");
        return nullptr;
    }

    const int width = inInfo.width;
    const int height = inInfo.height;
    const uint32_t* src = reinterpret_cast<const uint32_t*>(inPixels);

    // Create output Bitmap by calling Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
    jclass bitmapClass = env->FindClass("android/graphics/Bitmap");
    if (!bitmapClass) {
        LOGE("Could not find Bitmap class");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    jmethodID createBitmapMethod = env->GetStaticMethodID(
            bitmapClass,
            "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;"
    );
    if (!createBitmapMethod) {
        LOGE("Could not find createBitmap method");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    // Get Bitmap.Config.ARGB_8888
    jclass configClass = env->FindClass("android/graphics/Bitmap$Config");
    if (!configClass) {
        LOGE("Could not find Bitmap$Config class");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    jmethodID valueOfMethod = env->GetStaticMethodID(
            configClass,
            "valueOf",
            "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;"
    );
    if (!valueOfMethod) {
        LOGE("Could not find Bitmap.Config.valueOf");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    jstring argbName = env->NewStringUTF("ARGB_8888");
    jobject configObj = env->CallStaticObjectMethod(configClass, valueOfMethod, argbName);
    env->DeleteLocalRef(argbName);

    jobject outBitmap = env->CallStaticObjectMethod(bitmapClass, createBitmapMethod, width, height, configObj);
    if (!outBitmap) {
        LOGE("Failed to create output bitmap");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    // Lock output pixels
    void *outPixels = nullptr;
    if (AndroidBitmap_lockPixels(env, outBitmap, &outPixels) != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("Failed to lock output bitmap pixels");
        AndroidBitmap_unlockPixels(env, inputBitmap);
        return nullptr;
    }

    uint32_t* dst = reinterpret_cast<uint32_t*>(outPixels);

    // Simple edge detection (Sobel-like via neighbor difference)
    // Convert to grayscale then compute gradient magnitude using neighbors.
    // We'll use a simple kernel: gx = right - left; gy = bottom - top;
    // magnitude = sqrt(gx*gx + gy*gy); threshold to produce binary edges.

    auto get_gray = [&](int x, int y)->int {
        if (x < 0) x = 0;
        if (x >= width) x = width - 1;
        if (y < 0) y = 0;
        if (y >= height) y = height - 1;
        uint32_t p = src[y * width + x];
        int r = (p >> 16) & 0xFF;
        int g = (p >> 8) & 0xFF;
        int b = p & 0xFF;
        return (r + g + b) / 3;
    };

    const int threshold = 80; // tweakable

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int gx = get_gray(x + 1, y) - get_gray(x - 1, y);
            int gy = get_gray(x, y + 1) - get_gray(x, y - 1);
            int mag = static_cast<int>(std::sqrt((double)(gx * gx + gy * gy)));
            if (mag > threshold) {
                dst[y * width + x] = 0xFFFFFFFFu; // white
            } else {
                dst[y * width + x] = 0xFF000000u; // black
            }
        }
    }

    // Unlock bitmaps
    AndroidBitmap_unlockPixels(env, inputBitmap);
    AndroidBitmap_unlockPixels(env, outBitmap);

    // Return output bitmap
    return outBitmap;
}
