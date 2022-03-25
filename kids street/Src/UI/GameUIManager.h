//GameUIManager.h
//UI�Ǘ��p�N���X

#pragma once

#include "GameUISprite.h"
#include "GameUIButton.h"
#include <vector>

//UI�Ǘ��p�N���X
class CGameUIManager
{
public:
	enum UI_TYPE
	{
		UI_TYPE_SPRITE,	//�X�v���C�g
		UI_TYPE_BUTTON	//�{�^��
	};

public:
	CGameUIManager();
	~CGameUIManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGameUIManager; }
	static CGameUIManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	CGameUI* CreateUI(UI_TYPE type);	//UI�̐���
	void Step();						//�X�e�b�v
	void Draw();						//�`��
	void DeleteAll();					//UI�̍폜

private:
	static CGameUIManager* instance_;

	//����A�ǂ�ǂ�UI�������Ă����v�Ȃ悤��
	//���I�z��Ƃ��Đ錾
	std::vector<CGameUI*> ui_vec_;
};