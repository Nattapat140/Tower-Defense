#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "freeze.hpp"
#include "Group.hpp"
#include "MachineGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ShootingEffect.hpp"

const int FREEZE::Price = 50;
FREEZE::FREEZE(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/snow.png", "play/snow.png", x, y, 250, Price, 1.0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
char FREEZE::get_turret_id() {
    return 'F';
}
void FREEZE::CreateBullet() {

}
