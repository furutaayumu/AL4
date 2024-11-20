#include "Player.h"
#include "Matrix.h"
#include <cmath>
//Vector3 Add(const Vector3& v1, const Vector3& v2) {
//	Vector3 result;
//	result.x = (v1.x + v2.x);
//	result.y = (v1.y + v2.y);
//	result.z = (v1.z + v2.z);
//	return result;
//};
//
//Vector3 operator+=(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }

void Player::Initialize(Model* model,uint32_t textureHandle) { 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();

	input_ = Input::GetInstance(); 


}

void Player::Update() {
	worldTransform_.matWorld_;
	// 行列の転送
	worldTransform_.TransferMatrix();

	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if(input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	//移動制限
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;
	//移動範囲
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }