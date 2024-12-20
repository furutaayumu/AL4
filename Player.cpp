#include "Player.h"
#include "Matrix.h"

#include <cmath>


void Player::Initialize(Model* model,uint32_t textureHandle) { 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();

	input_ = Input::GetInstance(); 


}

void Player::Update() {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			    delete bullet;
			    return true;
		    } return false;
	});
	
	worldTransform_.matWorld_;

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


		Attack();

	//弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.matWorld_ = Matrix::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection& viewProjection) { 

		//弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Rotate() { 
	
	const float kRotSpeed = 0.02f;
	//押した方向に回転
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE) != 0 && input_->TriggerKey(DIK_SPACE) == 1) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = Matrix::TransformNormal(velocity, worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_,worldTransform_.translation_,velocity);

		bullets_.push_back(newBullet);

	/*	bullet_ = newBullet;*/
	}
}

Player::~Player() {
	//for (PlayerBullet* bullet : bullets_) {
	//	delete bullet;
	//}

}

