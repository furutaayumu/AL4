#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	//速度
	Vector3 velocity_;
};
