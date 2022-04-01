#include "Input.h"
#include "Key/Key.h"
#include "Mouse/Mouse.h"
#include "Pad/Pad.h"

/*		static�錾		*/

CInput* CInput::m_input;	//�C���v�b�g

//	�C���X�^���X�擾
CInput* CInput::GetInstance()
{
	if (!m_input)
		m_input = _NEW(CInput);

	return m_input;
}

//	�C���X�^���X�폜
void CInput::DeleteInstance()
{
	if (m_input)
		_DELETE(m_input);

	m_input = nullptr;
}


//	������
void CInput::Init()
{

	//���͋@����擾
	CKey::CreateInstance();
	CMouse::CreateInstance();
	CPad::CreateInstance();
	
	m_inputKind[INPUT_KIND_KEY] = CKey::GetInstance();
	m_inputKind[INPUT_KIND_MOUSE] = CMouse::GetInstance();
	m_inputKind[INPUT_KIND_PAD] = CPad::GetInstance();
	

	//	�e���͋@�평����
	for (int input_index = 0; input_index < INPUT_KIND_NUM; input_index++)
	{
		m_inputKind[input_index]->Init();
	}

	
}

//�X�e�b�v
void CInput::Step()
{
	for (int input_index = 0; input_index < INPUT_KIND_NUM; input_index++)
		m_inputKind[input_index]->Step();
}

//	�������ꂽ��
bool CInput::IsPush(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsPush(key_code);
}

//	�P���ɉ�����Ă��邩
bool CInput::IsDown(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsDown(key_code);
}

//	�����������Ă��邩
bool CInput::IsKeep(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsKeep(key_code);
}

//	���͂Ȃ��ꂽ��
bool CInput::IsRelease(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsRelease(key_code);
}

//	�g���K�[�l�擾
float CInput::GetTriggerValue(PAD_TRIGGER trigger)
{
	return CPad::GetInstance()->GetTriggerValue(trigger);
}

//	�X�e�B�b�N�l�擾
float CInput::GetStickValue(PAD_STICK stick)
{
	return CPad::GetInstance()->GetStickValue(stick);
}

//	�}�E�X���W�擾
void CInput::GetMousePos(float &x, float &y)
{
	CMouse::GetInstance()->GetMousePos(x, y);
}

//	�}�E�X���W�Z�b�g
void CInput::SetMousePos(float x, float y)
{
	CMouse::GetInstance()->SetMousePos(x, y);
}


//�㏈��
void CInput::Fin()
{
	//	���͏��폜
	CKey::GetInstance()->DeleteInstance();
	CPad::GetInstance()->DeleteInstance();
	CMouse::GetInstance()->DeleteInstance();

	
}