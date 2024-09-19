//
// Created by R1perXNX on 7/1/2024.
//

#include "GameWindow.h"
using namespace View;

GameWindow::GameWindow(int ScreenWidth, int ScreenHeight)
    : gameWindow(sf::VideoMode(ScreenWidth, ScreenHeight), "PacMan") {
    if (!font.loadFromFile("../Resources/arial.ttf")) {
        std::cerr << "Loading font failed";
    }
}
