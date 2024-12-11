#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>

class Player {
public:
	void Initialize(Model* model,uint32_t textureHandle_);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Rotate();
	void Attack();
	~Player();

private:


	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	PlayerBullet* bullet_ = nullptr;

	//キーボード入力
	Input* input_;

	//弾
	std::list<PlayerBullet*> bullets_;
};
	
