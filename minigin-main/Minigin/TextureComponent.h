#pragma once
#include <memory>
#include <string>
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{
	class TextureComponent final : public ComponentBase
	{
	public:
		TextureComponent(GameObject* owner);
		virtual ~TextureComponent() override = default;

		virtual void Render() const override;


		void SetTexture(const std::string& filename);
		glm::vec2 GetTextureSize() const { return m_pTexture->GetSize(); }

	
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};

}