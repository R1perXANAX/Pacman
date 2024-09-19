//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_DYNAMICENTITYMODEL_H
#define PACMANV2_DYNAMICENTITYMODEL_H
#include "EntityModel.h"
#include <array>


namespace Logic {
class DynamicEntityModel : public EntityModel {
protected:
    float speed{2.f};
    Direction direction{Up};
    Direction nextDirection{None};

    static const std::array<Vector2f, 5> directionVectors;
    static const std::array<Direction, 5> oppositeDirections;

public:
    virtual void Move(float deltatime) = 0;
    virtual void Stop() = 0;
    virtual void Kill() = 0;


    inline Direction GetDirection() const { return direction; }
    static inline const Vector2f& GetDirectionVector(Direction direction) { return directionVectors[direction]; }
    inline Direction GetNextDirection() const { return nextDirection; }
    static inline Direction GetOppositeDirection(Direction direction) { return oppositeDirections[direction]; }
    inline bool IsNewDirection() const { return direction != nextDirection; }
    inline void SetNextDirection(Direction nextDirection) { this->nextDirection = nextDirection; }
    inline void SetDirection(Direction direction) { this->direction = direction; };
    inline void SetSpeed(float newSpeed) { speed = newSpeed; }
    DynamicEntityModel(EntityType type, const Vector2f& position, float speed, Direction direction);
    ~DynamicEntityModel() override = default;


};
}
#endif //PACMANV2_DYNAMICENTITYMODEL_H