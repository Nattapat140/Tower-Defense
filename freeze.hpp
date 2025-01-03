#pragma once
#ifndef FREEZE_HPP
#define FREEZE_HPP
#include "Turret.hpp"

class FREEZE : public Turret {
public:
    static const int Price;
    FREEZE(float x, float y);
    void CreateBullet() override;
    char get_turret_id() override;
};
#endif // FREEZE_HPP
