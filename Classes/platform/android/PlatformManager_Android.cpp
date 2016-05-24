#include "PlatformManager_Android.h"
#include "platform/android/jni/JniHelper.h"


#define CLASS_NAME "org/cocos2dx/cpp/JniFuncHelper"

void PlatformManager_Android::showTipDialog(const std::string& title, const std::string& msg){
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showTipDialog", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jTitle = t.env->NewStringUTF(title.c_str());
		jstring jMsg = t.env->NewStringUTF(msg.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle, jMsg);
		t.env->DeleteLocalRef(jTitle);
		t.env->DeleteLocalRef(jMsg);
	}
}

extern "C"{
	void Java_org_cocos2dx_cpp_JniFuncHelper_setPackageName(JNIEnv *env, jobject thiz, jstring packageName){
		const char *pkgName = env->GetStringUTFChars(packageName, NULL);
		PlatformManager::getInstance()->setPackageName(pkgName);
		env->ReleaseStringUTFChars(packageName, pkgName);
	}

	void Java_org_cocos2dx_cpp_JniFuncHelper_exitApp(JNIEnv *env, jobject thiz)
	{
		PlatformManager::getInstance()->exitApp();
	}
}

bool PlatformManager_Android::init(){
	if (!PlatformManager::init()){
		return false;
	}
	return true;
}



PlatformManager* PlatformManager::getInstance()
{
	
	if (instance == nullptr)
{
		
		instance = new PlatformManager_Android();
		
		if (!instance->init())
{
			
			delete instance;
			
			instance = nullptr;
		
		}
	
	}
	
	return instance;

}