//DebugCamera.h
//�f�o�b�O�p�̃J����

#pragma once

#include "DxLib.h"

//�f�o�b�O�J�����N���X
class CDebugCamera
{
public:
	CDebugCamera();		//�R���X�g���N�^
	~CDebugCamera();	//�f�X�g���N�^

public:
	void Init();									//�������i�����Ȃ��j
	void Init(VECTOR pos, VECTOR look, VECTOR up);	//�������i��������j
	void Step();									//�X�e�b�v
	void Update();									//���f
	void Draw();									//�`��i�����_�ɋ��̂�`��j
	void Fin();										//�㏈��

private:
	VECTOR m_vPos;		//���_
	VECTOR m_vLook;		//�����_
	VECTOR m_vUp;		//�A�b�v�x�N�g��
	VECTOR m_angle;		//�p�x�i�A���O���j
};