#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;

class Turret: public Engine::Sprite {
protected:
    float coolDown;
    float reload = 0.8;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    virtual void ReloadCheck(bool notice, float reload);

public:
    int price;
    int bulletcnt = 0;
    const int Price = price;
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Turret(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    //void Speedy(float slowFactor, float slowTime);
    //void SpeedyEffect(float deltatime);
    virtual char get_turret_id();
    virtual int get_turret_bullet();
    int lvl = 1;
    void Upgrade(std::string img_s);
};
#endif // TURRET_HPP
