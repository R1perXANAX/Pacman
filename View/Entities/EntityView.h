//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_ENTITYVIEW_H
#define PACMANV2_ENTITYVIEW_H
#include "../GameWindow.h"
#include "../../Logic/ObserverPattern/IObserver.h"
#include "Animation.h"


namespace View {
template <typename T>
class EntityView : public IObserver {
protected:
    std::weak_ptr<T> attachedEntity;
    Animation anim;

public:
    virtual void Draw() = 0;
    void Update(const SubjectEvent& event) override;

    EntityView(std::shared_ptr<T> model)
        : attachedEntity(model) {
    };
    ~EntityView() override = default ;
};

template <typename T>
void EntityView<T>::Update(const SubjectEvent& event) {
    switch (event) {
    case SubjectEvent::Draw:
        Draw();
        break;
    default:
        break;
    }
}
}

#endif //PACMANV2_ENTITYVIEW_H
