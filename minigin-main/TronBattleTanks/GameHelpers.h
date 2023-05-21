#pragma once
#include "Scene.h"
#include "GameObject.h"

#include <string>
#include <iostream>
#include <fstream>

inline dae::GameObject* GetGameObject(dae::Scene* scene, const std::string& tag)
{
	for (const auto o : scene->GetGameObjects())
	{
        if(o->NeedsDeleting()) continue;
        if (o->GetTag() != tag) continue;

		return o.get();
	
	}
	return nullptr;
}

template <typename T>
T* GetComponentInScene(dae::Scene* scene, const std::string& tag)
{
	for (const auto o : scene->GetGameObjects())
	{
		if(!o->GetComponent<T>()) continue;

		if (o->GetTag() != tag) continue;

		return o->GetComponent<T>();
	}

	return nullptr;
}

inline void WriteTextToFile(const std::string& filename, const std::string& text)
{
    std::ifstream inputFile(filename);
    std::ofstream outputFile;

    if (inputFile.is_open()) {
        std::string line;
        std::string fileContent;

        while (std::getline(inputFile, line)) {
            fileContent += line + "\n";
        }

        inputFile.close();

        outputFile.open(filename);

        if (outputFile.is_open()) {
            outputFile << fileContent << text;
            outputFile.close();
            std::cout << "Text written to file successfully." << std::endl;
        }
        else {
            std::cout << "Unable to open the file for writing." << std::endl;
        }
    }
    else {
        std::cout << "Unable to open the file for reading." << std::endl;
    }
}