#pragma once

#include "Laser.h"

#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

class Alien {
public:
    Alien(Vector2 position, int type);
    void Draw();
    void Update(int direction);
    int getType() const { return type; }
    Vector2 getPosition() const { return position; }
    int getTextureWidth() const { return texture[type].width; }

    private:
    static Texture2D texture[3];
    Vector2 position;
    int type;
    static bool loaded;
    int lastDirection = 1;
    std::vector<std::unique_ptr<Laser>> lasers;

    void loadTextures();
    void shootLaser();
};