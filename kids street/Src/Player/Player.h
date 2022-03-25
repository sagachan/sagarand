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
	

public:
	VECTOR GetPos() { return m_pos_; }											//���W�̎擾
	VECTOR GetRot() { return m_rot_; }											//��]�l�̎擾
	VECTOR GetSize() { return size_; }
	VECTOR GetForward() { return move_; }										//�v���C���[�̉��Z�x�N�g�����擾
	VECTOR GetForwardVec() { return forward_; }
	float GetRad() { return m_radius; }											//�v���C���[�̔��a���擾
	bool GetAlive_Flg() { return is_alive_; }									//�v���C���[�̐����t���O�����擾
	
	
	
private:
	VECTOR			move_;				//�ړ���
	bool			move_flg_;			//���݈ړ��\���ǂ���
	VECTOR			forward_;			//�v���C���[�̌����x�N�g���i�[
	VECTOR			pos_save;			//�ړ��O�̒n�_�̃Z�[�u
	bool			is_alive_;			//�����t���O
	bool			hit_flg_;			//�ʃN���X�����蔻��t���O
	PLAYER_ANIM_STATE	state_;			//��ԁi�X�e�[�^�X�j
	PLAYER_ANIM_STATE	old_state_;		//�O���[�v��ԁi�X�e�[�^�X�j
	float			jump_time_;			//�W�����v�̎���
	float			m_radius;			//���a
	VECTOR			size_;				//�傫��
};