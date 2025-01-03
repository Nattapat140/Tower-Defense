#include <allegro5/base.h>
#include <random>
#include <string>
#include <map>

#include "DirtyEffect.hpp"
#include "GameEngine.hpp"
#include "Enemy.hpp"
#include "ORBBULLET.hpp"
#include "ORB.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"

class Turret;
class Sprite;
class ORB;

PlayScene* ORBBULLET::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void ORBBULLET::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	//std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

ORBBULLET::ORBBULLET(std::string img, float spd, float dmg, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* prnt, float OrbRadius, int ID) :
	Sprite(img, position.x, position.y), spd(spd), dmg(dmg), prnt(prnt), BulletID(ID){
	Velocity = forwardDirection.Normalize() * spd;
	Rotation = rotation;
	CollisionRadius = 4;
	prntPosX = prnt->Position.x; //initial pos 
	prntPosY = prnt->Position.y; //initial pos
	OrbitalRadius_G = OrbRadius;
}
void ORBBULLET::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!scene) {
		return;
	}
	float orbitalRadius = OrbitalRadius_G;
	float orbitSpeed = spd / orbitalRadius;
	Rotation += orbitSpeed * deltaTime;

	//the x-coordinate offset of the bullet on the orbit. It detemines how far the bullet is positioned along the x-axis relative to the center of the orbit.
	//for multiplying this formula give me the appropriate y and x-coordinate offset of the bullet on the circular orbit.
	float posX = prntPosX + orbitalRadius * sin(Rotation); //for position x
	//for vertical movement we use sin()...
	//the y-coordinate offset of the bullet on the orbit. It detemines how far the bullet is positioned along the y-axis relative to the center of the orbit.
	float posY = prntPosY + orbitalRadius * cos(Rotation); //for position y
	//for horizontal movement we use cos()...

	Position = Engine::Point(posX, posY);//the current position of the bulleton the orbit

	for (auto& obj : scene->EnemyGroup->GetObjects()) { //hit enemy part
		Enemy* enemy = dynamic_cast<Enemy*>(obj);
		if (!enemy->Visible) {
			continue;
		}
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			dynamic_cast<ORB*>(prnt)->bulletcnt--;
			OnExplode(enemy);
			enemy->Hit(dmg);

			auto bulletIterator = dynamic_cast<ORB*>(prnt)->bulletID.find(BulletID);
			if (bulletIterator != dynamic_cast<ORB*>(prnt)->bulletID.end()) {
				dynamic_cast<ORB*>(prnt)->bulletID.erase(bulletIterator);
			}

			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
}
void ORBBULLET::SelfDestruct() { //for shifter becuase we move the bullet should be gone for a while
	auto bulletIterator = dynamic_cast<ORB*>(prnt)->bulletID.find(BulletID);
	if (bulletIterator != dynamic_cast<ORB*>(prnt)->bulletID.end()) {
		dynamic_cast<ORB*>(prnt)->bulletID.erase(bulletIterator);
	}
	getPlayScene()->BulletGroup->RemoveObject(objectIterator);
	return;
}