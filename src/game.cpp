#include "game.hpp"
#include <iostream>

Game::Game()
{
    obstacles = GenerateObstacles();
    aliens = GenerateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Draw()
{
    spaceship.Draw();
    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }
    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
    for (auto &alien : aliens)
    {
        alien.Draw();
    }
    for (auto &alienLaser : alienLasers)
    {
        alienLaser.Draw();
    }
}

void Game::Update()
{
    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }
    MoveAliens();
    AlienShootLaser();
    for (auto &laser : alienLasers)
    {
        laser.Update();
    }
    DeleteInactiveLasers();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (it->IsOutOfScreen())
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (it->IsOutOfScreen())
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::GenerateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (float)(GetScreenWidth() - (4 * obstacleWidth)) / 5; // LARGHEZZA TOTALE - LARGHEZZA TOTALE DEGLI OSTACOLI DIVISO IL NUMERO DEI GAP DA CREARE

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}

std::vector<Alien> Game::GenerateAliens()
{
    float cell_size = 55; // PIXEL
    float center_x = 75;
    float center_y = 110;
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }
            float x = center_x + column * cell_size;
            float y = center_y + row * cell_size;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.GetType() - 1].width > GetScreenWidth())
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 0)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int y)
{
    for (auto &alien : aliens)
    {
        alien.position.y += y;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.GetType() - 1].width / 2, alien.position.y + alien.alienImages[alien.GetType() - 1].height}, -6));
        timeLastAlienFired = GetTime();
    }
}
