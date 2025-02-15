#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/spaceship.png");
    position = {
        static_cast<float>(GetScreenWidth() - image.width) / 2,
        static_cast<float>(GetScreenHeight() - image.height - 100)};
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
Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
void Spaceship::Reset()
{
    position = {
        static_cast<float>(GetScreenWidth() - image.width) / 2,
        static_cast<float>(GetScreenHeight() - image.width - 100)};
    lasers.clear();
}
void Spaceship::MoveRight()
{
    position.x += 5;
    if (position.x > GetScreenWidth() - image.width - 25)
    {
        position.x = GetScreenWidth() - image.width - 25;
    }
    else if (position.x < 25)
    {
        position.x = 25;
    }
}
void Spaceship::MoveLeft()
{
    position.x -= 5;
    if (position.x > GetScreenWidth() - image.width - 25)
    {
        position.x = GetScreenWidth() - image.width - 25;
    }
    else if (position.x < 25)
    {
        position.x = 25;
    }
}