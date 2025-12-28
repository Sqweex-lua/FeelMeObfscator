#ifdef FEELMEHAPPY_ANDROID
#include "FeelMeHappy.h"
#include <android/log.h>

#define LOG_TAG "FeelMeHappy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapp_MainActivity_initObfuscator(
    JNIEnv* env,
    jobject thiz
) {
    LOGI("Initializing FeelMeHappy obfuscator");
    
    const char* apiKey = FEEL("android_api_key_123");
    const char* serverUrl = FEEL("https://api.android-app.com/v1");
    const char* dbPath = FEEL("/data/data/com.example.myapp/database.db");
    
    LOGI("API Key: %s", apiKey);
    LOGI("Server URL: %s", serverUrl);
    LOGI("DB Path: %s", dbPath);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapp_MainActivity_getObfuscatedString(
    JNIEnv* env,
    jobject thiz,
    jstring input
) {
    const char* nativeString = env->GetStringUTFChars(input, nullptr);
    const char* obfuscated = FEEL(nativeString);
    jstring result = env->NewStringUTF(obfuscated);
    env->ReleaseStringUTFChars(input, nativeString);
    return result;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapp_MainActivity_getObfuscatedInt(
    JNIEnv* env,
    jobject thiz,
    jint value
) {
    int obfuscated = FEEL(static_cast<int>(value));
    return static_cast<jint>(obfuscated);
}

class AndroidConfig {
private:
    const char* m_appId = FEEL("com.example.myapp");
    const char* m_adUnitId = FEEL("ca-app-pub-3940256099942544/6300978111");
    const char* m_analyticsKey = FEEL("UA-12345678-1");
    int m_versionCode = FEEL(1001);
    
public:
    void logConfig() {
        LOGI("App ID: %s", m_appId);
        LOGI("Ad Unit: %s", m_adUnitId);
        LOGI("Analytics: %s", m_analyticsKey);
        LOGI("Version: %d", m_versionCode);
    }
};

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapp_MainActivity_testObfuscator(
    JNIEnv* env,
    jobject thiz
) {
    AndroidConfig config;
    config.logConfig();
    
    const char* permissions[] = {
        FEEL("android.permission.INTERNET"),
        FEEL("android.permission.ACCESS_NETWORK_STATE"),
        FEEL("android.permission.WRITE_EXTERNAL_STORAGE")
    };
    
    for (int i = 0; i < 3; i++) {
        LOGI("Permission %d: %s", i, permissions[i]);
    }
}
#else
int main() {
    return 0;
}
#endif
