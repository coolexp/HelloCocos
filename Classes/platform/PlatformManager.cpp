#include "PlatformManager.h"




PlatformManager* PlatformManager::instance = nullptr;
bool PlatformManager::init(){
	return true;
}
void PlatformManager::setPackageName(const std::string& value){
	log("PlatformManager::setPackageName:%s",value.c_str());
}

void PlatformManager::exitApp(){
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

PlatformManager::~PlatformManager(){
	
}