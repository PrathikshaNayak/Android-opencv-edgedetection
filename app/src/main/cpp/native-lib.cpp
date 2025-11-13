#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_assessment_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    return env->NewStringUTF("OpenCV Loaded Successfully!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_assessment_MainActivity_edgeDetection(
        JNIEnv* env,
        jobject /* this */,
        jlong matAddrInput,
        jlong matAddrOutput) {

    cv::Mat &input = *(cv::Mat *) matAddrInput;
    cv::Mat &output = *(cv::Mat *) matAddrOutput;

    cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);
    cv::Canny(output, output, 80, 100);
}
