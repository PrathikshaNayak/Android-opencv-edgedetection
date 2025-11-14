# Android-opencv-edgedetection
Android + OpenCV + OpenGL + Web project
# Android OpenCV Edge Detection Project

## 🏆 Features Implemented

### Android App
- Real-time image edge detection using **C++ (NDK) + OpenCV**
- Load images from gallery and detect edges using **Canny algorithm**
- JNI bridge between Android Java and C++ native library
- View processed images in **ImageView** components
- Saves processed images (optional)

### Web Viewer
- Simulates Android app output for demonstration
- Displays raw camera feed and edge-detected frames
- Shows FPS, processing time, and frame statistics
- Built in **TypeScript / JavaScript** with responsive layout

---

## 📸 Screenshots / GIF

**Android App:**

![Input Image](op-images/input_image.png)
![Edge Detection](op-images/edge_output.png)

**Web Viewer:**

![Web Viewer](op-images/web_viewer.png)

---

## ⚙️ Setup Instructions

### 1. Android App
1. Install **Android Studio** with C++ / NDK support
2. Clone this repository:
   ```bash
   git clone https://github.com/YourUsername/Android-opencv-edgedetection.git
   cd Android-opencv-edgedetection
Architecture
Android + C++

Java MainActivity handles UI (ImageViews + Buttons)

JNI bridge connects Java with native C++ (native-lib.cpp)

C++ processing:

Converts Bitmap → cv::Mat

Applies Canny edge detection

Returns processed Bitmap to Java

Output shown in ImageView

Web (TypeScript)

Displays simulated camera + edge detection

Uses canvas for frame rendering

Updates stats (FPS, JNI calls, processing time) every second

Can be extended to fetch real-time frames from Android via WebSocket
 Results:
