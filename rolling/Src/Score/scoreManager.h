#pragma once
#include "Score.h"

class CScoreManager
{

public:
	CScoreManager();		//コンストラクタ
	~CScoreManager();		//デストラクタ

public:
	static void CreateInstance() { if (!instance_)instance_ = new CScoreManager; }
	static CScoreManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:


	//スコアの初期化
	void Init();

	//スコア画像のロード
	void Load();

	//画面表示スコアの更新
	void Update();

	//スコアの描画
	void Draw();

	//スコア画像の破棄
	void Fin();

	//スコアを加算 trueを渡すとAllAddを呼ぶ
	void AddScore(int score, bool all_add_flg = false);

	//スコアを強制的にセットする
	void SetScore(int score);

	//スコアを取得
	int GetScore() { return score_.GetScore(); }

	//CScore* GetScore() { return &score_; }

private:
	static CScoreManager* instance_;
	CScore score_;

};