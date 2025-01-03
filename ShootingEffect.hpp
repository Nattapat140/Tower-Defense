#pragma once
#ifndef SHOOTINGEFFECT_HPP
#define SHOOTINGEFFECT_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>
#include "Point.hpp"
#include "GameEngine.hpp"
#include "Sprite.hpp"

class PlayScene;

class ShootingEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	ShootingEffect(Engine::Point position);
	void Update(float deltaTime) override;
};
#endif // EXPLOSIONEFFECT_HPP
