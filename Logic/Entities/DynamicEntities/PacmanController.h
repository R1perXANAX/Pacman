//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_PACMANCONTROLLER_H
#define PACMANV2_PACMANCONTROLLER_H

#include "PacmanEntity.h"


namespace Logic {
class PacmanController {
private:
    std::shared_ptr<PacmanEntity> pacman;

private:
    void Cornering() const;
    Direction CorrectDirection(Direction direction) const;
    void Collide() const;

public:
    PacmanController(const std::shared_ptr<PacmanEntity>& controller)
        : pacman(controller) {
    };
    void Update() const;
    std::shared_ptr<PacmanEntity> GetPacman() { return pacman; }
};
}

#endif //PACMANV2_PACMANCONTROLLER_H
