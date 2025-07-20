#include "SpaceShip.h"
#include "Laser.h"

#include <raylib.h>
#include <stdexcept>

SpaceShip::SpaceShip() {
    // Load spaceship texture
    texture = LoadTexture("../resources/spaceship.png");
    if (texture.id == 0) {
        // Handle texture loading failure
        throw std::runtime_error("Failed to load spaceship texture");
    }
    // Initialize spaceship position and speed
    position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - texture.height - 20) };
    speed = 200.0f; // Set a default speed for the spaceship

}
SpaceShip::~SpaceShip() {
    // Unload spaceship texture
    UnloadTexture(texture);
}
void SpaceShip::Draw() {
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y) , WHITE);
    for (const auto& laser : lasers) {
        laser->Draw();
    }
}
void SpaceShip::Move(float deltaX, float deltaY) {
    position.x += deltaX * speed * GetFrameTime();
    position.y += deltaY * speed * GetFrameTime();
}
void SpaceShip::Shoot() {
    lasers.push_back(std::make_unique<Laser>(Vector2{ position.x + texture.width / 2, position.y }, 300.0f));
}

void SpaceShip::UpdateLasers() {
    for (auto it = lasers.begin(); it != lasers.end();) {
        (*it)->Update();
        if (!(*it)->active) {
            it = lasers.erase(it); // Remove inactive lasers
        } else {
            ++it; // Move to the next laser
        }
    }
}