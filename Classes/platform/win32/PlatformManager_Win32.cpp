#include "PlatformManager_Win32.h"


bool PlatformManager_Win32::init(){
	if (!PlatformManager::init()){
		return false;
	}
	return true;
}

PlatformManager* PlatformManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new PlatformManager_Win32();
		if (!instance->init())
		{
			delete instance;
			instance = nullptr;
		}
	}
	return instance;
}