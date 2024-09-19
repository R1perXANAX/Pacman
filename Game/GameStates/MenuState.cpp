//
// Created by R1perXNX on 7/1/2024.
//

#include "MenuState.h"

#include "../ScoreManager.h"
#include "../GameStateManager.h"
#include "LevelState.h"
#include "../Game.h"
#include "../SoundManager.h"
#include "../../View/GameWindow.h"

using namespace Game;
using namespace View;

void MenuState::HandleTransition(const GameStateType to) {
    if (to == GameStateType::Level) {
        GGameStateManager->PushState(std::make_unique<LevelState>());
    }
}

void MenuState::Enter() {
    try {
        // Load fonts with error handling
        if (!font.loadFromFile("../Resources/RetroGraphics.ttf")) {
            throw std::runtime_error("Failed to load font: ../Resources/RetroGraphics.ttf");
        }

        if (!font1.loadFromFile("../Resources/arial.ttf")) {
            throw std::runtime_error("Failed to load font: ../Resources/arial.ttf");
        }

        // Load background sound with error handling
        if (gSoundManager) {
            gSoundManager->LoadBackgroundSound("../Resources/pino.wav");
        }

    } catch (const std::exception& e) {
        std::cerr << "Error in MenuState::Enter(): " << e.what() << std::endl;
        // Handle error, for example, by setting a fallback state or exiting the application
        game.Stop();
        return; // Early return if there's a critical error
    }

    // Continue with UI setup if resources were loaded successfully
    text.setFont(font);
    text.setString(sf::String("PACMAN MAIN MENU:"));
    text.setCharacterSize(36);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);

    text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 2 * SCREEN_MULT);
    credits.setFont(font1);
    credits.setString(sf::String(L"Just Me.\n\n Press ESC"));
    credits.setCharacterSize(24);
    textRect = credits.getLocalBounds();
    credits.setOrigin(textRect.left + textRect.width / 2.0f,
                      textRect.top + textRect.height / 2.0f);
    credits.setPosition(SCREEN_WIDTH / 2, 100);
    buttonSize = sf::Vector2f(5.0f * SCREEN_MULT, .5f * SCREEN_MULT);
    buttonPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_MULT);
    buttonPadding = 4; // 4px.
    std::string str[3];
    str[0] = "PLAY";
    str[1] = "CREDITS";
    str[2] = "EXIT";

    for (int i = 0; i < 3; ++i) {
        sf::Vector2f buttonPos(this->buttonPosition.x, this->buttonPosition.y +
                                                       (i * (buttonSize.y + buttonPadding)));
        rects[i].setSize(buttonSize);
        rects[i].setFillColor(sf::Color::Blue);
        rects[i].setOrigin(buttonSize.x / 2.0f,
                           buttonSize.y / 2.0f);
        rects[i].setPosition(buttonPos);
        labels[i].setFont(font);
        labels[i].setString(sf::String(str[i]));
        labels[i].setCharacterSize(20);
        sf::FloatRect rect = labels[i].getLocalBounds();
        labels[i].setOrigin(rect.left + rect.width / 2.0f,
                            rect.top + rect.height / 2.0f);
        labels[i].setPosition(buttonPos);
    }

    topScoreLabels.setFont(font);
    topScoreLabels.setString("TOP SCORES:");
    topScoreLabels.setCharacterSize(24);
    topScoreLabels.setPosition(10, 10);

    topScores = gScoreManager->GetTopScores();

    for (size_t i = 0; i < topScores.size(); ++i) {
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString(std::to_string(topScores[i]));
        scoreText.setCharacterSize(20);

        textRect = scoreText.getLocalBounds();
        scoreText.setOrigin(textRect.left + textRect.width / 2.0f,
                            textRect.top + textRect.height / 2.0f);
        scoreText.setPosition(60, 60 + i * 20);

        scoreTexts.push_back(scoreText);
    }

    // Dropdown menu setup
    dropdownBox.setSize(sf::Vector2f(200, 40));
    dropdownBox.setFillColor(sf::Color::Transparent);
    dropdownBox.setOrigin(dropdownBox.getSize().x / 2.0f, dropdownBox.getSize().y / 2.0f);
    dropdownBox.setPosition(SCREEN_WIDTH - 150, 50);

    selectedMapText.setFont(font);
    selectedMapText.setCharacterSize(20);
    selectedMapText.setString("Select Map");
    textRect = selectedMapText.getLocalBounds();
    selectedMapText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    selectedMapText.setPosition(dropdownBox.getPosition());

    // Get the total number of maps
    int totalMaps = MapManager::GetInstance().GetTotalMaps();
    for (int i = 0; i < totalMaps; ++i) {
        sf::Text mapOption;
        mapOption.setFont(font);
        mapOption.setString("Map " + std::to_string(i + 1));
        mapOption.setCharacterSize(20);
        mapOption.setPosition(dropdownBox.getPosition().x,
                              dropdownBox.getPosition().y + static_cast<float>(i + 1) * 40);
        mapOptions.push_back(mapOption);

        sf::RectangleShape optionBox;
        optionBox.setSize(dropdownBox.getSize());
        optionBox.setFillColor(sf::Color::Transparent);
        optionBox.setPosition(dropdownBox.getPosition().x,
                              dropdownBox.getPosition().y + static_cast<float>(i + 1) * 40);
        mapOptionBoxes.push_back(optionBox);
    }

}

