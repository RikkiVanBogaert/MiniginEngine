#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public ComponentBase
	{
	public:
		explicit TransformComponent();
		virtual ~TransformComponent();

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;


		virtual void Update(float deltaTime);
		virtual void Render() const;
		void SetTransform(const Transform& transform);
		void SetPosition(const glm::vec3& pos);


	protected:
		Transform m_Transform{};

	};

}
