#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "MathUtilityForText.h"
#include "MapChipField.h"

Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_ = Model::Create();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("player.jpg");
	EnemyHandle_ = TextureManager::Load("Enemy.webp");

	//初期化
	player_ = new Player();
	player_->Initialize(model_,textureHandle_);

	//敵初期化
	enemy_ = new Enemy();
	enemy_->Initialize(model_, EnemyHandle_);

	enemy_->SetPlayer(player_);

}

void GameScene::Update() {
	player_->Rotate();
	player_->Update(); 
	enemy_->Update();
}

void GameScene::Draw() {

	//PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>w

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//モデル描画
	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}

void GameScene::CheckAllCollisions() { 
	Vector3 posA, posB; 
	Vector3 A2B;

	float len;
	float radius;

	//const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets) {	
	//敵弾
		posB = bullet->GetWorldPosition();

	//AとBの距離
		A2B = posA - posB;
		len = Matrix::Length(A2B);
		radius = player_->GetRadius() + enemy_->GetRadius();
		if (len <= radius) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	
}
