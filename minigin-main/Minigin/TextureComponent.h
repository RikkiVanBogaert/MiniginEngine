#pragma once
#include <string>
#include "Texture2D.h"
#include "BaseComponent.h"

//using namespace dae;
// Texture2D;

class TextureComponent final : public ComponentBase
{
public:
	TextureComponent(GameObject* owner );
	virtual void Render() const override;

	
	void SetTexture(const std::string& filename);

	//virtual ~TextureComponent();

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};

};

