#pragma once

#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class PlatformManager{
public:
	static PlatformManager* getInstance();
	virtual ~PlatformManager();
protected:
	static PlatformManager* instance;
	virtual bool init();

public:
	virtual void showTipDialog(const std::string& title, const std::string& msg){};

	void setPackageName(const std::string& value);
	void exitApp();
};