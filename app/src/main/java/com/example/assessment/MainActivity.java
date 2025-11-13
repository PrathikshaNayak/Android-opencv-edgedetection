package com.example.assessment;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.graphics.Bitmap;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private ImageView imageView;
    private Button edgeButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.imageView);
        edgeButton = findViewById(R.id.edgeButton);

        if (!OpenCVLoader.initDebug()) {
            // Handle OpenCV initialization error
        }

        edgeButton.setOnClickListener(v -> {
            // Load bitmap from drawable
            Bitmap bitmap = Bitmap.createBitmap(512, 512, Bitmap.Config.ARGB_8888); // placeholder bitmap

            Mat inputMat = new Mat();
            Mat outputMat = new Mat();
            Utils.bitmapToMat(bitmap, inputMat);

            edgeDetection(inputMat.getNativeObjAddr(), outputMat.getNativeObjAddr());

            Utils.matToBitmap(outputMat, bitmap);
            imageView.setImageBitmap(bitmap);
        });
    }

    public native String stringFromJNI();
    public native void edgeDetection(long matAddrInput, long matAddrOutput);
}
