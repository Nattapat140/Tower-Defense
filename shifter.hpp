#pragma once
#ifndef SHIFTER_HPP
#define SHIFTER_HPP
#include "Turret.hpp"

class SHIFTER : public Turret {
public:
    static const int Price;
    SHIFTER(float x, float y);
    void CreateBullet() override;
    char get_turret_id() override;
};
#endif // SHIFTER_HPP
