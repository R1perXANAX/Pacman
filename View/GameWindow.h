//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANFINAL_GAMEWINDOW_H
#define PACMANFINAL_GAMEWINDOW_H

#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Global.h"
/**
 * @file GameWindow.h
 * @brief Class for managing the game window and its resources.
 *
 * GameWindow is responsible for creating and handling the main window of the game.
 * It encapsulates an SFML RenderWindow and a font resource, providing access to these
 * for rendering game elements and text.
 *
 * Member Variables:
 *   - m_window: The SFML RenderWindow used for displaying game content.
 *   - m_font: The SFML Font used for rendering text.
 *
 * Usage:
 *   - Create an instance of GameWindow with specified screen dimensions.
 *   - Use get_window() to access the SFML RenderWindow for drawing operations.
 *   - Use get_font() to access the loaded font for text rendering.
 *
 * Example:
 *   GameWindow gameWindow(800, 600);
 *   sf::RenderWindow& window = gameWindow.get_window();
 *   sf::Font& font = gameWindow.get_font();
 *   Use window and font for rendering
 */

namespace View {
class GameWindow {
private:
    sf::RenderWindow gameWindow;
    sf::Font font;

    GameWindow(int ScreenWidth, int ScreenHeight);

public:
    // Delete copy constructor and assignment operator
    GameWindow(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&) = delete;

    static GameWindow& GetInstance(int ScreenWidth = SCREEN_WIDTH, int ScreenHeight = SCREEN_HEIGHT) {
        static GameWindow instance(ScreenWidth, ScreenHeight);
        return instance;
    }

    /**
     * @brief Gets the SFML RenderWindow.
     * @return Reference to the SFML RenderWindow.
     */
    inline sf::RenderWindow& GetWindow() { return gameWindow; }

    /**
     * @brief Gets the SFML Font.
     * @return Reference to the SFML Font.
     */
    inline sf::Font& GetFont() { return font; };

    inline void SetFont(const std::string& FilePath) {
        if (!font.loadFromFile(FilePath)) {
            std::cerr << "Loading font failed";
        }
    };
};
}


#endif //PACMANFINAL_GAMEWINDOW_H
