//
// Created by R1perXNX on 7/1/2024.
//
#ifndef PACMANV2_ISUBJECT_H
#define PACMANV2_ISUBJECT_H
#include <memory>
#include "IObserver.h"

class ISubject {
public:
    virtual ~ISubject() {
    };
    virtual void Attach(std::shared_ptr<IObserver>) = 0;
    virtual void Detach(std::shared_ptr<IObserver>) = 0;
    virtual void Notify(const SubjectEvent& event) = 0;
};
#endif //PACMANV2_ISUBJECT_H
