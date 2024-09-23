#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

class SoundManager {
public:
    SoundManager();                                             // Constructor
    void loadSound(const std::string& name, const std::string& filePath);
    void playSound(const std::string& name);
    void setVolume(const std::string& name, float volume);      // Setter
    
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;        // Member variables
    std::map<std::string, sf::Sound> sounds;
};

#endif // SOUND_MANAGER_HPP
