#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>

class SoundManager {
public:
    SoundManager();
    void loadSound(const std::string& name, const std::string& filePath);
    void playSound(const std::string& name);
    
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
};

#endif // SOUND_MANAGER_HPP
