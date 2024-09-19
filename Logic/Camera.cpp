//
// Created by R1perXNX on 7/1/2024.
//

#include "Camera.h"
using namespace Logic;
/**
 * @brief Scales a vector based on the screen size.
 * @param Amount The amount to be scaled
 */
void Camera::Scale(Vector2f& Amount) const {
    Amount.x *= static_cast<float>(screenSize.x) / worldSize.x;
    Amount.y *= static_cast<float>(screenSize.y) / worldSize.y;
}

void Camera::Scale(float& x, float& y) const {
    x *= static_cast<float>(screenSize.x) / worldSize.x;
    y *= static_cast<float>(screenSize.y) / worldSize.y;
}

/**
* @brief Converts world coordinates to screen coordinates.
* @param WorldCoordinates World coordinates to be transformed.
* @param ScreenCoordinates Reference to store the converted screen coordinates.
*/
void Camera::World2Screen(const Vector2f& WorldCoordinates, Vector2f& ScreenCoordinates) const {
    const auto cell_size = GetCellSize();
    ScreenCoordinates.x = WorldCoordinates.x * cell_size.x;
    ScreenCoordinates.y = WorldCoordinates.y * cell_size.y;
}
