#pragma once
#include "BaseComponent.h"

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
	void SetTransform(const dae::Transform& transform);
	void SetPosition(const glm::vec3& pos);


protected:
	dae::Transform m_Transform{};
	bool m_NeedsUpdate{ true };
	//GameObject* m_pOwner;
};

