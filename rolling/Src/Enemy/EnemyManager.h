#pragma once

#include "FallEnemy/FallEnemy.h"
#include "EnemyCommon.h"

class CEnemyManager
{
public:

	CEnemyManager();	//コンストラクタ
	~CEnemyManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CEnemyManager; }
	//インスタンス取得
	static CEnemyManager* GetInstance() { return instance_; }
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

	//ドッスンクラスを取得
	CFallEnemy* GetFallEnemy() { return fallEnemy_; }

private:
	static CEnemyManager* instance_;	//インスタンス

	CFallEnemy fallEnemy_[FALL_ENEMY_NUM];	//ドッスンクラス

};