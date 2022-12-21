#pragma once

#include <map>
#include "../sfml.h"

class AssetsManager sealed
{
public:
	std::map<std::string, sf::Texture*> Textures;
	std::map<std::string, sf::SoundBuffer*> Sounds;
	std::map<std::string, sf::Music*> Musics;
	std::map<std::string, sf::Font*> Fonts;

	AssetsManager();
	~AssetsManager();
	AssetsManager(const AssetsManager&) = delete;

	void load();
private:
	static std::string getFilename(const std::string& filepath);
};

