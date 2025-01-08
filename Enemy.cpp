#include "Enemy.h"
#include "Matrix.h"
#include "PLayer.h"

float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
float Length(const Vector3& v) { return std::sqrt(Dot(v, v)); }

static Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	// 返り値
	return result;
}

	Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	assert(length != 0.0f);
	return {v.x / length, v.y / length, v.z / length};
}

		static Vector3 Multiply(const Vector3& v1, const float v2) {
	Vector3 result;
	result.x = v1.x * v2;
	result.y = v1.y * v2;
	result.z = v1.z * v2;

	// 返り値
	return result;
}

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
	const float kBulletSpeed = -1.0f;

	//velocity = Matrix::TransformNormal(velocity, worldTransform_.matWorld_);

	//弾の速度計算
	pWorldposition = player_->GetWorldPosition();
	eWorldposition = Enemy::GetWorldPosition();
	//ベクトルの正規化
	Vector3 difference = Subtract(eWorldposition, pWorldposition);
	Vector3 normalize = Normalize(difference);

	Vector3 velocity = Multiply(normalize, kBulletSpeed);

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

Vector3 Enemy::GetWorldPosition() {
	 Vector3 worldPos;
	 //ワールド行列を取得
	 worldPos.x = worldTransform_.matWorld_.m[3][0];
	 worldPos.y = worldTransform_.matWorld_.m[3][1];
	 worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos; 
}

void Enemy::OnCollision() {}
