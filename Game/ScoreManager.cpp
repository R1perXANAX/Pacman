//
// Created by R1perXNX on 7/3/2024.
//

#include "ScoreManager.h"
#include <algorithm>

using namespace Game;

// This method updates the score or lives left based on the event received.
void ScoreManager::Update(const SubjectEvent& event) {
    switch (event) {
    case SubjectEvent::PacmanDead:
        lifeLeft--; // Decrease life when Pacman dies
        break;
    case SubjectEvent::CoinEaten:
        coinsCollected++;   // Increase coin count when a coin is eaten
        currentScore += 10; // Increase score by 10
        break;
    case SubjectEvent::GhostEaten:
        currentScore += 100; // Increase score by 100 when a ghost is eaten
        break;
    default:
        break;
    }
}

// Constructor: Reserves space for top 5 scores and loads the scores from a file.
ScoreManager::ScoreManager() {
    topScores.reserve(5); // Reserve space for the top 5 scores
    LoadTopScores();      // Load the top scores from file
}

// Destructor: Saves the top scores to a file when the ScoreManager is destroyed.
ScoreManager::~ScoreManager() {
    SaveTopScores(); // Save the top scores to file
}

// Saves the top scores to a file. If the current score is in the top 5, it is added.
void ScoreManager::SaveTopScores(const std::string& filename) {
    // Find the correct position to insert the current score in descending order
    const auto it = std::lower_bound(topScores.begin(), topScores.end(), currentScore, std::greater<>());

    // Insert the score if it's in the top 5 or if there are fewer than 5 scores
    if (it != topScores.end() || topScores.size() < 5) {
        topScores.insert(it, currentScore); // Insert the current score
        // Ensure only the top 5 scores are kept
        if (topScores.size() > 5) {
            topScores.resize(5); // Trim the list to only the top 5 scores
        }
    }

    try {
        // Open the file for writing, truncating any existing content
        std::ofstream fileStream(filename, std::ios::out | std::ios::trunc);
        if (!fileStream) {
            throw std::ios_base::failure("Unable to open file for writing: " + filename);
        }

        // Write the top scores to the file
        for (const auto& score : topScores) {
            fileStream << score << std::endl; // Write each score on a new line
        }

    } catch (const std::exception& e) {
        // Print an error message if the file operation fails
        std::cerr << "Error saving top scores: " << e.what() << std::endl;
    }
}

void ScoreManager::LoadTopScores(const std::string& filename) {
    try {
        std::ifstream fileStream(filename, std::ios::in);
        if (!fileStream) {
            throw std::ios_base::failure("Unable to open file for reading: " + filename);
        }

        unsigned long score;
        while (fileStream >> score) {
            topScores.push_back(score);
            if (topScores.size() >= 5)
                break;
        }

        // Sort the scores in descending order
        std::sort(topScores.begin(), topScores.end(), std::greater<>());

    } catch (const std::exception& e) {
        std::cerr << "Error loading top scores: " << e.what() << std::endl;
    }
}
