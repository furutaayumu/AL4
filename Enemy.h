#pragma once

#include <WorldTransform.h>
#include <Model.h>
#include "Matrix.h"
#include "EnemyBullet.h"
#include "Player.h"

class Player;

class Enemy {
public:
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Fire();
	void ApprochIni();
	Vector3 GetWorldPosition();
	void OnCollision();
	//セッター
	void SetPlayer(Player* player) { player_ = player; }
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }
	float GetRadius() { return radius_; }

public:
	static const int kFireinterval = 60;

private:
	enum class Phase {
		Approch,
		Leave,
	};

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t EnemyHandle_;

	//ふぇーず
	Phase phase_;

	//敵の弾
	EnemyBullet* enemyBullet_;
	// 弾
	std::list<EnemyBullet*> bullets_;
	
	int32_t FireTimer = 60;

	Player* player_ = nullptr;

	Vector3 pWorldposition;
	Vector3 eWorldposition;

	float radius_ = 3.0f;
};
