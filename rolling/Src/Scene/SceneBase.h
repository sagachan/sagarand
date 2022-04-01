//SceneBase.h
//�V�[���p���N���X

#pragma once

class CSceneBase
{

public:
	CSceneBase();
	virtual ~CSceneBase();

	//������
	virtual void Init() = 0;

	//�ǂݍ���
	virtual void Load() = 0;

	//�e�ϐ��Ȃǂɒl���Z�b�g
	virtual void Set() = 0;

	//���t���[���Ăԏ���
	virtual void Step() = 0;

	//�`��
	virtual void Draw() = 0;

	//�㏈��
	virtual void Fin() = 0;
};