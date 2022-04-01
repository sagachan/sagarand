//TitleScene.h
//�^�C�g���V�[��

#pragma once

#include "SceneBase.h"

//�^�C�g���V�[���N���X
class CTitleScene :public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

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