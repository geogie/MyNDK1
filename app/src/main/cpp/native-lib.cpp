#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO, "georgeren",FORMAT,__VA_ARGS__)
#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG,"georgeren",FORMAT,__VA_ARGS__)
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"georgeren",FORMAT,__VA_ARGS__)

//获取文件大小
long getFileSize(const char *path) {
    FILE *fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_georgeren_myndk1_FileUtil_diff(JNIEnv *env, jclass type, jstring path_, jstring pattern_,
                                        jint count) {
    //需要分割的文件路径
    const char *path = env->GetStringUTFChars(path_, 0);
    //分割之后的小文件命名法则
    const char *pattern = env->GetStringUTFChars(pattern_, 0);

    // TODO
    //得到分割之后的小文件的命名列表（字符串数组），分配内存
    char **patches = (char **) malloc(sizeof(char *) * count);
    int i = 0;
    for (; i < count; i++) {
        //为字符数组的每一个条目分配内存
        patches[i] = (char *) malloc(sizeof(char) * 100);
        sprintf(patches[i], pattern, i);

        //打印日志
        //__android_log_print(ANDROID_LOG_DEBUG, "TAG_NDK", "File Name : %s\n", patches[i]);
        LOGE("position:%d name:%s \n", i, patches[i]);
    }
    FILE *fTotal = fopen(path, "rb");
    int fileSize = getFileSize(path);
    LOGE("fileSize:%d \n", fileSize);

    if (fileSize / count == 0) {
        //可以整除
        int partSize = fileSize / count;
        i = 0;
        for (; i < count; i++) {
            LOGE("1patches:%s \n", patches[i]);
            FILE *fPart = fopen(patches[i], "wb");
            int j = 0;
            for (; j < partSize; j++) {
                fputc(fgetc(fTotal), fPart);
            }
            fclose(fPart);
        }
    } else {
        //不可以整除
        int partSize = fileSize / (count - 1);
        i = 0;
        for (; i < count - 1; i++) {
            LOGE("2patches:%s \n", patches[i]);
            FILE *fPart = fopen(patches[i], "wb");
            int j = 0;
            for (; j < partSize; j++) {
                fputc(fgetc(fTotal), fPart);
            }
            fclose(fPart);
        }
        FILE *fLast = fopen(patches[count - 1], "wb");
        i = 0;
        for (; i < fileSize % (count - 1); i++) {
            fputc(fgetc(fTotal), fLast);
        }
        fclose(fLast);
    }

    //释放资源
    fclose(fTotal);
    i = 0;
    for (; i < count; i++) {
        free(patches[i]);
    }
    free(patches);


    env->ReleaseStringUTFChars(path_, path);
    env->ReleaseStringUTFChars(pattern_, pattern);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_georgeren_myndk1_FileUtil_patch(JNIEnv *env, jclass type, jstring path_, jstring pattern_,
                                         jint count) {
    const char *path = env->GetStringUTFChars(path_, 0);
    const char *pattern = env->GetStringUTFChars(pattern_, 0);

    // TODO
    //得到被分割的小文件的命名列表（字符串数组），分配内存
    char **patches = (char **) malloc(sizeof(char *) * count);
    int i = 0;
    for (; i < count; i++) {
        //为字符数组的每一个条目分配内存
        patches[i] = (char *) malloc(sizeof(char) * 100);
        sprintf(patches[i], pattern, i);

        //打印日志
        //__android_log_print(ANDROID_LOG_DEBUG, "TAG_NDK", "File Name : %s\n", patches[i]);
        LOGE("name:%s\n", patches[i]);
    }

    //合并的文件路径
    FILE *fTotal = fopen(path, "wb");
    i = 0;
    for (; i < count; i++) {
        int patchSize = getFileSize(patches[i]);
        FILE *fPart = fopen(patches[i], "rb");
        int j = 0;
        for (; j < patchSize; j++) {
            fputc(fgetc(fPart), fTotal);
        }
        fclose(fPart);
    }

    //释放资源
    fclose(fTotal);
    i = 0;
    for (; i < count; i++) {
        free(patches[i]);
    }
    free(patches);


    env->ReleaseStringUTFChars(path_, path);
    env->ReleaseStringUTFChars(pattern_, pattern);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_georgeren_myndk1_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
