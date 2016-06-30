#include "ShaderLayer.h"

using namespace cocos2d;

ShaderLayer::ShaderLayer() {
	m_pRenderTexture = nullptr;
	m_pRendTexSprite = nullptr;
	m_pGlProgram = nullptr;
	m_pRecreateEvent = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	m_pRecreateEvent = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event) {
		if (m_pGlProgram) {
			m_pGlProgram->reset();
			auto fragSource = FileUtils::getInstance()->getStringFromFile(m_pShaderFile);
			m_pGlProgram->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_pRecreateEvent, -1);
#endif
	
}
ShaderLayer::~ShaderLayer() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	if (m_pRecreateEvent) {
		Director::getInstance()->getEventDispatcher()->removeEventListener(m_pRecreateEvent);
	}
	m_pRecreateEvent = nullptr;
#endif
}
ShaderLayer* ShaderLayer::create(const std::string& shaderfile) {
	ShaderLayer* layer = new ShaderLayer();
	if (layer&&layer->initWithShader(shaderfile)) {
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool ShaderLayer::initWithShader(const std::string& shaderfile) {
	if (!Layer::init()) {
		return false;
	}
	m_pShaderFile = shaderfile;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_pRenderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	addChild(m_pRenderTexture);
	// init sprite
	m_pRendTexSprite = Sprite::create();
	m_pRendTexSprite->setTexture(m_pRenderTexture->getSprite()->getTexture());
	m_pRendTexSprite->setTextureRect(Rect(0, 0, m_pRendTexSprite->getTexture()->getContentSize().width, m_pRendTexSprite->getTexture()->getContentSize().height));
	m_pRendTexSprite->setPosition(Point::ZERO);
	m_pRendTexSprite->setAnchorPoint(Point::ZERO);
	m_pRendTexSprite->setFlippedY(true);
	addChild(m_pRendTexSprite);

	auto fragSource = FileUtils::getInstance()->getStringFromFile(m_pShaderFile);
	m_pGlProgram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(m_pGlProgram);
	m_pRendTexSprite->setGLProgramState(glProgramState);

	/*glProgramState->setUniformVec2("resolution", visibleSize);
	glProgramState->setUniformFloat("blurRadius", 10.0f);
	glProgramState->setUniformFloat("sampleNum", 7.0f);*/
	return true;
}

void ShaderLayer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) {

	if (m_pRenderTexture == nullptr) {
		return;
	}
	m_pRenderTexture->beginWithClear(0, 0, 0, 0);
	for (auto child : getChildren()){
		if (child != m_pRenderTexture && child != m_pRendTexSprite)
			child->visit(renderer, parentTransform, parentFlags);
	}
	m_pRenderTexture->end();

	m_pRendTexSprite->visit(renderer, parentTransform, parentFlags);
}