#pragma once
#include "platform/PlatformManager.h"

class PlatformManager_Win32 :public PlatformManager{
public:
	virtual bool init();
};