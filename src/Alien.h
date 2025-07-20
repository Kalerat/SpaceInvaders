#pragma once

#include "Laser.h"

#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

class Alien {
public:
    Alien(Vector2 position, int type);
    
    std::vector<std::unique_ptr<Laser>> lasers;
    
    void Draw();
    void Update(int direction);
    int getType() const { return type; }
    Vector2 getPosition() const { return position; }
    int getTextureWidth() const { return texture[type].width; }
    Rectangle GetBounds() const { return { position.x, position.y, static_cast<float>(texture[type].width), static_cast<float>(texture[type].height) }; }

    private:
    static Texture2D texture[3];
    Vector2 position;
    int type;
    static bool loaded;
    int lastDirection = 1;

    void loadTextures();
    void shootLaser();
};