//
// Created by R1perXNX on 7/3/2024.
//

#include "GhostView.h"
#include "../../../Logic/Camera.h"
#include "../../../Logic/StopWatch.h"

using namespace Logic;
using namespace View;

GhostView::GhostView(const std::shared_ptr<GhostEntity>& model)
    : EntityView(model) {
    if (!texture.loadFromFile("../Resources/Sprites.png")) {
        std::cerr << "Failed loading texture for Pacman";
    }

    sprite.setTexture(texture);
    // Add frames to the animation
    anim.AddFrame(AnimationType::Up, sf::IntRect(650, 295, 50, 50));
    anim.AddFrame(AnimationType::Up, sf::IntRect(650, 345, 50, 50));
    anim.AddFrame(AnimationType::Down, sf::IntRect(650, 195, 50, 50));
    anim.AddFrame(AnimationType::Down, sf::IntRect(650, 245, 50, 50));
    anim.AddFrame(AnimationType::Left, sf::IntRect(650, 195, 50, 50));
    anim.AddFrame(AnimationType::Left, sf::IntRect(650, 245, 50, 50));
    anim.AddFrame(AnimationType::Right, sf::IntRect(650, 0, 50, 50));
    anim.AddFrame(AnimationType::Right, sf::IntRect(650, 50, 50, 50));
    anim.SetSwitchTime(0.1f); // Set the time to switch frames

}

void GhostView::Draw() {
    auto tempModel = attachedEntity.lock();
    if (!tempModel || !tempModel->IsAlive())
        return;

    const auto deltaTime = Stopwatch::GetDeltaTime();

    if (tempModel->GetStateType() == PlayerStateType::GhostFearing) {
        textureRect = sf::IntRect(0, 595, 50, 50); // Stopped frame

    } else {
        if (!anim.IsRunning()) {
            anim.Start(); // Start animation when moving
        }
        switch (tempModel->GetDirection()) {
        case Direction::None:
            textureRect = sf::IntRect(650, 195, 50, 50); // None direction frame
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
