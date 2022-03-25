#pragma once

#include "../InputBase.h"

//----------- XInput�{�^�����͒�` -----------//
/*
	 XINPUT_BUTTON_DPAD_UP			(0)		// �f�W�^�������{�^����
	 XINPUT_BUTTON_DPAD_DOWN		(1)		// �f�W�^�������{�^����
	 XINPUT_BUTTON_DPAD_LEFT		(2)		// �f�W�^�������{�^����
	 XINPUT_BUTTON_DPAD_RIGHT		(3)		// �f�W�^�������{�^���E
	 XINPUT_BUTTON_START			(4)		// START�{�^��
	 XINPUT_BUTTON_BACK				(5)		// BACK�{�^��
	 XINPUT_BUTTON_LEFT_THUMB		(6)		// ���X�e�B�b�N��������
	 XINPUT_BUTTON_RIGHT_THUMB		(7)		// �E�X�e�B�b�N��������
	 XINPUT_BUTTON_LEFT_SHOULDER	(8)		// LB�{�^��
	 XINPUT_BUTTON_RIGHT_SHOULDER	(9)		// RB�{�^��
	 XINPUT_BUTTON_A				(12)	// A�{�^��
	 XINPUT_BUTTON_B				(13)	// B�{�^��
	 XINPUT_BUTTON_X				(14)	// X�{�^��
	 XINPUT_BUTTON_Y				(15)	// Y�{�^��
*/

//----------- �Q�[���p�b�h�̏���������\���̂̓��e(XINPUT_STATE�\����) -----------//
/*
	struct XINPUT_STATE
	{
		unsigned char	Buttons[ 16 ] ;	// �{�^���P�U��( �Y���ɂ� XINPUT_BUTTON_DPAD_UP �����g�p����A
						//			0:������Ă��Ȃ�  1:������Ă��� )
		unsigned char	LeftTrigger ;	// ���g���K�[( 0�`255 )
		unsigned char	RightTrigger ;	// �E�g���K�[( 0�`255 )
		short		ThumbLX ;	// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
		short		ThumbLY ;	// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
		short		ThumbRX ;	// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
		short		ThumbRY ;	// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
	} ;
*/

//�p�b�h�̃{�^�����͂̐�
const int PAD_BUTTON_LEN = 16;

//�p�b�h���̓N���X
class CPad : public CInputBase
{
public:
	CPad();		//�R���X�g���N�^
	~CPad();	//�f�X�g���N�^

public:
	/***�V���O���g��***/	//�p�b�h�͂P�����v��Ȃ�����
	static void CreateInstance() { if (!pad_)pad_ = new CPad; }
	static CPad* GetInstance() { return pad_; }
	static void DeleteInstance() { if (pad_)delete pad_; pad_ = nullptr; }

public:
	//������
	void Init() override;

	//�X�e�b�v
	void Step() override;

	//�������ꂽ��
	bool IsPush(int button_code) override;

	//�P���ɉ����ꂽ��
	bool IsDown(int button_code) override;

	//�����������Ă��邩
	bool IsKeep(int button_code) override;

	//���ܗ����ꂽ��
	bool IsRelease(int button_code) override;

	//�g���K�[�l�̎擾�i0.0f�`1.0f�̒l��Ԃ��j
	//���O�ɋ߂Â��قǎア�������݁A�P�ɋ߂Â��قǋ�����������
	float GetTriggerValue(PAD_TRIGGER trigger_kind);

	//�X�e�B�b�N�l�̎擾�i-1.0f�`1.0f�̒l��Ԃ��j
	//���u�|�P�ȏ�O�����v�Ȃ獶�A�܂��͉�
	//�@�u�O���傫���P�ȉ��v�Ȃ�E�A�܂��͏�ɌX���Ă���
	float GetStickValue(PAD_STICK stick_kind);

private:
	//�C���X�^���X
	static CPad* pad_;

	//���݃t���[���̃{�^�����
	unsigned char current_button_buf_[PAD_BUTTON_LEN];

	//�O�t���[���̃{�^�����
	unsigned char pre_button_buf_[PAD_BUTTON_LEN];

	//�p�b�h�̃g���K�[���
	float current_trigger_buf_[TRIGGER_MAX];
	float pre_trigger_buf_[TRIGGER_MAX];

	//�p�b�h�̃X�e�B�b�N���
	float stick_buf_[STICK_MAX];
};