#pragma once

#include "InputBase.h"

//���̓N���X
class CInput
{
public:

	//���͋@��̎��
	enum INPUT_KIND
	{
		INPUT_KIND_KEY,
		INPUT_KIND_MOUSE,
		INPUT_KIND_PAD,

		INPUT_KIND_NUM,
	};

private:

	//	�C���X�^���X
	static CInput* m_input;

	//	���͋@��
	CInputBase* m_inputKind[INPUT_KIND_NUM];

	/*CInput() {};*/
public:

	//	�C���X�^���X�擾
	static CInput* GetInstance();

	//	�C���X�^���X�폜
	void DeleteInstance();

	//	�������ꂽ��
	bool IsPush(INPUT_KIND input_kind, int key_code);

	//	�P���ɉ�����Ă��邩
	bool IsDown(INPUT_KIND input_kind, int key_code);

	//	�����������Ă��邩
	bool IsKeep(INPUT_KIND input_kind, int key_code);

	//	���͂Ȃ���Ă��邩
	bool IsRelease(INPUT_KIND input_kind, int key_code);

	//============================================
	//	�p�b�h�֘A
	//============================================

	//�p�b�h�̃g���K�[�l
	float GetTriggerValue(PAD_TRIGGER trigger);

	//�p�b�h�̃X�e�B�b�N�l
	float GetStickValue(PAD_STICK stick);

	//============================================
	//	�}�E�X�֘A
	//============================================

	//	�}�E�X���W�擾
	void GetMousePos(float& x, float& y);

	//	�}�E�X���W�Z�b�g
	void SetMousePos(float x, float y);

	void Init();
	void Step();
	static void Fin();

	~CInput() {};

public:
	//	�R���t�B�O�֘A

	//	�R���t�B�O�ɓo�^���Ă��铮��̓��͏��
	bool InputConf();

};