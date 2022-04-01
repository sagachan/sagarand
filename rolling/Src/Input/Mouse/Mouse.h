#pragma once

#include "../InputBase.h"

const int MOUSE_BUF_LEN = 3;

class CMouse : public CInputBase
{
private:

	//	�C���X�^���X
	static CMouse* m_mouse;

	CMouse() {};

	//���݂̃t���[���̃p�b�h�{�^�����
	char m_current_mouse_buf[MOUSE_BUF_LEN];

	//�O�t���[���̃p�b�h�̃{�^�����
	char m_pre_mouse_buf[MOUSE_BUF_LEN];

	//	���W
	float m_posX, m_posY;

public:
	~CMouse() {};

	static void CreateInstance() { if (!m_mouse)m_mouse = new CMouse; }
	static CMouse* GetInstance() { return m_mouse; }
	static void DeleteInstance() { if (m_mouse)delete m_mouse; m_mouse = nullptr; }

	//�������ꂽ��
	bool IsPush(int mouse_code);

	//�P���ɉ����ꂽ��
	bool IsDown(int mouse_code);

	//�����������Ă��邩
	bool IsKeep(int mouse_code);

	//���ܗ����ꂽ��
	bool IsRelease(int mouse_code);

	//	�}�E�X���W�擾
	void GetMousePos(float& x, float& y) { x = m_posX; y = m_posY; }

	//	�}�E�X���W�Z�b�g
	void SetMousePos(float x, float y) { m_posX = x; m_posY = y; }

	void Init();
	void Step();

};