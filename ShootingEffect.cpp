#include <cmath>
#include <string>

#include "ShootingEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"

// TODO 4 (1/2): You can imitate the 2 files: 'ExplosionEffect.hpp', 'ExplosionEffect.cpp' to create shoot effect.
PlayScene* ShootingEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
ShootingEffect::ShootingEffect(Engine::Point position) : Sprite("play/shoot-1.png", position.x, position.y), timeTicks(0) {
	for (int i = 1; i <= 4; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/shoot-" + std::to_string(i) + ".png"));
	}
}
void ShootingEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
