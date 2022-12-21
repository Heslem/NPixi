#include "AssetsManager.h"

#include <string>
#include <iostream>
#include <filesystem>

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
    std::cout << "Delete assets" << std::endl;
    for (const auto& item : Textures) {
        delete item.second;
    }
    for (const auto& item : Sounds) {
        delete item.second;
    }
    for (const auto& item : Musics) {
        delete item.second;
    }
    for (const auto& item : Fonts) {
        delete item.second;
    }
}

void AssetsManager::load()
{
    // TODO: use template for loading
    using namespace std;

    std::string texturesPath = "content/textures/";
    for (const auto& entry : filesystem::directory_iterator(texturesPath)) {
        string filepath = entry.path().string();
        
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(filepath)) {
            throw std::exception();
        }

        const std::string filename = getFilename(filepath);
        Textures[filename] = texture;
        cout << "Load texture: " << filename << endl;
    }

    std::string musicsPath = "content/musics/";
    for (const auto& entry : filesystem::directory_iterator(musicsPath)) {
        string filepath = entry.path().string();

        sf::Music* music = new sf::Music();
        if (!music->openFromFile(filepath)) {
            throw std::exception();
        }

        const std::string filename = getFilename(filepath);
        Musics[filename] = music;
        cout << "Load music: " << filename << endl;
    }

    std::string fontsPath = "content/fonts/";
    for (const auto& entry : filesystem::directory_iterator(fontsPath)) {
        string filepath = entry.path().string();

        sf::Font* font = new sf::Font();
        if (!font->loadFromFile(filepath)) {
            throw std::exception();
        }

        const std::string filename = getFilename(filepath);
        Fonts[filename] = font;
        cout << "Load font: " << filename << endl;
    }

    std::string soundsPath = "content/sounds/";
    for (const auto& entry : filesystem::directory_iterator(soundsPath)) {
        string filepath = entry.path().string();

        sf::SoundBuffer* sound = new sf::SoundBuffer();
        if (!sound->loadFromFile(filepath)) {
            throw std::exception();
        }

        const std::string filename = getFilename(filepath);
        Sounds[filename] = sound;
        cout << "Load sound: " << filename << endl;
    }
}

std::string AssetsManager::getFilename(const std::string& filepath)
{
    std::string temp(filepath);
    temp = filepath.substr(filepath.find_last_of("/\\") + 1);
    std::string fileWithoutExt = temp.substr(0, temp.find_last_of('.'));

    return fileWithoutExt;
}
