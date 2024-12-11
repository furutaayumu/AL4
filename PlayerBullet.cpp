#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include <cassert>
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = (v1.x + v2.x);
	result.y = (v1.y + v2.y);
	result.z = (v1.z + v2.z);
	return result;
};

Vector3 operator+=(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }

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
	worldTransform_.translation_ += velocity_;
	
	//worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
	//worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
