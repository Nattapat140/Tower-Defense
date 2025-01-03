#pragma once
#ifndef TWODICEENEMY_HPP
#define TWODICEENEMY_HPP
#include "Enemy.hpp"
class Turret;

class TWODICEENEMY : public Enemy {
public:
    TWODICEENEMY(int x, int y);
    // override from enemy.hpp and dice_enemy.hpp
    void Hit(float damage)override;
    void OnExplode()override;
};
#endif // TWODICEENEMY_HPP