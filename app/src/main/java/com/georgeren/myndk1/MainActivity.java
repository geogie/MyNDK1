package com.georgeren.myndk1;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        findViewById(R.id.btnDiff).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "diff-");
                String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "test_src.txt";
                // 写%是一个规则处理：c代码中会用sprintf处理，[0,n-1]个文件，需要手动建利diff文件夹，否则报错,分割后的子文件中文乱码--》合并后没有乱。
                String pathDiff = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "diff/test_%d.txt";
                FileUtil.diff(path, pathDiff, 9);
            }
        });
        findViewById(R.id.btnPatch).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "patch-");
                String pathPatch = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "diff/test_%d.txt";
                String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "diff/test_src.txt";
                FileUtil.patch(path, pathPatch, 9);
            }
        });

        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
