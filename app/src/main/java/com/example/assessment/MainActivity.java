package com.example.assessment;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.Button;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib"); // Load C++ library
        System.loadLibrary("opencv_java4"); // Load OpenCV
    }

    private ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.imageView);
        Button btnEdge = findViewById(R.id.btnEdge);

        // Load image from drawable
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.sample);
        imageView.setImageBitmap(bitmap);

        btnEdge.setOnClickListener(v -> {
            Bitmap edgeBitmap = bitmap.copy(Bitmap.Config.ARGB_8888, true);
            Mat mat = new Mat();
            Utils.bitmapToMat(edgeBitmap, mat);

            detectEdges(mat); // Call native C++ function

            Utils.matToBitmap(mat, edgeBitmap);
            imageView.setImageBitmap(edgeBitmap);
        });
    }

    // Native function
    public native void detectEdges(long matAddr);
}
