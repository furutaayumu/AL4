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
	Vector3 GetWorldPosition();
	void OnCollision();
	float GetRadius() { return radius_; }
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:


	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	PlayerBullet* bullet_ = nullptr;

	//キーボード入力
	Input* input_;

	//弾
	std::list<PlayerBullet*> bullets_;
	
	float radius_ = 3.0f;
};
	
