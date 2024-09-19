//
// Created by R1perXNX on 7/3/2024.
//

#include "PacmanView.h"
#include "../Animation.h"
#include "../../../Logic/Camera.h"
#include "../../../Logic/StopWatch.h"

using namespace Logic;
using namespace View;

PacmanView::PacmanView(const std::shared_ptr<PacmanEntity>& model)
    : EntityView(model) {
    if (!texture.loadFromFile("../Resources/Sprites.png")) {
        std::cerr << "Failed loading texture for Pacman";
    }

    sprite.setTexture(texture);
    // Add frames to the animation
    anim.AddFrame(AnimationType::Up, sf::IntRect(845, 495, 50, 50));
    anim.AddFrame(AnimationType::Up, sf::IntRect(845, 545, 50, 50));
    anim.AddFrame(AnimationType::Down, sf::IntRect(845, 195, 50, 50));
    anim.AddFrame(AnimationType::Down, sf::IntRect(845, 245, 50, 50));
    anim.AddFrame(AnimationType::Left, sf::IntRect(845, 345, 50, 50));
    anim.AddFrame(AnimationType::Left, sf::IntRect(845, 395, 50, 50));
    anim.AddFrame(AnimationType::Right, sf::IntRect(845, 45, 50, 50));
    anim.AddFrame(AnimationType::Right, sf::IntRect(845, 95, 50, 50));
    anim.SetSwitchTime(0.1f); // Set the time to switch frames
}

void PacmanView::Draw() {
    const auto tempModel = attachedEntity.lock();
    if (!tempModel || !tempModel->IsAlive())
        return;

    const auto deltaTime = Stopwatch::GetDeltaTime();

    if (!tempModel->CanMove() || tempModel->IsSleeping()) {
        textureRect = sf::IntRect(845, 345, 50, 50); // Stopped frame
        anim.Stop();                                 // Stop animation when not moving
    } else {
        if (!anim.IsRunning()) {
            anim.Start(); // Start animation when moving
        }
        switch (tempModel->GetDirection()) {
        case Direction::None:
            textureRect = sf::IntRect(845, 495, 50, 50); // None direction frame
            anim.Stop();
            break;
        case Direction::Up:
            anim.SetAnimation(AnimationType::Up);
            anim.Update(deltaTime);
            break;
        case Direction::Down:
            anim.SetAnimation(AnimationType::Down);
            anim.Update(deltaTime);
            break;
        case Direction::Left:
            anim.SetAnimation(AnimationType::Left);
            anim.Update(deltaTime);
            break;
        case Direction::Right:
            anim.SetAnimation(AnimationType::Right);
            anim.Update(deltaTime);
            break;
        }
        textureRect = anim.GetCurrentFrame();
    }

    sprite.setTextureRect(textureRect);
    auto size = tempModel->GetSize();
    Camera::GetInstance().Scale(size);
    sprite.setScale(size.x / textureRect.width, size.y / textureRect.height);
    Vector2f origin;
    Camera::GetInstance().World2Screen(tempModel->GetOrigin(), origin);

    sprite.setOrigin(textureRect.width / 2, textureRect.height / 2);
    sprite.setPosition({origin.x, origin.y});

    GameWindow::GetInstance().GetWindow().draw(sprite);

}
