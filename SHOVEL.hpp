#pragma once
#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "Turret.hpp"

class SHOVEL : public Turret {
public:
    static const int Price;
    SHOVEL(float x, float y);
    void CreateBullet() override;
    char get_turret_id() override;
};
#endif // SHOVEL_HPP
