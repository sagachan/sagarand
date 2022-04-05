#pragma once


namespace {
	const int NUMBER = 10;
	const int NUMBER_SIZE_X = 16;
	const int NUMBER_SIZE_Y = 32;
	const int ADD_SCORE_SPD = 1;
}

class CScore
{
public:
	CScore();
	~CScore();

	//スコアの初期化
	void InitScore();

	//スコア画像のロード
	void LoadScore();

	//画面表示スコアの更新
	void UpdateScore();

	//スコアの描画
	void DrawScore();

	//スコア画像の破棄
	void FinScore();

	//スコアを加算　画面表示用スコアには加算しない
	void AddScore(int score);
	//画面表示用スコアも含めて加算
	void AddAllScore(int score);

	//スコアをセットする
	void SetScore(int score);

	//スコアを取得
	int GetScore() { return score_; };

	void CalcDigitNum(int score);

private:
	int handle_[10];
	int score_;
	//画面表示スコア
	int disp_score_;
	int digit_num_;
};

