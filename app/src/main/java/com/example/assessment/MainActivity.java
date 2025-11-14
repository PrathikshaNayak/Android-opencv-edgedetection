package com.example.assessment;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    ImageView inputImageView, outputImageView;
    Button pickImageBtn, detectEdgesBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        inputImageView = findViewById(R.id.inputImage);
        outputImageView = findViewById(R.id.outputImage);
        pickImageBtn = findViewById(R.id.pickImage);
        detectEdgesBtn = findViewById(R.id.detectEdges);
    }
}
