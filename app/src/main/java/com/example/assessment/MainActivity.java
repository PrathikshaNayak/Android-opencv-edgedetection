import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;
package com.example.assessment;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.net.Uri;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;

import org.opencv.android.OpenCVLoader;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    ImageView inputImageView, outputImageView;
    Button pickImageBtn, detectEdgesBtn;
    Bitmap selectedBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        inputImageView = findViewById(R.id.inputImage);
        outputImageView = findViewById(R.id.outputImage);
        pickImageBtn = findViewById(R.id.pickImage);
        detectEdgesBtn = findViewById(R.id.detectEdges);

        // OpenCV Initialization
        if (!OpenCVLoader.initDebug()) {
            Log.e("OpenCV", "OpenCV initialization FAILED");
        } else {
            Log.d("OpenCV", "OpenCV initialized SUCCESSFULLY");
        }

        // Pick image button
        pickImageBtn.setOnClickListener(v -> openImagePicker());
    }

    // Image Picker launcher
    ActivityResultLauncher<String> imagePickerLauncher =
            registerForActivityResult(new ActivityResultContracts.GetContent(), uri -> {
                if (uri != null) {
                    loadImage(uri);
                }
            });

    // Opens the gallery
    private void openImagePicker() {
        imagePickerLauncher.launch("image/*");
    }

    // Loads selected image into ImageView
    private void loadImage(Uri uri) {
        try {
            InputStream inputStream = getContentResolver().openInputStream(uri);
            selectedBitmap = BitmapFactory.decodeStream(inputStream);
            inputImageView.setImageBitmap(selectedBitmap);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
