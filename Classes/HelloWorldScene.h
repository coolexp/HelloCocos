#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <mutex>
#include "DataLock.h"

struct DataVO
{
	int i;
	DataVO(){
		i = 1;
	}
};
struct TestData {
	TestData(bool *value) {
		m_pValue = value;
	}
	~TestData() {
		*m_pValue = false;
	}
	bool *m_pValue;
};

struct Counter {
	std::mutex mutex;
	int value;
	bool *m_pValue;
	Counter(bool *value) : value(0) {
		m_pValue = value;
	}
	void increment() {
		mutex.lock();
		++value;
		mutex.unlock();
	}

	void decrement() {
		mutex.lock();
		--value;
		mutex.unlock();

	}

	int getValue() {
		DataLock lock;
		return value;
	}
	~Counter() {
		*m_pValue = false;
	}
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	static void printHandler(int value);
	~HelloWorld();
private:
	void testHandler(int value);
	DataVO* m_pDataVO;
	void setDataVO(DataVO* vo);
	void setDataVO(const DataVO& vo);
	void testSprite();
	/**
	* @brief 测试一种错误的做法，以为已经释放了的内存
	*/
	void generateChar(char* p);
	void timeGap(float dt);
	/**
	* @brief 主动Crash，
	*/
	void crashMe();
	/**
	* @brief 显示Android的弹窗界面
	*/
	void showAndroidMsg();
	/**
	* @brief 测试多线程操作数据，
	*/
	void testMulThread();
};

#endif // __HELLOWORLD_SCENE_H__
