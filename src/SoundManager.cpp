#include "SoundManager.hpp"

SoundManager::SoundManager() {}

void SoundManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filePath)) {
        soundBuffers[name] = buffer;
        sounds[name] = sf::Sound(soundBuffers[name]);
    } else {
        // Handle loading error
        std::cerr << "Error loading sound: " << filePath << std::endl;
    }
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    } else {
        // Handle sound not found
        std::cerr << "Sound not found: " << name << std::endl;
    }
}
