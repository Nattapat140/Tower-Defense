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
#include "TwoDiceEnemy.hpp"
#include "dice_enemy.hpp"
TWODICEENEMY::TWODICEENEMY(int x, int y) : Enemy("play/dice-2.png", x, y, 25, 50, 26, 40) {
	// TODO 2 (1/3): You can imitate the 2 files: 'RedNormalEnemy.hpp', 'RedNormalEnemy.cpp' to create a new enemy.
}
void TWODICEENEMY::OnExplode() {
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
void TWODICEENEMY::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) { //fake deadth
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedTurrets)
			it->Target = nullptr;
		for (auto& it : lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		Enemy* enemy;
		getPlayScene()->EnemyGroup->AddNewObject(enemy = new DiceEnemy(Position.x, Position.y));
		enemy->UpdatePath(getPlayScene()->mapDistance);

		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}