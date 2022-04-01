//GameUIButton.cpp
//UIボタンクラス

#include "GameUIButton.h"
#include "DxLib.h"

CGameUIButton::CGameUIButton()
	:handle_(0)
{
}

CGameUIButton::~CGameUIButton()
{
}


//初期化
void CGameUIButton::Init(float pos_x, float pos_y)
{
	pos_x_ = pos_x;
	pos_y_ = pos_y;
}


//読み込み
void CGameUIButton::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//ステップ
void CGameUIButton::Step()
{
	//ボタンの更新処理
}


//描画
void CGameUIButton::Draw()
{
	DrawGraph((int)pos_x_, (int)pos_y_, handle_, true);
}


//削除
void CGameUIButton::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIButton::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}