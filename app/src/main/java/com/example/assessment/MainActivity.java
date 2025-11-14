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

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");  // Load C++ library
    }

    // Native function from C++
    public native Bitmap detectEdges(Bitmap inputBitmap);

    ImageView inputImageView, outputImageView;
    Button pickImageBtn, detectEdgesBtn;
    Bitmap selectedBitmap = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        inputImageView = findViewById(R.id.inputImage);
        outputImageView = findViewById(R.id.outputImage);
        pickImageBtn = findViewById(R.id.pickImage);
        detectEdgesBtn = findViewById(R.id.detectEdges);

        pickImageBtn.setOnClickListener(v -> openImagePicker());

        detectEdgesBtn.setOnClickListener(v -> {
            if (selectedBitmap == null) {
                Log.e("EdgeApp", "No image selected");
                return;
            }

            Bitmap processed = detectEdges(selectedBitmap);
            outputImageView.setImageBitmap(processed);
        });
    }

    // Image picker launcher
    ActivityResultLauncher<String> imagePickerLauncher =
            registerForActivityResult(new ActivityResultContracts.GetContent(), uri -> {
                if (uri != null) loadSelectedImage(uri);
            });

    private void openImagePicker() {
        imagePickerLauncher.launch("image/*");
    }

    // Load image into ImageView
    private void loadSelectedImage(Uri uri) {
        try {
            InputStream in = getContentResolver().openInputStream(uri);
            selectedBitmap = BitmapFactory.decodeStream(in);
            inputImageView.setImageBitmap(selectedBitmap);

            if (in != null) in.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
