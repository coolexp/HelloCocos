#include "DataVO.h"
#include "cocos2d.h"

using namespace cocos2d;

void DataVO::showValue() {
	CCLOG("showValue:%d", m_pValue);
}

void DataVO::setValue(int i) {
	m_pValue = i;
}

DataVO::~DataVO() {
	CCLOG("DataVO~");
}