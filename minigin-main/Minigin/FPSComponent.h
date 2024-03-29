#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class Font;

	class FPSComponent final : public ComponentBase
	{
	public:
		FPSComponent(GameObject* owner, const std::shared_ptr<Font>& font);

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

	private:
		std::unique_ptr<TextComponent> m_pTextCp;

		void UpdateFPS(float deltaTime) const;
	};
}

