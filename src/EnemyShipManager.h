#ifndef ENEMYSHIPMANAGER_H
#define ENEMYSHIPMANAGER_H

#include <random>
#include <vector>

#include "SDL.h"

#include "Direction.h"
#include "EnemyShip.h"
#include "missile.h"

class EnemyShipManager {
public:
    // constructor
    EnemyShipManager(int grid_x, int grid_y);
    
    // methods
    void Update();
    void CreateShips();
    void MoveShips();
    int ProcessShooterMissiles(const std::vector<Missile*> & missiles);
    void UpdateMissileTS();

    // member variables
    std::vector<std::vector<EnemyShip*>> ships; // cols x rows
    float speed = 0.1f;
    float missileWaitTime = 1000; // in milliseconds
    std::vector<Missile*> missiles;
    bool enemyWin = false;
    
private:
    // private methods
    void UpdateRefPoint();
    void ShootMissile();
    void UpdateMissiles();
    void InitializeState();
    
    // private member variables
    float ref_x;
    float ref_y;
    int ref_x_max;
    int ref_y_max;
    Direction direction;
    
    const int rows = 4;
    const int cols = 10;
    
    const int ship_w = 4;
    const int ship_h = 2;
    
    const int screen_buffer = 1;
    const int ship_buffer = 2;
    
    const int shooter_h = 5;
    
    const int grid_x;
    const int grid_y;
    
    const float missileSpeed = 1.0f;
    Uint32 missile_ts;
    std::random_device dev;
    std::mt19937 engine;    
};

#endif /* ENEMYSHIPMANAGER_H */
