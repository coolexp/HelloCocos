#pragma once
#include "cocos2d.h"

class ShaderLayer :public cocos2d::Layer {
public:
	static ShaderLayer* create(const std::string& shaderfile);
	bool initWithShader(const std::string& shaderfile);
	ShaderLayer();
	~ShaderLayer();
	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
private:
	cocos2d::RenderTexture* m_pRenderTexture;
	cocos2d::Sprite* m_pRendTexSprite;
	std::string m_pShaderFile;
	cocos2d::GLProgram* m_pGlProgram;
	cocos2d::EventListenerCustom* m_pRecreateEvent;
};