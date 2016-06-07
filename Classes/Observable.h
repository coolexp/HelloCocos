#pragma once
#include <memory>
#include <mutex>
#include "cocos2d.h"
#include "DataVO.h"

class Observable {
public:
	void registerNode(const std::weak_ptr<DataVO>& node);
	void unRegisterNode(const std::weak_ptr<DataVO>& node);
	void notifyObservers();
	static Observable* getInstance();
private:
	static Observable* instance;
private:
	std::vector<std::weak_ptr<DataVO> > m_pNodes;
	mutable std::mutex mutex;
};
