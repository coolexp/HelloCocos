#include "Observable.h"

using namespace cocos2d;

Observable* Observable::instance = nullptr;

Observable* Observable::getInstance() {
	if (instance == nullptr) {
		instance = new Observable();
	}
	return instance;
}
void Observable::registerNode(const std::weak_ptr<DataVO>& node) {
	m_pNodes.push_back(node);
}
void Observable::unRegisterNode(const std::weak_ptr<DataVO>& node) {
	for (auto it = m_pNodes.begin();it!=m_pNodes.end();it++)
	{
		if (it->lock() == node.lock()) {
			m_pNodes.erase(it);
			break;
		}
	}
}
void Observable::notifyObservers() {
	auto it = m_pNodes.begin();
	while (it != m_pNodes.end()) {
		std::shared_ptr<DataVO> obj = it->lock();
		if (obj&&it->expired()) {
			// do something
			DataVO* pp = obj.get();
			pp->showValue();
			++it;
		}else {
			it = m_pNodes.erase(it);
		}
	}
}