#include "AssetManager.hpp"

AssetManager::AssetManager() {}                                                                       // Constructor

AssetManager::AssetManager(const AssetManager&) {}                                                 // Copy constructor

AssetManager& AssetManager::operator=(const AssetManager&) {                                       // Assignment operator
    return *this;
}

AssetManager& AssetManager::getInstance() {                                                           // Singleton instance
    static AssetManager instance;                                                                        // static instance of AssetManager
    return instance;
}

sf::Texture* AssetManager::getTexture(const std::string& filepath) {                                     // Get texture method
    auto search = textures.find(filepath);                                                                  // Search for texture in the container
    if (search != textures.end()) {                                                                         // If texture is found, return it
        return &search->second;
    } else {                                                                                                // If texture is not found, load it
        sf::Texture texture;
        if (!texture.loadFromFile(filepath)) {
            std::cerr << "Failed to load texture: " << filepath << std::endl;
            return nullptr;
        } else {
            textures.insert(std::make_pair(filepath, texture));                                             // Insert loaded texture
            return &textures[filepath];                                                                     // Return the newly loaded texture
        }
    }
}