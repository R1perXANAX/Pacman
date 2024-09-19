#include <iostream>

#include "Game/Game.h"
#include "Game/SoundManager.h"
#include "Game/ScoreManager.h"
#include "Game/GameStateManager.h"

Game::PacmanGame game;
std::unique_ptr<Game::GameStateManager> GGameStateManager;
std::shared_ptr<Game::ScoreManager> gScoreManager;
std::shared_ptr<Game::SoundManager> gSoundManager;

int main() {
    game.Run();
}
