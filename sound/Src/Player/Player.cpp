#include "Player.h"
#include "../Common.h"
#include <math.h>
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Animation/Animation.h"
#include "../Field/FieldManager.h"


namespace
{
	//�v���C���[�֘A
	const VECTOR PLAYER_START_POS = VGet(0.0f, 1.0f, 0.0f);	//�v���C���[�̍��W
	const float PLAYER_SPD = 1.0f;			//�v���C���[�̈ړ����x
	const float PLAYER_ADDSPD = 10.6f;		//������v���C���[���x
	const float PLAYER_m_rot_SPD = 0.01f;		//�v���C���[�̉�]���x
	const float PLAYER_m_rot_RETURN_SPEED = 1.5f; //�v���C���[�̉�]�̖߂�X�s�[�h
	const float PLAYER_MAX_ROT = 30.0f;		//�v���C���[�̍ő��]�p�x�i�R�O�x�܂Łj
	const float PLAYER_MIN_ROT = -30.0f;	//�v���C���[�̍ŏ���]�p�x�i�|�R�O�x�܂Łj
	const float PLAYER_JUMP_POWER = 0.5f;	//�v���C���[�̃W�����v��
	const float PLAYER_G_POWER = 0.5;		//�v���C���[�ɂ�����d�͂̋����ݒ�i���̐��l�͉��j
	const bool  HIT_INIT_FLG = false;		//�v���C���[�ɊO������ύX�\�ȓ����蔻��t���O�̏����l

	const int	PLAYER_BULLET_INTERVAL = 10;//�v���C���[�̒ʏ�e���ˎ���
	const float PLAYER_W = 4.0f;			//�v���C���[�̉���
	const float PLAYER_H = 4.0f;			//�v���C���[�̍���
	const float PLAYER_D = 4.0f;			//�v���C���[�̉��s��
	const float PLAYER_R = 4.5f;			//�v���C���[�̔��a

	const float	 PLAYER_DEAD_MIN_POS_Y = -30.0f;//�v���C���[�����S����ŏ�Y���W

	//��ʔ͈͊֘A
	const float RANGE_MAX_WIDTH = 14.0f;	//�����̍ő�͈�
	const float RANGE_MIN_WIDTH = -14.0f;	//�����̍ŏ��͈�
	const float RANGE_MAX_HEIGHT = 12.0f;	//�c���̍ő�͈�
	const float RANGE_MIN_HEIGHT = -12.0f;	//�c���̍ő�͈�

	//�W�����v�֘A
	const float ORIGIN_POS = 0.0f;			//���_���W
	const float JUMP_TOP = 25.0f;			//�W�����v�̍ō��n�_
	const float PLAYER_JUMP_TIME = 0.35f;	//�v���C���[�̔�Ԏ���
	const float PLAYER_JUMP_VAL = 0.0f;		//�W�����v��
	const float GRAVITY = 1.0f;				//�d��
	const float JUMP_CHARGE = 10.0f;		//�W�����v���̗��ߍd������
	const float JUMP_LANDING = 40.0f;		//�W�����v��̒��n�d������

	const float FRAME_DIS = 10.0f;
}




//�R���X�g���N�^
CPlayer::CPlayer()
{
	Init();
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
	Fin();
}



//������
void CPlayer::Init()
{
	m_hndl_ = 0;					//���f���n���h��
	m_pos_ = { 0.0f };				//���W
	m_old_pos_ = { 0.0f };			//�ړ��O�̍��W
	move_ = { 0.0f };				//�ړ���
	m_rot_ = { 0.0f };				//��]�l
	clear_flag_ = false;
}



//�ǂݍ��݁i���[�h�j
void CPlayer::Load()
{
	//���f���ǂݍ���
	m_hndl_ = MV1LoadModel("Data/Player/playerBall.x");
}



//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CPlayer::Set()
{
	m_pos_ = PLAYER_START_POS;
	state_ = PLAYER_STAND;			//�X�e�[�^�X
	is_alive_ = true;				//�����t���O
	size_ = VGet(PLAYER_W, PLAYER_H, PLAYER_D);
	m_rad_ = PLAYER_R;
	m_rot_ = { 0.0f, 0.2f, 0.0f };
}


