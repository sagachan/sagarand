#pragma once

#include "../Common.h"

enum PAD_TRIGGER
{
	LEFT_TRIGGER,		//���g���K�[
	RIGHT_TRIGGER,		//�E�g���K�[

	TRIGGER_MAX,		//�g���K�[�ő吔
};

enum PAD_STICK
{
	LEFT_STICK_X,		//���X�e�B�b�N��X
	LEFT_STICK_Y,		//���X�e�B�b�N��Y


	RIGHT_STICK_X,		//�E�X�e�B�b�N��X
	RIGHT_STICK_Y,		//�E�X�e�B�b�N��Y

	STICK_MAX,			//�X�e�B�b�N�̍ő吔
};


//���͗p���N���X
class CInputBase
{
public:
	//==================================================
	//���͋@��ɂ���đ��삪�ς��̂ŏ������z�֐��Ő錾
	//==================================================

	//�������ꂽ��
	virtual bool IsPush(int Key_code) = 0;

	//�P���ɉ����ꂽ��
	virtual bool IsDown(int Key_code) = 0;

	//�����������Ă��邩
	virtual bool IsKeep(int Key_code) = 0;

	//���ܗ����ꂽ��
	virtual bool IsRelease(int Key_code) = 0;

	//������
	virtual void Init() = 0;

	//�X�e�b�v
	virtual void Step() = 0;
};
