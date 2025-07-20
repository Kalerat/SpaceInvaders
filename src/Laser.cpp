#include "Laser.h"
#include "SpaceInvaders.h"

Laser::Laser(Vector2 position, float speed)
    : position(position), speed(speed), active(true) {
    // Constructor implementation
}

Laser::~Laser() {
    // Destructor implementation
}

void Laser::Update() {
    if (active) {
        position.y -= speed * GetFrameTime(); // Move the laser (positive speed = up, negative speed = down)
        // Check boundaries based on direction
        if (speed > 0 && position.y < UI_OFFSET_Y) {
            active = false; // Deactivate upward laser if it goes above the UI boundary
        }
        else if (speed < 0 && position.y > GetScreenHeight()) {
            active = false; // Deactivate downward laser if it goes below the screen
        }
    }
}

void Laser::Draw() {
    if (active) {
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 5, 20, RED);
    }
}