package com.georgeren.myndk1;

/**
 * Created by georgeRen on 2017/9/21.
 */

public class FileUtil {
    /**
     * 文件拆分
     * @param path 路径
     * @param pattern 拆分法则 UTF-8
     * @param count 个数 9
     */
    public static native void diff(String path, String pattern, int count);


    /**
     * 文件合并
     * @param path
     * @param pattern
     * @param count
     */
    public static native void patch(String path, String pattern, int count);
}
