#include "Mouse.h"
#include "DxLib.h"

const int MOUSE_INPUT_BUF[MOUSE_BUF_LEN] = { MOUSE_INPUT_MIDDLE, MOUSE_INPUT_LEFT ,MOUSE_INPUT_RIGHT };

/*		static �錾		*/

CMouse* CMouse::m_mouse;


//�������ꂽ��
bool CMouse::IsPush(int mouse_code)
{
	if (m_current_mouse_buf[mouse_code] == 1 && m_pre_mouse_buf[mouse_code] == 0)
		return true;

	return false;
}

//�P���ɉ����ꂽ��
bool CMouse::IsDown(int mouse_code)
{
	if (m_current_mouse_buf[mouse_code] == 1)
		return true;

	return false;
}

//�����������Ă��邩
bool CMouse::IsKeep(int mouse_code)
{
	if (m_current_mouse_buf[mouse_code] == 1 && m_pre_mouse_buf[mouse_code] == 1)
		return true;

	return false;
}

//���ܗ����ꂽ��
bool CMouse::IsRelease(int mouse_code)
{
	if (m_current_mouse_buf[mouse_code] == 0 && m_pre_mouse_buf[mouse_code] == 1)
		return true;

	return false;
}

void CMouse::Init()
{
	for (int buf_index = 0; buf_index < MOUSE_BUF_LEN; buf_index++)
	{
		m_current_mouse_buf[buf_index] = '\0';
		m_pre_mouse_buf[buf_index] = '\0';
	}
}

void CMouse::Step()
{
	//���t���̃L�[����O�t���z��Ɉړ�
	memcpy(m_pre_mouse_buf, m_current_mouse_buf, sizeof(char) * MOUSE_BUF_LEN);

	for (int mouse_index = 0; mouse_index < MOUSE_BUF_LEN; mouse_index++)
	{
		if ((GetMouseInput() & MOUSE_INPUT_BUF[mouse_index]) != 0)
			m_current_mouse_buf[mouse_index] = 1;
		else
			m_current_mouse_buf[mouse_index] = 0;
	}
}