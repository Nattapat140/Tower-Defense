#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "GOLDENEMY.hpp"
GOLDENEMY::GOLDENEMY(int x, int y) : Enemy("play/enemy-11.png", x, y, 25, 50, 20, 0) {
	// TODO 2 (1/3): You can imitate the 2 files: 'RedNormalEnemy.hpp', 'RedNormalEnemy.cpp' to create a new enemy.
}
void GOLDENEMY::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
void GOLDENEMY::Hit(float damage) {
	hp -= damage;
	getPlayScene()->EarnMoney(3);
	if (hp <= 0) { //completely deadth
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedTurrets)
			it->Target = nullptr;
		for (auto& it : lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}