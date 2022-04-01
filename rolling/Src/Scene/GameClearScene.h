//GameClearScene.h
//�Q�[���N���A�V�[��

#pragma once

#include "SceneBase.h"

//�Q�[���N���A�N���X
class CGameClearScene :public CSceneBase
{
public:
	CGameClearScene();
	~CGameClearScene();

	//������
	void Init() override;

	//�ǂݍ���
	void Load() override;

	//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Set() override;

	//���t���[���Ăԏ���
	void Step() override;

	//�`��
	void Draw() override;

	//�㏈��
	void Fin() override;

private:
	//�������\����
	struct TextInfo
	{
		int handle;
		float pos_x;
		float pos_y;
		float base_pos_y;
		float size;
		float wave_angle;
	};

	TextInfo text_info_;	//�������
};