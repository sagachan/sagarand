#pragma once

#include "../InputBase.h"

//	���̓R���t�B�O�N���X
class CInputConfig
{
public:

	static const int KEY_LEN = 40;
	static const int MOUSE_LEN = 3;
	static const int PAD_LEN = 8;

private:

	//�V���O���g��
	static CInputConfig* m_Instance;

public:

	static CInputConfig* GetInstance();

private:

	int  *KeyConfHandle;	//�L�[�摜
	int	 *PadConfHandle;	//�p�b�h�摜
	int  *MouseConfHandle;	//�}�E�X�摜
	int  NoneConfHandle;	//�Ȃɂ��Ȃ��Ƃ�
	bool IsInputCheck;	//���͂��I�������
	bool IsStepCheck;	//�J�n�p

	//	���̓r�b�g���\����
	struct InputBit
	{
		int KeyBit;		//�L�[�{�[�h
		int PadBit;		//�p�b�h
		int MouseBit;	//�}�E�X
		int TrigerBit;	//�p�b�h�g���K�[
	};

	//	���͏��
	InputBit Input_bit[INPUT_NUM];

	
private:
	CInputConfig()
		:Input_bit{0 },
		IsInputCheck(false),
		IsStepCheck(false)
	{};

public:
	//	�e����̓���
	//	����	�F���͂�������
	bool InputPush(const INPUT_CONF& kind);
	bool InputDown(const INPUT_CONF& kind);
	bool InputKeep(const INPUT_CONF& kind);
	bool InputRelease(const INPUT_CONF& kind);
	bool InputTriger(const INPUT_CONF& kind);

public:

	//	�C���v�b�g�R���t�B�O������
	void InputConfigInit();

	//	���̓L�[�A�{�^���ύX
	//	����	�Fconf_kind	�ύX����L�[�܂��̓{�^���̓���̎��
	//		�FIsKey		�ύX���镨���L�[���ǂ��� ( true = �L�[ : false = �p�b�h )
	void InputConfigStep(const INPUT_CONF& conf_kind, const bool& IsKey);

	//	���ݓo�^����Ă���L�[�A�{�^����`��i�L�[�R���t�B�O�ݒ蒆�̂݁j
	void InputConfigDraw();

	//	�폜
	void Delete();

	void SetInputCheck(const bool& check) { IsInputCheck = check; }
	bool GetInputCheck() { return IsInputCheck; }
};