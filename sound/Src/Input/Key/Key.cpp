#include "Key.h"
#include "DxLib.h"

/*		static �錾		*/

CKey* CKey::m_key;


//�������ꂽ��
bool CKey::IsPush(int key_code)
{
	//�O�t���ŉ�����ĂȂ� ���� ���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//������ĂȂ��̂� false
	return false;
}

//�P���ɉ����ꂽ��
bool CKey::IsDown(int key_code)
{
	//�O�t���ł�����Ă��� ���� ���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

//�����������Ă��邩
bool CKey::IsKeep(int key_code)
{
	//�O�t���ŉ�����Ă��� ���� ���t���ŉ�����Ă��Ȃ�
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	return false;
}

//���ܗ����ꂽ��
bool CKey::IsRelease(int key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

void CKey::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

void CKey::Step()
{
	//�O�t���[���̃L�[���ϐ��ɋL�^���Ă���
	for (int index = 0; index < KEY_BUF_LEN; index++)
		preKeyBuf[index] = currentKeyBuf[index];

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf);
}