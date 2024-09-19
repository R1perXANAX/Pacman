//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_STOPWATCH_H
#define PACMANV2_STOPWATCH_H

#include <chrono>

namespace Logic {
class Stopwatch {
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& GetInstance(double maxFPS = 60.0);
    void Start();
    void Stop();
    void Reset();
    double Elapsed() const;
    void UpdateDeltaTime();
    static float GetDeltaTime();

private:
    Stopwatch(double maxFPS);

    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point lastTime;
    bool running;
    double maxFPS;
    static float deltaTime;
};
}


#endif //PACMANV2_STOPWATCH_H