//�������v���C���[�ʒu���W��
void CPlayer::Set(VECTOR pos)
{
	m_pos_ = pos;
}


//�v���C���[�������蔻��̉e�����󂯂鏈��
void CPlayer::HitSet()
{
	m_pos_.x = m_old_pos_.x;
	m_pos_.z = m_old_pos_.z;
}





//���t���[���Ăԏ����i����j
void CPlayer::Step()
{
	StepClearCheck();

	//�v���C���[�ɏ�ɏd�͂�������
	m_pos_.y -= GRAVITY;
	//m_pos_.y

	//�v���C���[�̈ړ��O�̍��W���L�^
	m_old_pos_ = m_pos_;
	move_.x = 0.0f;
	move_.z = 0.0f;
	m_rot_.x += 0.3f;
	
	StepInput();

	if(jumpFlg_ == false)
		StepJump();
	else
	{
		move_.y *= 0.9f;
	}


	if (m_pos_.y > JUMP_TOP)
	{
		move_.y = 0.0f;
	}


	//�O�Ɏ����I�ɐi��
	move_.z += PLAYER_SPD;


	//�v���C���[�̍��W�x�N�g�����A�s�񂩂�擾
	m_pos_ = CMyMath::VecAdd(m_pos_, move_);
	StepDead();//���S����
}


//�X�V
void CPlayer::Update()
{
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();

	//�v���C���[�̉�]
	MV1SetRotationXYZ(m_hndl_, m_rot_);

	//�v���C���[�̍��W
	MV1SetPosition(m_hndl_, m_pos_);
}


//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(m_hndl_);
	
}


//�폜
void CPlayer::Delete()
{
	//�v���C���[���f���폜
	MV1DeleteModel(m_hndl_);

	//�폜������0�������Ă���
	m_hndl_ = 0;
}


//�㏈��
void CPlayer::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (m_hndl_ != 0)
	{
		//�폜���Ă�ł���
		Delete();
	}
}


//���̓X�e�b�v
void CPlayer::StepInput()
{
	CInput* input = CInput::GetInstance();
	CRoad* field = CFieldManager::GetInstance()->GetRoad();
	
	m_old_pos_ = m_pos_;//�����O���W��ێ�

	//���ړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A))
	{
		move_.x -= PLAYER_SPD;
	}
	//�E�ړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D))
	{
		move_.x += PLAYER_SPD;

	}
}

//���S����
void CPlayer::StepDead()
{
	//��苗������������
	if (m_pos_.y < PLAYER_DEAD_MIN_POS_Y)
	{
		is_alive_ = false;//�t���O��܂�
	}
}

void CPlayer::StepJump()
{
	CRoad* field = CFieldManager::GetInstance()->GetRoad();

	//�t���[���n���h�����擾
	int frame_handle = field->GetFrameHandle();

	//�t���[���̐����擾
	int frame_max = MV1GetFrameNum(frame_handle);

	for(int index = 0; index < frame_max; index++)
	{
		VECTOR targetPos = MV1GetFramePosition(frame_handle, index);

		//�Ώۃt���[���܂ł̍��W���쐬
		float dis = CMyMath::GetDistance(targetPos, m_pos_);

		if (dis < FRAME_DIS)
		{
			move_.y = 5.0f;
			jumpFlg_ = true;

		}

	}

}

void CPlayer::StepClearCheck()
{
	CRoad* field = CFieldManager::GetInstance()->GetRoad();

	//�t���[���n���h�����擾
	int frame_clear_handle = field->GetFrameClearHandle();

	//�t���[���̐����擾
	int frame_max = MV1GetFrameNum(frame_clear_handle);

	for (int index = 0; index < frame_max; index++)
	{
		VECTOR targetPos = MV1GetFramePosition(frame_clear_handle, index);

		//�Ώۃt���[���܂ł̍��W���쐬
		float dis = CMyMath::GetDistance(targetPos, m_pos_);

		if (dis < FRAME_DIS)
		{
			clear_flag_ = true;
		}

	}

}