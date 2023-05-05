#pragma once

#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class RotationCp final : public ComponentBase
	{
	public:
		RotationCp(GameObject* owner, float rotSpeed, float radius);

		virtual void Update(float deltaTime) override;

	protected:


	private:
		float m_RotSpeed{};
		float m_Radius{};
		float m_Angle{};
		glm::vec2 m_OffsetToParent{};
	};
}