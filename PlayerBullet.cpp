#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position) { assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("bullet.webp");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = 0;
	worldTransform_.translation_.y = 0;
}

void PlayerBullet::Update() { 
	worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
