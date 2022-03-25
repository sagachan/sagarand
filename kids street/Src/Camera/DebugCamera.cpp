//DebugCamera.cpp
//�f�o�b�O�p�̃J����

#include "DebugCamera.h"
#include "CameraManager.h"
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"


namespace
{
	const float CAMERA_MOVE_SPD = 0.2f;		//���_�̑��x
	const float CAMERA_LOOK_SPD = 0.2f;		//�����_�̑��x
	const float CAMERA_LOOK_Y_DIST = 20.0f;	//�����_�̏㉺�ɓ������鋗��
}

//�R���X�g���N�^
CDebugCamera::CDebugCamera()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//�f�X�g���N�^
CDebugCamera::~CDebugCamera()
{	
}


//�������i�����Ȃ��j
void CDebugCamera::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}


//�������i��������j
void CDebugCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}


//�X�e�b�v
void CDebugCamera::Step()
{
	//----------------------------
	// �J�����̒����_
	//----------------------------

	//�����_�����
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_UP))
		m_vLook.y += CAMERA_LOOK_SPD;
	//�����_������
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_DOWN))
		m_vLook.y -= CAMERA_LOOK_SPD;
	//�����_������
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_LEFT))
	{
		//���_���璍���_�܂ł̃x�N�g�������߂�
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//���ړ��p�̃x�N�g�������߂�
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//���ړ��p�̃x�N�g���𐳋K��
		left_move = CMyMath::VecNormalize(left_move);
		//�����Ƃ����ړ��ʂɂ���i�K�؂Ȑ��l�ɂ���j
		left_move = CMyMath::VecScale(left_move, CAMERA_LOOK_SPD);

		//�����_�ɉ��Z
		m_vLook = CMyMath::VecAdd(m_vLook, left_move);
	}
	//�����_���E��
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_RIGHT))
	{
		//���_���璍���_�܂ł̃x�N�g�������߂�
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//���ړ��p�̃x�N�g�������߂�
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//���ړ��p�̃x�N�g���𐳋K��
		left_move = CMyMath::VecNormalize(left_move);
		//�����Ƃ����ړ��ʂɂ���i�K�؂Ȑ��l�ɂ���j
		left_move = CMyMath::VecScale(left_move, CAMERA_LOOK_SPD);

		//���ړ��p�Ȃ̂ŁA�E�ړ��p�ɕϊ�
		VECTOR right_move = { 0 };
		right_move.x = -left_move.x;
		right_move.y = -left_move.y;
		right_move.z = -left_move.z;

		//�����_�ɉ��Z
		m_vLook = CMyMath::VecAdd(m_vLook, right_move);
	}


	//�����_�����i���_����}20�܂Łj
	if (m_vLook.y - m_vPos.y > CAMERA_LOOK_Y_DIST)
		m_vLook.y = CAMERA_LOOK_Y_DIST + m_vPos.y;
	else if (m_vLook.y - m_vPos.y < -CAMERA_LOOK_Y_DIST)
		m_vLook.y = -CAMERA_LOOK_Y_DIST + m_vPos.y;


	//----------------------------
	// �J�����̎��_�i���W�j
	//----------------------------

	//�O�ֈړ�
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_W))
	{
		//���_���璍���_�ւ̃x�N�g�������߂�i�O�ړ��p�x�N�g���j
		VECTOR front_move = CMyMath::VecCreate(m_vPos, m_vLook);
		//���K������
		front_move = CMyMath::VecNormalize(front_move);
		//�K�؂ȑ傫���ɂ���
		front_move = CMyMath::VecScale(front_move, CAMERA_MOVE_SPD);

		//���_�E�����_�ɂ��ꂼ����Z
		m_vPos = CMyMath::VecAdd(m_vPos, front_move);
		m_vLook = CMyMath::VecAdd(m_vLook, front_move);
	}
	//���ֈړ�
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_S))
	{
		//���_���璍���_�ւ̃x�N�g�������߂�i�O�ړ��p�x�N�g���j
		VECTOR front_move = CMyMath::VecCreate(m_vPos, m_vLook);
		//���K������
		front_move = CMyMath::VecNormalize(front_move);
		//�K�؂ȑ傫���ɂ���
		front_move = CMyMath::VecScale(front_move, CAMERA_MOVE_SPD);

		//�O�ړ��p�Ȃ̂ŁA���ړ��p�ɕϊ�
		VECTOR back_move = { 0 };
		back_move.x = -front_move.x;
		back_move.y = -front_move.y;
		back_move.z = -front_move.z;

		//���_�E�����_�ɂ��ꂼ����Z
		m_vPos = CMyMath::VecAdd(m_vPos, back_move);
		m_vLook = CMyMath::VecAdd(m_vLook, back_move);
	}
	//���ֈړ�
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_A))
	{
		//���_���璍���_�܂ł̃x�N�g�������߂�
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//���ړ��p�̃x�N�g�������߂�
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//���ړ��p�̃x�N�g���𐳋K��
		left_move = CMyMath::VecNormalize(left_move);
		//�����Ƃ����ړ��ʂɂ���i�K�؂Ȑ��l�ɂ���j
		left_move = CMyMath::VecScale(left_move, CAMERA_MOVE_SPD);

		//���_�E�����_�ɂ��ꂼ����Z
		m_vPos = CMyMath::VecAdd(m_vPos, left_move);
		m_vLook = CMyMath::VecAdd(m_vLook, left_move);
	}
	//�E�ֈړ�
	if (CInput::GetInstance()->IsDown(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_D))
	{
		//���_���璍���_�܂ł̃x�N�g�������߂�
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//���ړ��p�̃x�N�g�������߂�
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//���ړ��p�̃x�N�g���𐳋K��
		left_move = CMyMath::VecNormalize(left_move);
		//�����Ƃ����ړ��ʂɂ���i�K�؂Ȑ��l�ɂ���j
		left_move = CMyMath::VecScale(left_move, CAMERA_MOVE_SPD);

		//�E�ړ��p�̃x�N�g���ɂ��邽�߁A���ړ��p�̃x�N�g���𔽓]
		VECTOR right_move = { 0 };
		right_move.x = -left_move.x;
		right_move.y = -left_move.y;
		right_move.z = -left_move.z;

		//���_�E�����_�ɂ��ꂼ����Z
		m_vPos = CMyMath::VecAdd(m_vPos, right_move);
		m_vLook = CMyMath::VecAdd(m_vLook, right_move);
	}
}


//���f
void CDebugCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}


//�`��i�����_�ɋ��̂�`��j
void CDebugCamera::Draw()
{
	//���̂�`��
	DrawSphere3D(m_vLook, 0.5f, 5, GetColor(0, 255, 255), GetColor(0, 0, 0), false);

	//�\������
	DrawFormatString(500, 10, GetColor(255, 255, 0), "�f�o�b�O�J�������[�h");
	DrawFormatString(500, 25, GetColor(255, 255, 255), 
		"Pos �F( %.1f, %.1f, %.1f )", m_vPos.x, m_vPos.y, m_vPos.z);
	DrawFormatString(500, 40, GetColor(255, 255, 255),
		"Look�F( %.1f, %.1f, %.1f )", m_vLook.x, m_vLook.y, m_vLook.z);
}


//�㏈��
void CDebugCamera::Fin()
{
}