//Sky.cpp
//道クラス

#include "Sky.h"


//コンストラクタ
CSky::CSky()
{
	mapInfo_ = { 0 };
}

//デストラクタ
CSky::~CSky()
{
}

void CSky::Init()
{
	
}


//読み込み
void CSky::Load()
{
	// モデル読み込み
	mapInfo_.handle = MV1LoadModel("Data/Map/sky.x");
}



//セット
void CSky::Set()
{
	//モデルセット
	MV1SetPosition(mapInfo_.handle, MAP_POS);
}


//ステップ
void CSky::Step()
{

}


//更新
void CSky::Update()
{

}


//描画
void CSky::Draw()
{
	MV1DrawModel(mapInfo_.handle);
}


//削除
void CSky::Delete()
{
}


//後処理
void CSky::Fin()
{
	MV1DeleteModel(mapInfo_.handle);
}