#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void MoveRight();
    void MoveLeft();
    void Update();
    void Draw();
    void FireLaser();
    std::vector<Laser> lasers;
    Rectangle getRect();
    void Reset();

private:
    Texture2D image;
    Vector2 position;
};