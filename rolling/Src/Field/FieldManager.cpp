//FieldManager.cpp
//フィールド管理
//CFieldへのアクセスは必ずCFieldManagerを経由

#include "FieldManager.h"
//CFieldManagerの実体宣言、初期化
CFieldManager* CFieldManager::instance_ = nullptr;

//コンストラクタ
CFieldManager::CFieldManager()
{
}

//デストラクタ
CFieldManager::~CFieldManager()
{
}

void CFieldManager::Init()
{
	road_.Init();
}


//読み込み
void CFieldManager::Load()
{
	road_.Load();
}



//セット
void CFieldManager::Set()
{
	road_.Set();
}


//ステップ
void CFieldManager::Step()
{
	road_.Step();
}


//更新
void CFieldManager::Update()
{
	
	road_.Update();
	
}


//描画
void CFieldManager::Draw()
{
	
	road_.Draw();
	
}


//削除
void CFieldManager::Delete()
{
	
	road_.Delete();
}


//後処理
void CFieldManager::Fin()
{
	road_.Fin();
}

