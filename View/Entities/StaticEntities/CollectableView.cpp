//
// Created by R1perXNX on 7/3/2024.
//

#include "CollectableView.h"
#include "../../../Logic/Camera.h"

using namespace Logic;
using namespace View;

WallView::WallView(const std::shared_ptr<WallEntity>& model)
    : EntityView(model) {
    auto size = model->GetSize();
    Camera::GetInstance().Scale(size);
    rectangleShape.setSize({size.x, size.y});

    Vector2f coords;
    Camera::GetInstance().World2Screen(model->GetPosition(), coords);
    rectangleShape.setPosition(coords.x, coords.y);
    rectangleShape.setFillColor(sf::Color::Blue);
}

void WallView::Draw() {
    GameWindow::GetInstance().GetWindow().draw(rectangleShape);
}

CoinView::CoinView(const std::shared_ptr<CoinEntity>& model)
    : EntityView(model) {
    Vector2f size{0.2, 0.2};
    Camera::GetInstance().Scale(size);
    circleShape.setRadius(size.x / 2);

    Vector2f coords;
    Camera::GetInstance().World2Screen(model->GetOrigin(), coords);
    circleShape.setPosition(coords.x, coords.y);
    circleShape.setFillColor(sf::Color::Yellow);
    circleShape.setOrigin(size.x / 2, size.x / 2);
}

void CoinView::Draw() {
    const auto tempModel = attachedEntity.lock();
    if (!tempModel || !tempModel->IsAvailable())
        return;

    GameWindow::GetInstance().GetWindow().draw(circleShape);
}

FruitView::FruitView(const std::shared_ptr<FruitEntity>& model)
    : EntityView(model) {
    if (!texture.loadFromFile("../Resources/Sprites.png")) {
        std::cerr << "Failed to load sprites\n";
        return;
    }

    switch (model->GetType()) {
    case Fruit:
        textureRect = sf::IntRect(595, 150, 50, 50);
        break;
    case Banana:
        textureRect = sf::IntRect(595, 250, 50, 50);
        break;
    default:
        break;
    }

    sprite.setTextureRect(textureRect);
    sprite.setTexture(texture);

    Vector2f size{1.f, 1.f};
    Camera::GetInstance().Scale(size);
    sprite.setScale(size.x / textureRect.width, size.y / textureRect.height);
    Vector2f coords;
    Camera::GetInstance().World2Screen(model->GetOrigin(), coords);
    sprite.setOrigin(textureRect.width / 2, textureRect.height / 2);
    sprite.setPosition({coords.x, coords.y});
}

void FruitView::Draw() {
    const auto tempModel = attachedEntity.lock();
    if (!tempModel || !tempModel->IsAvailable())
        return;

    GameWindow::GetInstance().GetWindow().draw(sprite);
}
