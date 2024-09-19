//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_SCOREMANAGER_H
#define PACMANV2_SCOREMANAGER_H
#include <fstream>
#include <vector>
#include <memory>
#include "../Logic/ObserverPattern/IObserver.h"

namespace Game {
class ScoreManager final : public IObserver {
private:
    unsigned long currentScore{0};
    std::vector<unsigned long> topScores;
    unsigned short lifeLeft{3};
    unsigned int coinsCollected{0};
    unsigned int maxCoinsInThisLevel{0};
    int currentLevel{0};

public:
    ScoreManager();

    void SaveTopScores(const std::string& filename = "../Resources/score.txt");
    void LoadTopScores(const std::string& filename = "../Resources/score.txt");

    void Update(const SubjectEvent& event) override;

    inline unsigned long GetCurrentScore() const { return currentScore; }
    inline unsigned long GetTopScore() const { return topScores.empty() ? 0 : topScores[0]; }
    inline std::vector<unsigned long> GetTopScores() const { return topScores; }

    inline void Reset() {
        currentScore = 0;
        lifeLeft = 3;
        coinsCollected = 0;
    }

    inline void ResetLevels() { currentLevel = 0; }
    inline void SetMaxCoins(unsigned int maxCoins) { maxCoinsInThisLevel = maxCoins; }
    inline bool IsGameOver() const { return lifeLeft == 0; }
    inline unsigned short GetLifeLeft() const { return lifeLeft; }

    inline bool IsVictory() {
        if (coinsCollected == maxCoinsInThisLevel) {
            coinsCollected = 0;
            return true;
        } else {
            return false;
        }
    }

    inline void IncrementLevel() { currentLevel++; }
    inline unsigned int GetCurrentLevel() const { return currentLevel; }

    ~ScoreManager() override;
};
}

extern std::shared_ptr<Game::ScoreManager> gScoreManager;
#endif //PACMANV2_SCOREMANAGER_H
