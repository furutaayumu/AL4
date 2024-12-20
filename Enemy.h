#pragma once

#include <WorldTransform.h>
#include <Model.h>
#include "Matrix.h"



class Enemy {
public:


	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	enum class Phase {
		Approch,
		Leave,
	};

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t EnemyHandle_;

	//ふぇーず
	Phase phase_;
};
