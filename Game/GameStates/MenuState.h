//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_MENUSTATE_H
#define PACMANV2_MENUSTATE_H
#include "IGameState.h"
#include "../../Global.h"
#include <array>

namespace Game {
class MenuState final : public IGameState {
    sf::Font font;
    sf::Font font1;
    sf::Text text;
    sf::Text credits;
    sf::Vector2f buttonSize;
    sf::Vector2f buttonPosition;
    std::array<sf::RectangleShape, 3> rects;
    std::array<sf::Text, 3> labels;
    sf::Text topScoreLabels;
    std::vector<unsigned long> topScores;
    std::vector<sf::Text> scoreTexts;
    bool showCredits{false};
    unsigned int buttonPadding{};

    // Dropdown menu members
    sf::RectangleShape dropdownBox;
    sf::Text selectedMapText;
    std::vector<sf::Text> mapOptions;
    std::vector<sf::RectangleShape> mapOptionBoxes;
    bool isDropdownOpen = false;
    int selectedMapIndex = -1;

public:
    MenuState() = default;
    void HandleTransition(GameStateType to) override;
    void Enter() override;
    void Exit() override;
    void Update() override;
    void HandleMouseClick() override;
    void HandleInput(sf::Event& event) override;
    void Draw() override;

    inline GameStateType GetType() override {
        return GameStateType::MainMenu;
    }

    ~MenuState() override = default;
};
}

#endif //PACMANV2_MENUSTATE_H