#include <cmath>
#include <iostream>

#include "shooter.h"

void Shooter::Update() {
    // We first capture the center cell before updating.
    SDL_Point prev_cell{ static_cast<int>(center_x), static_cast<int>(center_y)};
    
    UpdateCenter();
    
    // Capture the center's cell after updating.
    SDL_Point current_cell{ static_cast<int>(center_x), static_cast<int>(center_y)};

    // Update all of the body vector items if the shooter's
    // center has moved to a new cell (x-direction only).
    if (current_cell.x != prev_cell.x) {
        PopulateBody();
    }
    
    // If the shooter has any active missiles on the screen
    // update missile locations / active status
    if (missiles.size() > 0) {
        UpdateMissiles();
    }
}

void Shooter::UpdateCenter() {
    switch (direction) {
        case Direction::kLeft:
            if (center_x > xbuffer && moving) {
                center_x -= speed;
            }
            break;

        case Direction::kRight:
            if (center_x < grid_x - xbuffer && moving) {
                center_x += speed;
            }
            break;
        case Direction::kDown:
            // shooter will never enter kDown case
            break;
    }
}

void Shooter::PopulateBody() {
    body.clear();
    const int x = static_cast<int>(center_x);
    const int y = static_cast<int>(center_y);
    
    std::vector<int> x_rel = {-3, -2, -2, -1, -1,  0,  0,  0,  0,  1,  1,  2,  2,  3};
    std::vector<int> y_rel = { 0, -1,  0,  0,  2, -2, -1,  1,  2,  0,  2, -1,  0,  0};
    
    for (int i = 0; i < x_rel.size(); i++) {
        body.push_back(SDL_Point{x + x_rel[i], y + y_rel[i]});
    }
}

void Shooter::MoveBody() {
    if ( 0 == body.size() ) {
        // no body to move
    } else {
        // TODO:
    }
}

void Shooter::ShootMissile() {
    // two missiles from the shooter, left and right
    missiles.push_back(Missile(center_x-2, center_y-2 , missileSpeed, grid_y));
    missiles.push_back(Missile(center_x+2, center_y-2 , missileSpeed, grid_y));
}

void Shooter::UpdateMissiles() {
    for (auto &missile : missiles) {
        missile.UpdateLocation();
    }
    
    // Clean-up missile if not active
    missiles.erase(std::remove_if(missiles.begin(),
                                  missiles.end(),
                                  [](const Missile & missile) { return !missile.active; }),
                   missiles.end());
}

// Inefficient method to check if cell is occupied by snake.
bool Shooter::ShooterCell(int x, int y) {
    if (x == static_cast<int>(center_x) && y == static_cast<int>(center_y)) {
        return true;
    }
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}
