//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_ENTITYMODEL_H
#define PACMANV2_ENTITYMODEL_H

#include "../ObserverPattern/ISubject.h"
#include "../Vector2D.h"
#include "../ObserverPattern/IObserver.h"
#include <vector>

namespace Logic {
enum EntityType {
    Pacman,
    Coin,
    Ghost,
    Fruit,
    Wall,
    Banana,
    GhostSetup
};

enum Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

class EntityModel : public ISubject {
protected:
    EntityType type;
    Vector2f position;
    Vector2f origin;
    Vector2f spawnPos;
    Vector2f size{1.f, 1.f};
    std::vector<std::shared_ptr<IObserver>> observers;

public:
    void Attach(std::shared_ptr<IObserver> observer) override;
    void Detach(std::shared_ptr<IObserver> observer) override;
    void Notify(const SubjectEvent& event) override;

    //Getters
    EntityType GetType() const { return type; }
    Vector2f GetPosition() const;
    Vector2f GetOrigin() const;
    Vector2f GetSize() const { return size; }

    //Setters
    void SetPosition(const Vector2f& newPosition);
    void SetPosition(float x, float y) { SetPosition(Vector2f(x, y)); }
    void SetOrigin(const Vector2f& newOrigin);
    void SetOrigin(float x, float y) { SetOrigin(Vector2f(x, y)); }

    void CenterObject(Direction direction);
    virtual void Spawn() = 0;
    virtual bool IsAvailable() { return false; }

    virtual void SetAvailable(bool available) {
    }

    EntityModel(EntityType type, const Vector2f& position);
    ~EntityModel() override;

};
}

#endif //PACMANV2_ENTITYMODEL_H