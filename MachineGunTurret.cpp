#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "FireBullet.hpp"
#include "Group.hpp"
#include "MachineGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ShootingEffect.hpp"

const int MachineGunTurret::Price = 60;
MachineGunTurret::MachineGunTurret(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/turret-1.png", x, y, 300, Price, 1.0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void MachineGunTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.

    for (int i = 0;i < this->lvl ;i++) {
        Engine::Point perpendicular = Engine::Point(-normalized.y, normalized.x);
        Engine::Point Pos = Position + normalized * 36 + perpendicular * (i - (this->lvl - 1) / 2.0f) * 10.0f;
        getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Pos, diff, rotation, this));
    }
    // TODO 4 (2/2): Add a ShootEffect here. Remember you need to include the class.
    getPlayScene()->EffectGroup->AddNewObject(new ShootingEffect(this->Position + normalized * 36));
    AudioHelper::PlayAudio("gun.wav");
}
char MachineGunTurret::get_turret_id() {
    return 'M';
}
