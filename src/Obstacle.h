#pragma once

#include "Block.h"
#include <raylib.h>
#include <vector>


class Obstacle {
public:
    Obstacle(Vector2 position, Color color = YELLOW);
    
    std::vector<Block> blocks; // Vector to hold the blocks that make up the obstacle

    void Draw();
    void Update();
    Rectangle GetBounds() const { 
        return { position.x, position.y, static_cast<float>(BLOCK_SIZE * grid[0].size()), static_cast<float>(BLOCK_SIZE * grid.size()) }; 
    }
    
    static std::vector<std::vector<int>> grid; // 2D vector to represent the grid of blocks

private:
    Vector2 position;
    Color color;
};
