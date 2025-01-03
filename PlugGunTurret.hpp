#ifndef PLUGGUNTURRET_HPP
#define PLUGGUNTURRET_HPP
#include "Turret.hpp"

class PlugGunTurret : public Turret {
public:
    static const int Price;
    PlugGunTurret(float x, float y);
    void CreateBullet() override;
    char get_turret_id() override;
};
#endif // PLUGGUNTURRET_HPP