void MenuState::Exit() {
    if (gSoundManager)
        gSoundManager->StopBackground();
}

void MenuState::Update() {
    if (gSoundManager)
        gSoundManager->PlayBackground();
}

void MenuState::HandleMouseClick() {
    const sf::Vector2i mousePosition = sf::Mouse::getPosition(GameWindow::GetInstance().GetWindow());
    const float halfX = buttonSize.x / 2.0f;
    const float halfY = buttonSize.y / 2.0f;

    for (int i = 0; i < 3; ++i) {
        if (static_cast<float>(mousePosition.x) >= rects[i].getPosition().x - halfX &&
            static_cast<float>(mousePosition.x) <= rects[i].getPosition().x + halfX &&
            static_cast<float>(mousePosition.y) >= rects[i].getPosition().y - halfY &&
            static_cast<float>(mousePosition.y) <= rects[i].getPosition().y + halfY) {
            if (i == 0) {
                HandleTransition(GameStateType::Level);
            } else if (i == 1) {
                showCredits = true;
            } else if (i == 2) {
                game.Stop();
            }
        }
    }

    if (static_cast<float>(mousePosition.x) >= dropdownBox.getPosition().x - dropdownBox.getSize().x / 2.0f &&
        static_cast<float>(mousePosition.x) <= dropdownBox.getPosition().x + dropdownBox.getSize().x / 2.0f &&
        static_cast<float>(mousePosition.y) >= dropdownBox.getPosition().y - dropdownBox.getSize().y / 2.0f &&
        static_cast<float>(mousePosition.y) <= dropdownBox.getPosition().y + dropdownBox.getSize().y / 2.0f) {
        isDropdownOpen = !isDropdownOpen;
    } else if (isDropdownOpen) {
        for (int i = 0; i < mapOptionBoxes.size(); ++i) {
            if (static_cast<float>(mousePosition.x) >= mapOptionBoxes[i].getPosition().x - mapOptionBoxes[i].getSize().x
                / 2.0f &&
                static_cast<float>(mousePosition.x) <= mapOptionBoxes[i].getPosition().x + mapOptionBoxes[i].getSize().x
                / 2.0f &&
                static_cast<float>(mousePosition.y) >= mapOptionBoxes[i].getPosition().y - mapOptionBoxes[i].getSize().y
                / 2.0f &&
                static_cast<float>(mousePosition.y) <= mapOptionBoxes[i].getPosition().y + mapOptionBoxes[i].getSize().y
                / 2.0f) {
                selectedMapIndex = i;
                MapManager::GetInstance().SetMap(i);
                selectedMapText.setString("Map " + std::to_string(i + 1));
                isDropdownOpen = false;
                break;
            }
        }
    }
}


void MenuState::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            HandleMouseClick();
        }
    }
    if (event.key.code == sf::Keyboard::Escape) {
        showCredits = false;
    }
    if (event.type == sf::Event::Closed) {
        game.Stop();
    }
}

void MenuState::Draw() {
    if (!showCredits) {
        GameWindow::GetInstance().GetWindow().clear(sf::Color::Black);

        GameWindow::GetInstance().GetWindow().draw(topScoreLabels);

        for (auto& score_text : scoreTexts) {
            GameWindow::GetInstance().GetWindow().draw(score_text);
        }

        for (int i = 0; i < 3; ++i) {
            GameWindow::GetInstance().GetWindow().draw(rects[i]);
            GameWindow::GetInstance().GetWindow().draw(labels[i]);
        }

        GameWindow::GetInstance().GetWindow().draw(dropdownBox);
        GameWindow::GetInstance().GetWindow().draw(selectedMapText);

        if (isDropdownOpen) {
            for (auto& optionBox : mapOptionBoxes) {
                GameWindow::GetInstance().GetWindow().draw(optionBox);
            }
            for (auto& optionText : mapOptions) {
                GameWindow::GetInstance().GetWindow().draw(optionText);
            }
        }

        GameWindow::GetInstance().GetWindow().draw(text);
    } else {
        GameWindow::GetInstance().GetWindow().clear(sf::Color::Black);
        GameWindow::GetInstance().GetWindow().draw(credits);
    }
    GameWindow::GetInstance().GetWindow().display();
}