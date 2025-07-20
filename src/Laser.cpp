#include "Laser.h"

Laser::Laser(Vector2 position, float speed)
    : position(position), speed(speed), active(true) {
    // Constructor implementation
}

Laser::~Laser() {
    // Destructor implementation
}

void Laser::Update() {
    if (active) {
        position.y -= speed * GetFrameTime(); // Move the laser upwards
        if (position.y < 0) {
            active = false; // Deactivate the laser if it goes off-screen
        }
    }
}

void Laser::Draw() {
    if (active) {
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 5, 20, RED);
    }
}