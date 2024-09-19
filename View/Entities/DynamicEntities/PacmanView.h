//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_PACMANVIEW_H
#define PACMANV2_PACMANVIEW_H
#include "../EntityView.h"
#include "../../../Logic/Entities/DynamicEntities/PacmanEntity.h"

namespace View {
class PacmanView final : public EntityView<Logic::PacmanEntity> {
private:
    sf::Texture texture;
    sf::IntRect textureRect;
    sf::Sprite sprite;

public:
    PacmanView(const std::shared_ptr<Logic::PacmanEntity>& model);

    void Draw() override;

    ~PacmanView() override = default;
};
}

#endif //PACMANV2_PACMANVIEW_H
