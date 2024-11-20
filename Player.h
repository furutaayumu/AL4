#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#pragma once
class Player {
public:
	void Initialize(Model* model,uint32_t textureHandle_);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Rotate();

private:
	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	//キーボード入力
	Input* input_;
};
