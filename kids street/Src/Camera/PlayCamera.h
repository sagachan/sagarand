//PlayCamera.h
//�v���C�V�[���ł̃J����

#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

class CPlayCamera
{
	
public:
	CPlayCamera();	//�R���X�g���N�^
	~CPlayCamera();	//�f�X�g���N�^

public:
	//������
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//���t���[���Ăԏ����i����j
	void Step();

	//�J�������̍X�V����
	void Update();

	//�㏈��
	void Fin();

	//���W�擾
	VECTOR GetPos() { return cameraInfo.pos; }

	//�����_�擾
	VECTOR GetLook() { return cameraInfo.look; }

private:

	//�J�������
	struct CameraInfo
	{
		VECTOR	pos;		//���_
		VECTOR	look;		//�����_
		VECTOR	up;			//�A�b�v�x�N�g��
		float fRotX;		//�����p�x(X���p�x)
		float fRotY;		//�����p�x(Y���p�x)
	};

	CameraInfo cameraInfo;
};