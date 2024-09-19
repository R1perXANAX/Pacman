//
// Created by R1perXNX on 7/3/2024.
//

#include "Animation.h"

using namespace View;

Animation::Animation()
    : switchTime(0.1f), totalTime(0.0f), currentFrame(0), running(false), currentAnimation(AnimationType::Up) {
}

void Animation::AddFrame(const AnimationType animationType, const sf::IntRect& frame) {
    animations[animationType].push_back(frame);
}

void Animation::SetSwitchTime(const float time) {
    switchTime = time;
}

void Animation::SetAnimation(AnimationType animationType) {
    if (animations.find(animationType) != animations.end()) {
        currentAnimation = animationType;
    }
}

void Animation::Update(const float deltaTime) {
    if (!running)
        return;

    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentFrame = (currentFrame + 1) % animations[currentAnimation].size();
    }
}

void Animation::Start() {
    running = true;
    Reset();
}

void Animation::Stop() {
    running = false;
    Reset();
}

void Animation::Reset() {
    totalTime = 0.0f;
    currentFrame = 0;
}

const sf::IntRect& Animation::GetCurrentFrame() const {
    return animations.at(currentAnimation)[currentFrame];
}

bool Animation::IsRunning() const {
    return running;
}
