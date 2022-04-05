#include "DxLib.h"
#include "Score.h"

namespace
{
	// 数字画像のファイルパス
	const char* SCORE_PATH = "Data/score/number16x32_01.png";

}

CScore::CScore()
	:digit_num_()
	,disp_score_()
	,handle_()
	,score_()
{
}

CScore::~CScore()
{

}


//初期化
void CScore::InitScore()
{
	for (int score_index = 0; score_index < NUMBER; score_index++)
	{
		handle_[score_index] = -1;
	}
	score_ = 0;
	disp_score_ = 0;
}



//読み込み
void CScore::LoadScore()
{

	LoadDivGraph(SCORE_PATH, 10, 10, 1, NUMBER_SIZE_X, NUMBER_SIZE_Y, handle_);

}


//データ破棄
void CScore::FinScore()
{
	for (int score_index = 0; score_index < NUMBER; score_index++)
	{
		if (handle_[score_index] != -1)
		{
			DeleteGraph(handle_[score_index]);
			handle_[score_index] = -1;
		}
	}
}

//スコアの描画
void CScore::DrawScore()
{
	CalcDigitNum(disp_score_);
	int TempScore = disp_score_;
	for (int score_index = 0; score_index < digit_num_; score_index++)
	{
		//あまりを出す
		int Num = TempScore % 10;
		//対応する数字を画像サイズ通りに描画　
		DrawRotaGraph(30 - score_index *NUMBER_SIZE_X, NUMBER_SIZE_Y, 1.0, 0.0, handle_[Num], true);

		//桁を減らす
		TempScore /= 10;
	}
}

//スコア加算する
void CScore::AddScore(int score)
{
	score_ += score;
}

void CScore::AddAllScore(int score)
{
	score_ += score;
	disp_score_ += score;
}


//スコアをセット
void CScore::SetScore(int score)
{
	disp_score_ = score;
	score_ = score;
}


void CScore::UpdateScore()
{
	//表示スコアと正しいスコアに差があるなら
	if (score_ != disp_score_)
	{
		//表示スコアを加算
		disp_score_ += ADD_SCORE_SPD;

		//もし行き過ぎたなら正しいスコアに戻す
		if (disp_score_ > score_)
		{
			disp_score_ = score_;
		}
	}
}

void CScore::CalcDigitNum(int score)
{

	int ans;
	// scoreが0の時は下のループを通らずに表示桁数１にして終わる
	if (score == 0)
	{
		digit_num_ = 1;
		return;
	}
	for (ans = 1, digit_num_ = 1; ans <= score; digit_num_++)
	{
		ans *= 10;
	}
	digit_num_ -= 1;


}