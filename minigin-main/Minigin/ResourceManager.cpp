#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace dae;

void ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

std::vector<int> ResourceManager::ParseCsv(const std::string& filename) const
{
	std::vector<int> result;

	// Open the file for reading
	std::ifstream file(filename);
	if (!file.is_open())
	{
		// Handle error
		std::cout << "Couldn't open file\n";
		return result;
	}

	// Read each line of the file
	std::string line;
	while (std::getline(file, line))
	{
		// Parse the line into integers
		std::stringstream ss(line);
		std::string field;
		while (std::getline(ss, field, ','))
		{
			try
			{
				result.push_back(std::stoi(field));
			}
			catch (std::invalid_argument&)
			{
				// Handle invalid data
				std::cout << "Invalid data in file\n";
			}
		}
	}

	std::cout << "File successfully opened\n";
	return result;
}
