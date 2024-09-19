//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_ANIMATION_H
#define PACMANV2_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <vector>

namespace View {
enum class AnimationType {
    Up,
    Down,
    Left,
    Right
};

class Animation {
private:
    std::map<AnimationType, std::vector<sf::IntRect>> animations;
    AnimationType currentAnimation;
    float switchTime;
    float totalTime;
    size_t currentFrame;
    bool running;

public:
    Animation();

    void AddFrame(AnimationType animationType, const sf::IntRect& frame);
    void SetSwitchTime(float time);
    void SetAnimation(AnimationType animationType);
    void Update(float deltaTime);
    void Start();
    void Stop();
    void Reset();
    const sf::IntRect& GetCurrentFrame() const;
    bool IsRunning() const;

};
}

#endif //PACMANV2_ANIMATION_H
