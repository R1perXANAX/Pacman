#include "StopWatch.h"
#include <thread>

using namespace Logic;

float Stopwatch::deltaTime = 0.0;

Stopwatch::Stopwatch(const double maxFPS)
    : running(false), maxFPS(maxFPS) {
}

Stopwatch& Stopwatch::GetInstance(const double maxFPS) {
    static Stopwatch instance(maxFPS);
    return instance;
}

void Stopwatch::Start() {
    if (!running) {
        startTime = std::chrono::high_resolution_clock::now();
        lastTime = startTime;
        running = true;
    }
}

void Stopwatch::Stop() {
    if (running) {
        running = false;
    }
}

void Stopwatch::Reset() {
    running = false;
}

double Stopwatch::Elapsed() const {
    if (running) {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(currentTime - startTime).count();
    }
    return 0.0;
}

void Stopwatch::UpdateDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

    // Cap the frame rate
    const double minFrameTime = 1.0 / maxFPS;
    if (deltaTime < minFrameTime) {
        const auto sleepTime = std::chrono::duration<double>(minFrameTime - deltaTime);
        std::this_thread::sleep_for(sleepTime);
        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
    }
    lastTime = currentTime;
}

float Stopwatch::GetDeltaTime() {
    return deltaTime;
}
