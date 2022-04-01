//CameraManager.h
//�J�����Ǘ�
//C***Camera�ւ̃A�N�Z�X�͕K��CCameraManager���o�R

#pragma once

#include "PlayCamera.h"
#include "DebugCamera.h"

//�J�����Ǘ��N���X
class CCameraManager
{
public:
	//�J����ID
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_DEBUG,	//CDebugCamera
	};

public:
	CCameraManager();	//�R���X�g���N�^
	~CCameraManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_)instance_ = new CCameraManager; }
	//�C���X�^���X�擾
	static CCameraManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();	//������
	void Step();	//�X�e�b�v
	void Update();	//���f
	void Draw();	//�`��
	void Fin();		//�㏈��

	//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
	void SetNearFar(float near_val, float far_val);

	//�����̃J�����ɕύX����
	void ChangeCamera(CAMERA_ID cmaeraID);

	//���݂̃J����ID���擾
	CAMERA_ID GetCameraID() { return m_eCurrentCameraID; }

	//�v���C�J�����N���X���擾
	CPlayCamera* GetPlayCamera() { return &m_PlayCamera; }

	//�f�o�b�O�J�����N���X���擾
	CDebugCamera* GetDebugCamera() { return &m_DebugCamera; }

private:
	//�C���X�^���X
	static CCameraManager* instance_;

	//���݂̃J����ID
	CAMERA_ID m_eCurrentCameraID;

	//�e�J�����̕ϐ�
	CPlayCamera m_PlayCamera;	//�v���C�J�����N���X
	CDebugCamera m_DebugCamera;	//�f�o�b�O�J�����N���X
};