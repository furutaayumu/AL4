#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	
	velocity_ = velocity;
	model_ = model;
	textureHandle_ = TextureManager::Load("bullet.webp");

	worldTransform_.Initialize();	
	worldTransform_.translation_ = position;
	/*worldTransform_.translation_.y = position.y;*/
}

void PlayerBullet::Update() { 
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_ += velocity_;
	
	//worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
	//worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
