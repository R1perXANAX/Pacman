//
// Created by R1perXNX on 7/1/2024.
//

#include "SoundManager.h"

using namespace Game;

// Loads a sound associated with a specific event and stores it in the soundBuffers map.
void SoundManager::LoadSound(const SubjectEvent &event, const std::string &fileName) {
    try {
        sf::SoundBuffer buffer;
        // Attempt to load the sound file into the buffer
        if (buffer.loadFromFile(fileName)) {
            soundBuffers[event] = buffer;  // Store the loaded buffer in the map
        } else {
            throw std::runtime_error("Failed to load sound: " + fileName);
        }
    } catch (const std::exception &e) {
        // Log any errors that occur during loading
        std::cerr << e.what() << std::endl;
    }
}

// Loads the background sound into the longSongBuffer.
void SoundManager::LoadBackgroundSound(const std::string &fileName) {
    try {
        // Attempt to load the background sound file into the longSongBuffer
        if (!longSongBuffer.loadFromFile(fileName)) {
            throw std::runtime_error("Failed to load background sound: " + fileName);
        }
    } catch (const std::exception &e) {
        // Log any errors that occur during loading
        std::cerr << e.what() << std::endl;
    }
}

// Updates the sound manager to play sounds associated with events and manage currently playing sounds.
void SoundManager::Update(const SubjectEvent &event) {
    // Check if there is a sound buffer associated with the event
    if (soundBuffers.find(event) != soundBuffers.end()) {
        sf::Sound sound;
        sound.setBuffer(soundBuffers[event]);  // Set the sound buffer for the event
        sounds.push_back(sound);  // Add the sound to the list of currently playing sounds
        sounds.back().play();  // Play the sound
    }

    // Remove sounds that have finished playing from the sounds vector
    sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
                                [](const sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; }),
                 sounds.end());
}

// Plays the background sound if it's not already playing.
void SoundManager::PlayBackground() {
    // Check if the background sound is not already playing
    if (longSong.getStatus() != sf::Sound::Playing) {
        longSong.setBuffer(longSongBuffer);  // Set the sound buffer for the background sound
        longSong.play();  // Play the background sound
    }
}

// Constructor: Initializes the SoundManager by loading sounds for specific events.
SoundManager::SoundManager() {
    try {
        LoadSound(PacmanDead, "../Resources/explosion.wav");  // Load the sound for when Pacman dies
        LoadSound(CoinEaten, "../Resources/coin.wav");  // Load the sound for when a coin is eaten
    } catch (const std::exception &e) {
        // Log any errors that occur during the SoundManager initialization
        std::cerr << "Error in SoundManager constructor: " << e.what() << std::endl;
    }
}

// Stops the background sound if it is currently playing.
void SoundManager::StopBackground() {
    // Check if the background sound is playing
    if (longSong.getStatus() == sf::Sound::Playing) {
        longSong.stop();  // Stop the background sound
    }
}
