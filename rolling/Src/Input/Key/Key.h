#pragma once

#include "../InputBase.h"

const int KEY_BUF_LEN = 256;

class CKey : public CInputBase
{
private:
	CKey() {};

	//	�C���X�^���X
	static CKey* m_key;

	//���݃t���[���̃L�[���
	char currentKeyBuf[KEY_BUF_LEN];

	//�O�t���[���̃L�[���
	char preKeyBuf[KEY_BUF_LEN];
public:

	static void CreateInstance() { if (!m_key)m_key = new CKey; }
	static CKey* GetInstance() { return m_key; }
	static void DeleteInstance() { if (m_key)delete m_key; m_key = nullptr; }

	//�������ꂽ��
	bool IsPush(int key_code);

	//�P���ɉ����ꂽ��
	bool IsDown(int key_code);

	//�����������Ă��邩
	bool IsKeep(int key_code);

	//���ܗ����ꂽ��
	bool IsRelease(int key_code);

	void Init();
	void Step();

	~CKey() {};

};