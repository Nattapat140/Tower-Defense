#pragma once
#ifndef ORB_HPP
#define ORB_HPP
#include "Turret.hpp"
#include "Sprite.hpp"
#include <vector>
#include <memory>
#include <map>
using namespace std;
class Enemy;
class Sprite;
class ORBBULLET;

class ORB : public Turret {
protected:
    int flag;
public:
    static const int Price;
    int bulletcnt;
    map <int, ORBBULLET*> bulletID;
    ORB(float x, float y, int bullet_num);
    void CreateBullet() override;
    char get_turret_id() override;
    int get_turret_bullet() override;
    void destruct_bullet();
    void ReloadCheck(bool notice, float reload);
};
#endif // ORB_HPP
