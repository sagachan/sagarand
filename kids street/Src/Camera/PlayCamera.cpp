//PlayCamera.cpp
//�v���C�V�[���ł̃J����

#include "PlayCamera.h"
#include <math.h>
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Input/Pad/Pad.h"

//�J�����֘A
#define CAMERA_OFFSET_Z			(-12.0f)		//�J�����̒����_����̎�O�I�t�Z�b�g�l
#define CAMERA_LOOK_OFFSET_Y	(4.0f)		//�J�����̒����_�̍����I�t�Z�b�g
#define CAMERA_ROT_SPEED		(0.052f)	//�J�����̉�]���x

namespace
{
	//�J�����̉�]�X�s�[�h
	const float PLAY_CAMERA_ROTATION = (2.0f * DX_PI_F / 180.0f);
	//�J�����̉�]�l�ő�
	const float PLAY_CAMERA_ROTATION_MAX = (2.0f * DX_PI_F);
	//�J������X��]�l�ő�
	const float PLAY_CAMERA_ROTATION_MAX_X = (20.0f * 2.0f * DX_PI_F / 180.0f);
	//�J������X��]�l�ŏ�
	const float PLAY_CAMERA_ROTATION_MIN_X = (-10.0f * 2.0f * DX_PI_F / 180.0f);

	//�J�����̃T�C�Y
	const float PLAY_CAMERA_SIZE_H = 1.0f;
	const float PLAY_CAMERA_SIZE_W = 1.0f;
	const float PLAY_CAMERA_SIZE_D = 1.0f;
	const float PLAY_CAMERA_SIZE_R = 1.0f;
}

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

	VECTOR player_rot = player->GetRot();	//��]�l���擾
	VECTOR player_pos = player->GetPos();	//���W���擾

	//----------------------------
	// �J�����̒����_
	//----------------------------
	cameraInfo.look = player->GetPos();
	cameraInfo.look.y = player->GetPos().y + CAMERA_LOOK_OFFSET_Y;	//�v���C���[�̏����������

	//
	//�J�����̉�]
	//

	//�X�e�B�b�N�̒l���擾
	float stick_x = CInput::GetInstance()->GetStickValue(RIGHT_STICK_X);
	float stick_y = CInput::GetInstance()->GetStickValue(RIGHT_STICK_Y);


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