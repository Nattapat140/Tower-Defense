#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "shifter.hpp"
#include "Group.hpp"
#include "MachineGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ShootingEffect.hpp"

const int SHIFTER::Price = 0;
SHIFTER::SHIFTER(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/shifter.png", "play/shifter.png", x, y, 250, Price, 1.0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
char SHIFTER::get_turret_id() {
    return 'C';
}
void SHIFTER::CreateBullet() {

}
