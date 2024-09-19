//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_CAMERA_H
#define PACMANV2_CAMERA_H
#include "Vector2D.h"

namespace Logic {
class Camera {
    Vector2i screenSize;
    Vector2f worldSize;
    Vector2f cellSize{};


    Camera(const Vector2i& WorldSize, const Vector2f& ScreenSize)
        : screenSize(ScreenSize), worldSize(WorldSize) {
    };
    Camera() = default;

public:
    /**
     * @brief Gets the size of a cell in the world.
     * @return Size of a cell in the world in game units.
     */
    [[nodiscard]] inline Vector2d GetCellSize() const {
        return {static_cast<double>(screenSize.x / worldSize.x), static_cast<double>(screenSize.y / worldSize.y)};
    }


    void Scale(Vector2f& Amount) const;
    void Scale(float& x, float& y) const;
    // Project world coordinates to screen coordinates
    void World2Screen(const Vector2f& WorldCoordinates, Vector2f& ScreenCoordinates) const;

    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }

    static Camera& GetInstance(const Vector2i& WorldSize, const Vector2f& ScreenSize) {
        static Camera instance(WorldSize, ScreenSize);
        return instance;
    }

    // Set world size
    static void SetWorldSize(const Vector2f& WorldSize) {
        GetInstance().worldSize = WorldSize;
    }

    // Set screen size
    static void SetScreenSize(const Vector2i& ScreenSize) {
        GetInstance().screenSize = ScreenSize;
    }

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
};
}

#endif //PACMANV2_CAMERA_H
