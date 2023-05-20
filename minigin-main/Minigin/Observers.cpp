//#pragma once
//#include "Observers.h"
//#include "GameObject.h"
//#include "TextComponent.h"
//#include "CounterCp.h"
//#include "Scene.h"
//
//#include <iostream>
//
//class PointsCp;
//
//namespace dae
//{
//	class HealthCp;
//}
//
//using namespace dae;
//
//void UI::OnNotify(ObserverEvent event, GameObject* owner)
//{
//	switch (event)
//	{
//	case ActorDied:
//		UpdateUI(owner, "Lives");
//		std::cout << "ACTOR DIED - From Observer\n";
//		break;
//	case ScoredPoint:
//		UpdateUI(owner, "Points");
//		break;
//	}
//}
//
//void UI::UpdateUI(GameObject* owner, const std::string& UIType)
//{
//	std::string newValue{};
//	//dae::UICp* text{};
//
//	//ugly ah code man but idk
//	for (auto sibling : owner->GetScene()->GetGameObjects())
//	{
//		if (sibling->NeedsDeleting()) continue;
//
//		if (sibling->GetTag() != owner->GetTag())
//			continue;
//		
//		if (UIType == "Lives")
//		{
//			if (auto hp = sibling->GetComponent<HealthCp>())
//			{
//				newValue = std::to_string(hp->GetAmount());
//			}
//
//		}
//		else if (UIType == "Points")
//		{
//			if (auto hp = sibling->GetComponent<PointsCp>())
//			{
//				newValue = std::to_string(hp->GetAmount());
//			}
//
//		}
//
//	}
//
//	/*if (text)
//	{
//		text->SetText(text->GetBeginText() + newValue);
//	}*/
//
//}
