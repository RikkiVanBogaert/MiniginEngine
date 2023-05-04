#pragma once
#include <string>
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{


	class TextureComponent final : public ComponentBase
	{
	public:
		TextureComponent(GameObject* owner);
		virtual void Render() const override;


		void SetTexture(const std::string& filename);
		glm::vec2 GetTextureSize() { return m_Texture->GetSize(); };

		//virtual ~TextureComponent();

	private:
		std::shared_ptr<dae::Texture2D> m_Texture{};
	};

}