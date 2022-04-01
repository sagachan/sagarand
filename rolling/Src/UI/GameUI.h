//GameUI.h
//UIのベースとなるクラス

#pragma once

//UIのベースとなるクラス
class CGameUI
{
public:
	CGameUI();
	virtual ~CGameUI();

public:
	virtual void Init(float pos_x, float pos_y) = 0;	//初期化
	virtual void Load(const char* file_path) = 0;		//読み込み
	virtual void Step() = 0;							//ステップ
	virtual void Draw() = 0;							//描画
	virtual void Delete() = 0;							//削除
	virtual void Fin() = 0;								//後処理

	void SetPosX(float pos_x) { pos_x_ = pos_x; }	//Ｘ座標設定
	void SetPosY(float pos_y) { pos_y_ = pos_y; }	//Ｙ座標設定

	float GetPosX()const { return pos_x_; }	//Ｘ座標取得
	float GetPosY()const { return pos_y_; }	//Ｙ座標取得

protected:
	float pos_x_;	//Ｘ座標
	float pos_y_;	//Ｙ座標
};