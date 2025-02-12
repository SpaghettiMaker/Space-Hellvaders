#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"

class Game
{
private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    void DeleteInactiveLasers();
    std::vector<Obstacle> GenerateObstacles();
    std::vector<Alien> aliens;
    std::vector<Alien> GenerateAliens();
    void MoveAliens();
    void MoveDownAliens(int y);
    int aliensDirection;
    std::vector<Laser> alienLasers;
    void AlienShootLaser();
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;

public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
};
