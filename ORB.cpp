#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "ORBBULLET.hpp"
#include "Group.hpp"
#include "ORB.hpp"
#include "Turret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ShootingEffect.hpp"

const int ORB::Price = 80;
ORB::ORB(float x, float y, int bullet_num) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/orb.png", x, y, 300, Price, 1.0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    bulletcnt = bullet_num;
    this->flag = 1; // this tower is new
}
void ORB::CreateBullet() { //this will keep creating bullets in each tick in different pos according to the formula
    PlayScene* scene = getPlayScene();
    if (!scene) {
        return;
    }
    const float Radius = 150.0f;
    const float Speed = 200.0f;
    Engine::Point pos = Position; 
    int creationSize, tmpcnt = 0;

    if (this->bulletcnt >= 0 && (this->bulletcnt <= 4) && (this->flag == 1)) {
        creationSize = this->bulletcnt;
    }
    else {
        creationSize = 4;
    }
    // make sure that we ceate the bullet same amount as before shifting
    for (int i = 0;i < creationSize;i++) {
        float rotation = i * 3.14 / 2;
        ORBBULLET* bullet = new ORBBULLET("play/orbbullet.png", Speed, 4, pos, Position, rotation, this, Radius, i);
        scene->BulletGroup->AddNewObject(bullet);
        bulletID[i] = bullet;
        tmpcnt++;
    }
    if (tmpcnt != this->bulletcnt) { //reset the bulletcnt
        this->bulletcnt = tmpcnt;
    }
    this->flag = 0; //this tower is not new
}
char ORB::get_turret_id() {
    return 'O';
}
void ORB::ReloadCheck(bool notice, float reload) { //check whether we should create new bullets or not
    if (this->bulletcnt >= 1 && this->flag == 0) { //it has to be >= 1 cuz if it is == 4 everytime it hits enemy it will create bullet more
        return;
    }
    else if (this->bulletcnt >= 1 && this->flag == 1) {
        CreateBullet();
    }
    else {
        CreateBullet();
    }
}
int ORB::get_turret_bullet() { //return bulletcnt
    return this->bulletcnt;
}
void ORB::destruct_bullet() { //destroying bullets
    for (int i = 0;i < 4;i++) {
        if (bulletID.find(i) != bulletID.end()) {
            bulletID[i]->SelfDestruct(); //call in orbbullet.cpp
        }
    }
}
