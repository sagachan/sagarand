//PlayScene.h
//�v���C�V�[��

#pragma once

#include "DxLib.h"
#include "SceneBase.h"

#define WAIT_MAX_TIME 30


//�v���C�V�[���N���X
class CPlayScene :public CSceneBase
{
public:
	CPlayScene();
	~CPlayScene();

	//������
	void Init() override;

	//�ǂݍ���
	void Load() override;

	//�e�ϐ��Ȃǂɒl���Z�b�g
	void Set() override;

	//���t���[���Ăԏ���
	void Step() override;

	

	//�`��
	void Draw() override;

	//�㏈��
	void Fin() override;


	
	VECTOR map_pos; //�����蔻��p�}�b�v���W
	int map_handle; //�����蔻�胂�f���ǂݍ���



};
