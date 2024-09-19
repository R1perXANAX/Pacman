//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_IOBSERVER_H
#define PACMANV2_IOBSERVER_H
#include <iostream>
#include <string>

enum SubjectEvent {
    Draw,
    CoinEaten,
    FruitEaten,
    GhostEaten,
    PacmanDead
};

class IObserver {
public:
    virtual void Update(const SubjectEvent& event) = 0;
    virtual ~IObserver() = default;
};

#endif //PACMANV2_IOBSERVER_H
