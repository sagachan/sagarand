//GameOverScene.h
//�Q�[���I�[�o�[�V�[��

#pragma once

#include "SceneBase.h"

//�Q�[���I�[�o�[�V�[���N���X
class CGameOverScene :public CSceneBase
{
public:
	CGameOverScene();
	~CGameOverScene();

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