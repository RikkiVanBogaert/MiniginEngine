#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> GetTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

		std::vector<int> ParseCsv(const std::string& filename) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;

		std::map<std::string, std::shared_ptr<Texture2D>> m_texturesMap;

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
	};
}
