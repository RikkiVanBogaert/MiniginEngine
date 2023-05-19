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
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_pOwner->GetWorldTransform().x, m_pOwner->GetWorldTransform().y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().GetTexture(filename);
	m_pOwner->SetSize(m_Texture->GetSize());
}

