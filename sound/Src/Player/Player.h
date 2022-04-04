//Player.h
//�v���C���[�N���X

#pragma once

#include "DxLib.h"
#include "../Animation/Animation.h"


class CPlayer : public CAnim3D
{
public:

	enum PLAYER_ANIM_STATE
	{
		PLAYER_INIT,
		PLAYER_STAND,
		PLAYER_WALK,
		PLAYER_RUN,
		PLAYER_JUMP,
		PLAYER_THROW,
		PLAYER_RELOAD
	};

	enum PLAYER_ANIM_NO
	{
		INIT,
		THROW,
		ARMATURE,
		JUMP,
		STAND,
		WALK,
		RELOAD,
		ANIM_MAX_NUM
	};

public:
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();				//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Set(VECTOR pos);
	void HitSet();			//�����蔻��p�֐��Aoldpos�ɖ߂�
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��

	void StepInput();		//���̓X�e�b�v
	void StepDead();		//���S����
	void StepJump();		//�W�����v����
	void StepClearCheck();	//�N���A�̃`�F�b�N����

public:
	VECTOR GetSize() { return size_; }
	VECTOR GetForward() { return move_; }										//�v���C���[�̉��Z�x�N�g�����擾
	VECTOR GetForwardVec() { return forward_; }
	float GetRad() { return m_rad_; }											//�v���C���[�̔��a���擾
	bool GetAlive_Flg() { return is_alive_; }									//�v���C���[�̐����t���O�����擾
	bool GetClearFlag() { return clear_flag_; }									//�N���A�t���O���擾����
	bool SetJumpFlag(bool flg) { return jumpFlg_ = flg; }
	void SetAlive_Flg(bool flg) { is_alive_ = flg; }
	
private:
	VECTOR			move_;				//�ړ���
	VECTOR			forward_;			//�v���C���[�̌����x�N�g���i�[
	VECTOR			posSave;			//�ړ��O�̒n�_�̃Z�[�u
	VECTOR			size_;				//�傫��
	bool			moveFlg_;			//���݈ړ��\���ǂ���
	bool			is_alive_;			//�����t���O
	bool			hitFlg_;			//�ʃN���X�����蔻��t���O
	bool			jumpFlg_;
	float			jumpTime_;			//�W�����v�̎���
	bool			clear_flag_;		//�N���A�t���O

	PLAYER_ANIM_STATE	state_;			//��ԁi�X�e�[�^�X�j
	PLAYER_ANIM_STATE	old_state_;		//�O���[�v��ԁi�X�e�[�^�X�j
	
};