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
	const float kEnemySpeed = 0.2f;
	move.z += kEnemySpeed;
	move.x += kEnemySpeed;

	switch (phase_) { case Phase::Approch:
	default:
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
		worldTransform_.translation_.x += move.x;


		worldTransform_.matWorld_;

		worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		worldTransform_.TransferMatrix();

		worldTransform_.UpdateMatrix();
		break;
	}

}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, EnemyHandle_); }
