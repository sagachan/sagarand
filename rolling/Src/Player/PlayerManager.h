//PlayerManager.h
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由

#pragma once

#include "Player.h"

class CPlayerManager
{
public:

	CPlayerManager();	//コンストラクタ
	~CPlayerManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CPlayerManager; }
	//インスタンス取得
	static CPlayerManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	//初期化
	void Init();

	//読み込み
	void Load();

	//セット
	void Set();

	//ステップ
	void Step();

	//反映
	void Update();

	//描画
	void Draw();

	//削除
	void Delete();

	//後処理
	void Fin();

	//プレイヤークラスを取得
	CPlayer* GetPlayer() { return &player_; }

private:
	static CPlayerManager* instance_;	//インスタンス

	CPlayer player_;	//プレイヤークラス

};