#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class AssetManager {
private:
    AssetManager();                                      // Constructor (private for singleton pattern)
    AssetManager(const AssetManager&);                // Copy constructor
    AssetManager& operator=(const AssetManager&);     // Assignment operator

    unordered_map<string, sf::Texture> textures;  // Container for textures

public:
    static AssetManager& getInstance();                  // Get instance of AssetManager (singleton)
    sf::Texture* getTexture(const string& filepath);   // Get texture by file path
};

#endif // ASSETMANAGER_HPP