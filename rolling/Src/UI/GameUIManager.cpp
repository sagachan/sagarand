//GameUIManager.cpp
//UI管理用クラス

#include "GameUIManager.h"

CGameUIManager* CGameUIManager::instance_ = nullptr;

CGameUIManager::CGameUIManager()
{
}

CGameUIManager::~CGameUIManager()
{
}

//UIの生成
CGameUI* CGameUIManager::CreateUI(UI_TYPE type)
{
	CGameUI* ui = nullptr;
	switch (type) 
	{
		case UI_TYPE_SPRITE: ui = new CGameUISprite; break;
		case UI_TYPE_BUTTON: ui = new CGameUIButton; break;
	}

	ui_vec_.push_back(ui);
	return ui;
}


//ステップ
void CGameUIManager::Step()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Step();
	}
}


//描画
void CGameUIManager::Draw()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Draw();
	}
}


//UIの削除（vector内のUIをすべて削除）
void CGameUIManager::DeleteAll()
{
	//まずUIを削除してから
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		CGameUI* ui = (*itr);
		ui->Fin();
		delete ui;
	}
	//配列を削除する
	ui_vec_.clear();
	ui_vec_.shrink_to_fit();
}