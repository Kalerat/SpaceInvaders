#pragma once

#include "Block.h"
#include <raylib.h>
#include <vector>


class Obstacle {
public:
    Obstacle(Vector2 position, Color color = YELLOW);
    ~Obstacle();

    void Draw();
    void Update();
    
    static std::vector<std::vector<int>> grid; // 2D vector to represent the grid of blocks
    
private:
    Vector2 position;
    Color color;
    std::vector<Block> blocks; // Vector to hold the blocks that make up the obstacle
};
