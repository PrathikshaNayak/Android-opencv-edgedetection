#include <jni.h>
#include <android/bitmap.h>
#include <cmath>

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_assessment_MainActivity_detectEdgesNative(
        JNIEnv *env, jobject obj, jobject inputBitmap) {

    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, inputBitmap, &info);

    void* pixelsIn;
    AndroidBitmap_lockPixels(env, inputBitmap, &pixelsIn);

    // Create output bitmap
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(
            bitmapCls,
            "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;"
    );

    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass configCls = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOf = env->GetStaticMethodID(
            configCls, "valueOf",
            "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;"
    );
    jobject config = env->CallStaticObjectMethod(configCls, valueOf, configName);

    jobject outputBitmap = env->CallStaticObjectMethod(
            bitmapCls, createBitmap,
            info.width, info.height, config
    );

    void* pixelsOut;
    AndroidBitmap_lockPixels(env, outputBitmap, &pixelsOut);

    uint32_t* in = (uint32_t*) pixelsIn;
    uint32_t* out = (uint32_t*) pixelsOut;

    // SIMPLE EDGE EFFECT
    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {

            int idx = y * info.width + x;

            uint32_t px = in[idx];

            int r = (px >> 16) & 0xFF;
            int g = (px >> 8) & 0xFF;
            int b = px & 0xFF;

            int gray = (r + g + b) / 3;

            // Simple threshold edge detection
            uint32_t color = (gray > 128) ? 0xFFFFFFFF : 0xFF000000;

            out[idx] = color;
        }
    }

    AndroidBitmap_unlockPixels(env, inputBitmap);
    AndroidBitmap_unlockPixels(env, outputBitmap);

    return outputBitmap;
}
