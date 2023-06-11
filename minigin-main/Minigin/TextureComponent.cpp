#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

using namespace dae;

TextureComponent::TextureComponent(GameObject* owner):
ComponentBase(owner)
{}

void TextureComponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, GetOwner()->GetWorldTransform().x, GetOwner()->GetWorldTransform().y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().GetTexture(filename);
	GetOwner()->SetSize(m_Texture->GetSize());
}

