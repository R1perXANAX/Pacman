//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_SOUNDMANAGER_H
#define PACMANV2_SOUNDMANAGER_H


#include "../Logic/ObserverPattern/IObserver.h"
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

namespace Game {
class SoundManager final: public IObserver {
    std::map<SubjectEvent, sf::SoundBuffer> soundBuffers;
    std::vector<sf::Sound> sounds;
    sf::SoundBuffer longSongBuffer;
    sf::Sound longSong;

    void LoadSound(const SubjectEvent& event, const std::string& fileName);

public:
    // Private constructor to prevent instancing
    SoundManager();

    void Update(const SubjectEvent& event) override;
    void LoadBackgroundSound(const std::string& fileName);
    void PlayBackground();
    void StopBackground();
    ~SoundManager() override = default;
};
}

extern std::shared_ptr<Game::SoundManager> gSoundManager;

#endif //PACMANV2_SOUNDMANAGER_H
