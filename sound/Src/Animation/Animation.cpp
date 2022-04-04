#include "Animation.h"

//�A�j���Đ��^�C�v
enum 
{
	ANIMSTATE_LOOP,		//�J��Ԃ����[�v
	ANIMSTATE_END,		//�ŏI�t���[���Œ�~

	ANIMSTATE_NUM		//�A�j���Đ��^�C�v��
};

//�R���X�g���N�^
CAnim3D::CAnim3D()
{
	//---���N���X�̃R���X�g���N�^�������Ő�ɌĂ΂�Ă���---//

	ZeroMemory(&anim_data_, sizeof(anim_data_));	//�A�j���Đ��֘A�f�[�^
}

//�f�X�g���N�^
CAnim3D::~CAnim3D()
{
	DetachAnim();
}

//������
void CAnim3D::Init()
{
	CModel::Init();	//���N���X�����ɏ�����
	ZeroMemory(&anim_data_, sizeof(anim_data_));	//�A�j���Đ��֘A�f�[�^
}

//�X�V����
void CAnim3D::Update()
{
	//���f���̍X�V�i���W�A��]�l�A�g�k�l�̐ݒ�j
	CModel::Update();

	//�A�j���[�V�����̍X�V
	UpdateAnim();
}

//�㏈��
void CAnim3D::Fin()
{
	//�A�j���[�V�������f�^�b�`
	DetachAnim();

	//���N���X���ォ��j���i��ɃA�j�����f�^�b�`���Ă���A�n���h�����폜�j
	CModel::Fin();
}


//���[�v�A�j�����N�G�X�g
void CAnim3D::RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	//�����������[�v�ɕς���
	anim_data_.state_ = ANIMSTATE_LOOP;
}

//�G���h���[�v�A�j�����N�G�X�g
void CAnim3D::RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	//���������G���h���[�v�ɕς���
	anim_data_.state_ = ANIMSTATE_END;
}

//�A�j�����N�G�X�g
void CAnim3D::Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	//�A�j������
	DetachAnim();

	//�A�j���Đ����e��f�[�^���Z�b�g
	anim_data_.handle_ = MV1AttachAnim(m_hndl_, iAnimID, iAnimSrcHndl, NameCheck);
	anim_data_.id_ = iAnimID;
	anim_data_.end_frm_ = MV1GetAnimTotalTime(m_hndl_, iAnimID);
	anim_data_.frm_ = 0.0f;
	
	anim_data_.spd_ = iAnimSpd;
}

//�A�j���[�V�����f�^�b�`
void CAnim3D::DetachAnim()
{
	if (anim_data_.handle_ != -1)
	{
		MV1DetachAnim(m_hndl_, anim_data_.handle_);
		anim_data_.handle_ = -1;
	}
}

//�A�j���A�b�v�f�[�g
void CAnim3D::UpdateAnim()
{
	if (anim_data_.handle_ == -1)return;	//�A�j���[�V�������Đ�����Ă��Ȃ�

	//�A�j���[�V�������x�X�V
	anim_data_.frm_ += anim_data_.spd_;

	if (anim_data_.frm_ >= anim_data_.end_frm_)
	{
		//�ŏI�t���[���܂ŗ�����A��Ԃɍ��킹�ē����ς���
		switch (anim_data_.state_)
		{
		//���[�v�͍ŏ��ɖ߂邾��
		case ANIMSTATE_LOOP:
			anim_data_.frm_ = 0.0f;
			break;
		//�G���h���[�v�͍Ō�Ŏ~�߂�
		case ANIMSTATE_END:
			anim_data_.frm_ = anim_data_.end_frm_;
			break;
		}
	}

	//�Đ����Ԑݒ�
	MV1SetAttachAnimTime(m_hndl_, anim_data_.handle_, anim_data_.frm_);
}