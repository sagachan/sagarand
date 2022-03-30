//CameraManager.cpp
//�J�����Ǘ�
//C***Camera�ւ̃A�N�Z�X�͕K��CCameraManager���o�R

#include "CameraManager.h"

//CCameraManager�̎��̐錾�A������
CCameraManager* CCameraManager::instance_ = nullptr;

//�R���X�g���N�^
CCameraManager::CCameraManager()
	:m_eCurrentCameraID(CAMERA_ID_PLAY)
{
	//CPlayCamera�̃R���X�g���N�^�͎����ŌĂ΂�܂�
	//CDebugCamera�̃R���X�g���N�^�͎����ŌĂ΂�܂�
}

//�f�X�g���N�^
CCameraManager::~CCameraManager()
{
	//CPlayCamera�̃f�X�g���N�^�͎����ŌĂ΂�܂�
	//CDebugCamera�̃f�X�g���N�^�͎����ŌĂ΂�܂�
}


//������
void CCameraManager::Init()
{
	//�e�J�����̏�����
	m_PlayCamera.Init(VGet(0.0f, 4.0f, -28.0f), CPlayerManager::GetInstance()->GetPlayer()->GetPosition(), VGet(0.0f, 1.0f, 0.0f));
	m_DebugCamera.Init(VGet(0.0f, 8.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}


//�X�e�b�v
void CCameraManager::Step()
{
	//���݂̃J����ID�ɂ���ď�����U�蕪����
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_PlayCamera.Step();
		break;
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Step();
		break;
	}
}


//���f
void CCameraManager::Update()
{
	//���݂̃J����ID�ɂ���ď�����U�蕪����
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_PlayCamera.Update();
		break;
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Update();
		break;
	}
}


//�`��
void CCameraManager::Draw()
{
	//���݂̃J����ID�ɂ���ď�����U�蕪����
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Draw();
		break;
	}
}


//�㏈��
void CCameraManager::Fin()
{
	//�e�J�����̂��Ə���
	m_PlayCamera.Fin();
	m_DebugCamera.Fin();
}


//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}


//�����̃J�����ɕύX����
void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
{
	m_eCurrentCameraID = cameraID;
}