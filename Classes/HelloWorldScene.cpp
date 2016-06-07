#include "HelloWorldScene.h"
#include "platform/PlatformManager.h"
#include "Observable.h"

USING_NS_CC;

static Counter* m_pCounter=nullptr;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
HelloWorld::~HelloWorld() {
	CC_SAFE_DELETE(m_pCounter);
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	ValueMap valueMap = FileUtils::getInstance()->getValueMapFromFile("config.plist");
    
	std::string v = valueMap["txt1"].asString();
	auto label = Label::createWithTTF(v, "fonts/FounderBold.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	testHandler(110);

	// ���Դ����ȫ��ָ��ָ��һ���Ѿ��ͷŵ��ڴ��ַ
	/*DataVO vo;
	vo.setValue(5);
	// �����÷�
	setDataVO(&vo);

	// ��ȷ�÷�
	setDataVO(vo);*/

	std::string value = "HelloWorld";

#if CC_ENABLE_CACHE_TEXTURE_DATA
	// ��������Դ��Ҫ�ָ��ķ�������Androidƽ̨����Ǳ���ģ�����shader�޷��ָ�
	auto resetDataAndTextureListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
		CCLOG("=================================>");
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(resetDataAndTextureListener, 1);
#endif
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/PublicNewSystem.plist");
	auto sp = Sprite::createWithSpriteFrameName("UI_PublicNew_SubHeroLock1.png");
	addChild(sp);
	sp->setPosition(Vec2(100, 200));

	// �����ⲿ�ж�ĳ�����Ƿ�����
	bool isValid = true;
	{
		TestData v(&isValid);
	}
	if (isValid) {
		CCLOG("û������");
	}else {
		CCLOG("�Ѿ�����");
	}

	// ���Դ����д���������ڴ�й¶
	char *p = nullptr;
	generateChar(p);
	free(p);
	{
		m_pDataVO = new DataVO();
		std::shared_ptr<DataVO> pp =std::make_shared<DataVO>(*m_pDataVO);
		Observable::getInstance()->registerNode(pp);
	}
	//Observable::getInstance()->registerNode(node);
    return true;
}
// �����÷�
void HelloWorld::setDataVO(DataVO* vo){
	// m_pDataVO ȫ��ָ�룬���׳�����һȫ��ָ�룬ָ����ʱ��ַ�����´����á�
	m_pDataVO = vo;
}
// ��ȷ�÷�
void HelloWorld::setDataVO(const DataVO& vo){
	
}

static std::atomic<int> cnt = { 0 };
void f()
{
	for (int n = 0; n < 1000; ++n) {
		cnt.fetch_add(1, std::memory_order_relaxed);
	}
}
int t(int value) {
	return value + 10;
}
void HelloWorld::testHandler() {
	std::vector<std::thread> v;
	for (int n = 0; n < 10; ++n) {
		v.emplace_back(f);
	}
	for (auto& t : v) {
		t.join();
	}
	CCLOG("%d", cnt);
	std::future<int> future = std::async(t, 10);
	// ���߳̿������������顣
	int value =future.get();// ���tû��ִ���ֱ꣬�ӵ��ã����̻߳�����
}

void HelloWorld::printHandler(int value){
	log("printHandler:%d",value);
}
void HelloWorld::testHandler(int value){
	std::thread t([=](){
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			HelloWorld::printHandler(value);
		});
	});
	t.detach();
}

void HelloWorld::generateChar(char* p) {
	p = (char *)malloc(100 * sizeof(char));
}

void HelloWorld::timeGap(float dt) {
	if (m_pCounter) {
		m_pCounter->increment();
		int value = m_pCounter->getValue();
		CCLOG("timeGap:%d", value);
	}
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	testHandler();
	//Observable::getInstance()->notifyObservers();
	return;
	testMulThread();// �������߳���GL�̲߳���ͬһ�����ݣ�����ͬ���Լ�׼ȷ��
	return;
	crashMe();
	showAndroidMsg();
}

void HelloWorld::testMulThread(){
	std::thread tt([=]() {
		bool isValid = true;
		m_pCounter = new Counter(&isValid);
		while (true)
		{
			if (isValid) {
				m_pCounter->increment();
				CCLOG("counter.value:%d", m_pCounter->value);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			else {
				break;
			}
		}
	});
	tt.detach();
	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::timeGap));
}
void HelloWorld::crashMe() {
	// ���߳�
	std::thread t([=]() {
		Node* node = nullptr;
		node->setVisible(false);
	});
	t.detach();
}


void HelloWorld::showAndroidMsg() {
	PlatformManager::getInstance()->showTipDialog("Tips", "ExitApp");
}

void HelloWorld::testSprite(){
	Sprite* sprite = nullptr;
	sprite->initWithFile("1.png");
	addChild(sprite);
}