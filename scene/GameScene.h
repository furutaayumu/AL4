#pragma once

#include <DirectXGame/audio/Audio.h>
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <vector>
#include "DebugCamera.h"
#include "Tenkyu.h"
#include "MapChipField.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summar

	uint32_t textureHandle_ = 0;
	uint32_t EnemyHandle_ = 0;

	//3dモデル
	Model* model_ = nullptr;

	//座標
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	//プレイヤー
	Player* player_ = nullptr;

	//敵
	Enemy* enemy_ = nullptr;
};
