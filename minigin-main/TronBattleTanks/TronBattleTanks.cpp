#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

void LoadGameScene()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto levelObj = std::make_shared<Level>("../Data/Resources/LevelLayout0.csv");
	//scene.Add(levelObj);
	//scene.SetActiveLevel(levelObj.get());

	//auto gameObj = std::make_shared<GameObject>();
	//scene.Add(gameObj);

	////InitControllableObjects(scene, gameObj.get());

}

void load()
{
	//LoadDaeScene();
	LoadGameScene();
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}