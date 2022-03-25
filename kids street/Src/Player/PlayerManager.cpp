//PlayerManager.cpp
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由

#include "PlayerManager.h"

//CPlayerManagerの実体宣言、初期化
CPlayerManager* CPlayerManager::instance_ = nullptr;


//コンストラクタ
CPlayerManager::CPlayerManager()
{
	//CPlayerのコンストラクタは自動で呼ばれます
}

//デストラクタ
CPlayerManager::~CPlayerManager()
{
	//CPlayerのデストラクタは自動で呼ばれます
}


//初期化
void CPlayerManager::Init()
{
	//プレイヤーの初期化を呼ぶ
	player_.Init();
}


//読み込み
void CPlayerManager::Load()
{
	//プレイヤーの読み込み
	player_.Load();
}


//セット
void CPlayerManager::Set()
{
	//プレイヤーのセット
	player_.Set();
}


//ステップ
void CPlayerManager::Step()
{
	//プレイヤーのステップ
	player_.Step();
}


//反映
void CPlayerManager::Update()
{
	//プレイヤーの反映
	player_.Update();
}


//描画
void CPlayerManager::Draw()
{
	//プレイヤーの描画
	player_.Draw();
}


//削除
void CPlayerManager::Delete()
{
	//プレイヤー削除
	player_.Delete();
}


//後処理
void CPlayerManager::Fin()
{
	//プレイヤーの後処理を呼ぶ
	player_.Fin();
}