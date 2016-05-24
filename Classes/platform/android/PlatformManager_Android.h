#pragma once
#include "platform/PlatformManager.h"

class PlatformManager_Android :public PlatformManager{
public:
	virtual bool init();
	virtual void showTipDialog(const std::string& title, const std::string& msg) override;
};