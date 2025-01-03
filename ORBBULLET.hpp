#ifndef ORBBULLET_HPP
#define ORBBULLET_HPP
#include <string>
#include "Bullet.hpp"
#include "Sprite.hpp"
#include "GameEngine.hpp"
#include "Sprite.hpp"

class Enemy;
class Turret;
class PlayScene;
namespace Engine {
    struct Point;
}  // namespace Engine

class ORBBULLET : public Engine::Sprite {
protected:
    float spd;
    float dmg;
    float prntPosX, prntPosY;
    float OrbitalRadius_G;
    Turret* prnt;
    PlayScene* getPlayScene();
    virtual void OnExplode(Enemy* enemy);
public:
    int BulletID;
    Enemy* Target = nullptr;
    ORBBULLET(std::string img, float spd, float dmg, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* prnt, float OrbRadius, int ID);
    void Update(float deltaTime) override;
    void SelfDestruct();
};
#endif // ORBBULLET_HPP
