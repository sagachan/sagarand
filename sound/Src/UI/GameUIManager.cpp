//GameUIManager.cpp
//UI�Ǘ��p�N���X

#include "GameUIManager.h"

CGameUIManager* CGameUIManager::instance_ = nullptr;

CGameUIManager::CGameUIManager()
{
}

CGameUIManager::~CGameUIManager()
{
}

//UI�̐���
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


//�X�e�b�v
void CGameUIManager::Step()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Step();
	}
}


//�`��
void CGameUIManager::Draw()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Draw();
	}
}


//UI�̍폜�ivector����UI�����ׂč폜�j
void CGameUIManager::DeleteAll()
{
	//�܂�UI���폜���Ă���
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		CGameUI* ui = (*itr);
		ui->Fin();
		delete ui;
	}
	//�z����폜����
	ui_vec_.clear();
	ui_vec_.shrink_to_fit();
}