#pragma once
#include <vector>
#include "block.hpp"

class Obstacle
{
public:
    Obstacle(Vector2 position);
    ~Obstacle();
    void Draw();
    void Update();
    void AddBlock();
    void RemoveBlock();
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;

private:
    Vector2 position;
};