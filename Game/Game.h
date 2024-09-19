//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_GAME_H
#define PACMANV2_GAME_H


namespace Game {
class PacmanGame {
    bool running;

private:
    static void Cleanup();

public:
    PacmanGame();
    void Run() const;
    void Stop() { running = false; }
    ~PacmanGame() = default;
};
}

extern Game::PacmanGame game;

#endif //PACMANV2_GAME_H
