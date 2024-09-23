#include "SoundManager.hpp"

/*
Class definition for SoundManager, a class that manages the loading and playing of sounds.
*/

SoundManager::SoundManager() {}

// Load the sound with the given name and file path
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

// Play the sound with the given name
void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    } else {
        // Handle sound not found
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

// Set the volume of the sound with the given name
void SoundManager::setVolume(const std::string& name, float volume) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].setVolume(volume);
    } else {
        // Handle sound not found
        std::cerr << "Sound not found: " << name << std::endl;
    }
}
