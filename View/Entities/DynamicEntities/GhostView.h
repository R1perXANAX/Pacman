//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_GHOSTVIEW_H
#define PACMANV2_GHOSTVIEW_H
#include "../../../Logic/Entities/DynamicEntities/GhostEntity.h"
#include "../EntityView.h"

namespace View {
class GhostView final : public EntityView<Logic::GhostEntity> {
private:
    sf::Texture texture;
    sf::IntRect textureRect;
    sf::Sprite sprite;

public:
    GhostView(const std::shared_ptr<Logic::GhostEntity>& model);

    void Draw() override;

    ~GhostView() override = default;
};
}

#endif //PACMANV2_GHOSTVIEW_H
