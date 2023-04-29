#include "Level.h"

using namespace std;
#include <fstream>
#include <sstream>

Level::Level(const std::string& mapFile)
{
	auto map = parse_csv(mapFile);
	for (auto i : map)
	{
		std::cout << i;
	}
}


std::vector<int> Level::parse_csv(const std::string& filename)
{
	std::vector<int> result;

	// Open the file for reading
	std::ifstream file(filename);
	if (!file.is_open())
	{
		// Handle error
		std::cout << "Couldnt open file\n";
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

	std::cout << "File succesfully opened\n";
	return result;
}