#include "Enemy.h"
#include "Matrix.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	EnemyHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	
	worldTransform_.translation_.z = 10;

	
}

void Enemy::Update() { 
		// 移動処理
	Vector3 move = {0, 0, 0};
	const float kEnemySpeed = 0.1f;
	move.z += kEnemySpeed;
	move.x += kEnemySpeed;

	


	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	switch (phase_) { 
	case Phase::Approch:
		worldTransform_.translation_.z -= move.z;
		if (worldTransform_.translation_.z <= -10.0f) {
			phase_ = Phase::Leave;
		}

	

		worldTransform_.matWorld_;

		worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		worldTransform_.TransferMatrix();

		worldTransform_.UpdateMatrix();
		break;

	case Phase::Leave:

			ApprochIni();
		worldTransform_.translation_.x += move.x;

		worldTransform_.matWorld_;

		worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		worldTransform_.TransferMatrix();
		
		worldTransform_.UpdateMatrix();
		break;
	}

}

void Enemy::Draw(ViewProjection& viewProjection) { 
				// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	model_->Draw(worldTransform_, viewProjection, EnemyHandle_); }

void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	//velocity = Matrix::TransformNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
}

void Enemy::ApprochIni() { 
		FireTimer--;
	if (FireTimer <= 1) {
		Fire();
		FireTimer = kFireinterval;
	}

 }
