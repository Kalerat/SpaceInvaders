#pragma once

#include "Laser.h"

#include <raylib.h>
#include <vector>
#include <memory>

class SpaceShip {
public:
    SpaceShip();
    ~SpaceShip();

    void Draw();
    void Move(float deltaX, float deltaY);
    void Shoot();
    void UpdateLasers(); // Update the state of all lasers

    private:
    Texture2D texture; // Texture for the spaceship
    Vector2 position; // Position of the spaceship
    float speed; // Speed of the spaceship
    std::vector<std::unique_ptr<Laser>> lasers; // List of lasers shot by the spaceship
};
