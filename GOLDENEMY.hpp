#pragma once
#ifndef GOLDENEMY_HPP
#define GOLDENEMY_HPP
#include "Enemy.hpp"

class GOLDENEMY : public Enemy {
public:
    GOLDENEMY(int x, int y);
    // override from enemy.hpp and dice_enemy.hpp
    void Hit(float damage)override;
    void OnExplode()override;
};
#endif // GOLDENEMY_HPP
