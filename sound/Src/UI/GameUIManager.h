//GameUIManager.h
//UI管理用クラス

#pragma once

#include "GameUISprite.h"
#include "GameUIButton.h"
#include <vector>

//UI管理用クラス
class CGameUIManager
{
public:
	enum UI_TYPE
	{
		UI_TYPE_SPRITE,	//スプライト
		UI_TYPE_BUTTON	//ボタン
	};

public:
	CGameUIManager();
	~CGameUIManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGameUIManager; }
	static CGameUIManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	CGameUI* CreateUI(UI_TYPE type);	//UIの生成
	void Step();						//ステップ
	void Draw();						//描画
	void DeleteAll();					//UIの削除

private:
	static CGameUIManager* instance_;

	//今後、どんどんUIが増えても大丈夫なように
	//動的配列として宣言
	std::vector<CGameUI*> ui_vec_;
};