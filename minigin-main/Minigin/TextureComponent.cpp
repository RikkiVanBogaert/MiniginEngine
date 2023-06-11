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
	Renderer::GetInstance().RenderTexture(*m_pTexture, GetOwner()->GetWorldTransform().x, GetOwner()->GetWorldTransform().y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().GetTexture(filename);
	GetOwner()->SetSize(m_pTexture->GetSize());
}

