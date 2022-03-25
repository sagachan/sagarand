//PlayCamera.cpp
//�v���C�V�[���ł̃J����

#include "PlayCamera.h"
#include <math.h>
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Input/Pad/Pad.h"

//�J�����֘A
#define CAMERA_OFFSET_Z	(-25.0f)		//�J�����̒����_����̎�O�I�t�Z�b�g�l
#define CAMERA_LOOK_OFFSET_Y (10.0f)	//�J�����̒����_�̍����I�t�Z�b�g

//�R���X�g���N�^
CPlayCamera::CPlayCamera()
{
	cameraInfo = { 0 };
}

//�f�X�g���N�^
CPlayCamera::~CPlayCamera()
{
}


//�������i�����Ȃ��j
void CPlayCamera::Init()
{
	cameraInfo = { 0 };
}


//�������i��������j
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	cameraInfo.pos = pos;
	cameraInfo.look = look;
	cameraInfo.up = up;
}


//���t���[���Ăԏ����i����j
void CPlayCamera::Step()
{
	//�v���C���[�̏����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//���͑���N���X�擾
	CInput* input = CInput::GetInstance();

	// �J�����̒����_
	cameraInfo.look = player->GetPos();
	cameraInfo.look.y = player->GetPos().y + CAMERA_LOOK_OFFSET_Y;	//�v���C���[�̏����������

	// �����_�����_�ɕ��s�ړ�����s����쐬
	MATRIX origin_look_mat =
		CMyMath::GetTranslateMatrix(VGet(-cameraInfo.look.x, -cameraInfo.look.y, -cameraInfo.look.z));

	//�J�����𒍎��_����O�Ɉړ������镽�s�ړ��s����쐬
	MATRIX fore_look_mat =
		CMyMath::GetTranslateMatrix(VGet(0.0f, 0.0f, CAMERA_OFFSET_Z));

	//�J������X����]�s����쐬
	MATRIX pitch_mat = CMyMath::GetPitchMatrix(cameraInfo.fRotX);

	//�J������Y����]�s����쐬
	MATRIX yaw_mat = CMyMath::GetYawMatrix(cameraInfo.fRotY);

	// �����_�����̈ʒu�ɕ��s�ړ�����s����쐬
	MATRIX default_look_mat = CMyMath::GetTranslateMatrix(cameraInfo.look);

	//�e�s��������i�|���Z�̏��Ԃɒ��ӁI�I�j
	MATRIX mult_mat = CMyMath::MatMult(default_look_mat, yaw_mat);
	mult_mat = CMyMath::MatMult(mult_mat, pitch_mat);
	mult_mat = CMyMath::MatMult(mult_mat, fore_look_mat);
	mult_mat = CMyMath::MatMult(mult_mat, origin_look_mat);

	//�����_�ɍs����|���ăJ�����̍��W���Z�o
	cameraInfo.pos = CMyMath::MatTransform(mult_mat, cameraInfo.look);
}


//�J�������̍X�V����
void CPlayCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(cameraInfo.pos, cameraInfo.look, cameraInfo.up);
}


//�㏈��
void CPlayCamera::Fin()
{
}