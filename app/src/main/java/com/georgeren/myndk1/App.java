package com.georgeren.myndk1;

import android.app.Application;

/**
 * Created by georgeRen on 2017/9/21.
 */

public class App extends Application{
    static {
        //加载动态库.so文件，注意不用写lib前缀，系统会默认添加
        System.loadLibrary("native-lib");
    }
    @Override
    public void onCreate() {
        super.onCreate();
    }
}
