#pragma once
#include "Observers.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "CounterCp.h"
#include "UICp.h"
#include "Scene.h"

#include <iostream>

using namespace dae;

void UI::OnNotify(Event event, GameObject* owner)
{
	switch (event)
	{
	case ActorDied:
		UpdateUI(owner, "Lives");
		std::cout << "ACTOR DIED - From Observer\n";
		break;
	case ScoredPoint:
		UpdateUI(owner, "Points");
		break;
	}
}

void UI::UpdateUI(GameObject* owner, const std::string& UIType)
{
	std::string newValue{};
	dae::UICp* text{};

	//ugly ah code man but idk
	for (auto sibling : owner->GetScene()->GetGameObjects())
	{
		if (sibling->NeedsDeleting()) continue;

		if (sibling->GetTag() != owner->GetTag())
			continue;


		if (auto textCp = sibling->GetComponent<dae::UICp>())
		{
			if(textCp->GetType() == UIType)
				text = textCp;
		}
		
		if (UIType == "Lives")
		{
			if (auto hp = sibling->GetComponent<dae::HealthCp>())
			{
				newValue = std::to_string(hp->GetAmount());
			}

		}
		else if (UIType == "Points")
		{
			if (auto hp = sibling->GetComponent<dae::PointsCp>())
			{
				newValue = std::to_string(hp->GetAmount());
			}

		}

	}

	if (text)
	{
		text->SetText(text->GetBeginText() + newValue);
	}

}
