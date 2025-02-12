#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/spaceship.png");
    position = {
        static_cast<float>(GetScreenWidth() - image.width) / 2,
        static_cast<float>(GetScreenHeight() - image.width)};
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}
void Spaceship::Draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}
void Spaceship::FireLaser()
{
    Laser laser = Laser({position.x + image.width / 2 - 3, position.y}, 10);
    lasers.push_back(laser);
}
void Spaceship::MoveRight()
{
    position.x += 5;
    if (position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
    else if (position.x < 0)
    {
        position.x = 0;
    }
}
void Spaceship::MoveLeft()
{
    position.x -= 5;
    if (position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
    else if (position.x < 0)
    {
        position.x = 0;
    }
}