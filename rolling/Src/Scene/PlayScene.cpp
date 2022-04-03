//PlayScene.cpp
//�v���C�V�[��

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Field/FieldManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"
#include "../MyMath/MyMath.h"
#include "../Collision/Collision.h"
#include "../Collision/CollisionManager.h"


CPlayScene::CPlayScene()
{
	map_handle = 0;
	map_pos = { 0 };
}

CPlayScene::~CPlayScene()
{
}




//������
void CPlayScene::Init()
{
	//�v���C���[�Ǘ�������
	//�}�l�[�W���[�C���X�^���X����
	CPlayerManager::CreateInstance();
	//���������C���X�^���X���擾
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	//�}�l�[�W���[������
	player_manager->Init();


	
	

	////�A�j���[�V����������
	//CAnim3D::Init;


	//�t�B�[���h�Ǘ�������
	CFieldManager::CreateInstance();
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Init();

	//�G�l�~�[�Ǘ�������
	CEnemyManager::CreateInstance();
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	enemy_manager->Init();


	//�J�����Ǘ�������
	CCameraManager::CreateInstance();
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Init();
	camera_manager->SetNearFar(2.0f, 1500.0f);	//�j�A�t�@�[�ݒ�

	//�v���C�J�����ɕύX
	camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	////�t�F�[�h�A�E�g�̊J�n����
	//CFade::StartFade(CFade::FADE_OUT, CFade::FADE_COLOR_WHITE);

	//��������
	CSound::InitSound();

	//�����蔻�胂�f���ǂݍ���
	map_handle = MV1LoadModel("Data/Model/Field/done/Field.x");

	//�����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(map_handle, -1, TRUE);
	map_pos = { 0.0f, -2.0f, 0.0f };

	//�}�b�v�̉�]
	MV1SetPosition(map_handle, map_pos);

	//�����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1RefreshReferenceMesh(map_handle, -1, TRUE);

	//�����蔻��Ǘ�������
	CCollisionManager::CreateInstance();


	////�t�H�O��L���ɂ���
	//SetFogEnable(TRUE);
	//SetFogColor(255, 255, 255);
	//SetFogStartEnd(400.0f, 600.0f);
	
}


//�ǂݍ���
void CPlayScene::Load()
{	
	//�t�B�[���h�Ǘ��ǂݍ���
	CFieldManager::GetInstance()->Load();

	//�v���C���[�Ǘ��ǂݍ���
	CPlayerManager::GetInstance()->Load();

	//�G�l�~�[�Ǘ��ǂݍ���
	CEnemyManager::GetInstance()->Load();


	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_PLAY);
}


//�e�ϐ��Ȃǂ̏����l��ݒ�
void CPlayScene::Set()
{	
	//�t�B�[���h�Ǘ��Z�b�g
	CFieldManager::GetInstance()->Set();

	//�v���C���[�Ǘ��Z�b�g
	CPlayerManager::GetInstance()->Set();
	
	//�G�l�~�[�Ǘ��Z�b�g
	CEnemyManager::GetInstance()->Set();

	//���Đ�
	CSound::PlayBGM(CSound::BGM_PLAY);
}


//���t���[���Ăԏ���
void CPlayScene::Step()
{
	CCameraManager* camera_manager = CCameraManager::GetInstance();

	//====================
	//�I�u�W�F�N�g�֘A
	//====================

	//�X�e�b�v
	//�v���C�J�������Ȃ�i�f�o�b�O�J�������́A�v���C���[�͓������Ȃ��j
	if (camera_manager->GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//�v���C���[�Ǘ��X�e�b�v
		CPlayerManager::GetInstance()->Step();
	}

	
	//�t�B�[���h�Ǘ��X�e�b�v
	CFieldManager::GetInstance()->Step();

	//�G�l�~�[�Ǘ��X�e�b�v
	CEnemyManager::GetInstance()->Step();

	//�����蔻��Ǘ��X�e�b�v
	CCollisionManager::GetInstance()->Step();

	//�t�B�[���h�Ǘ��̍X�V
	CFieldManager::GetInstance()->Update();

	//�X�V
	//�v���C���[�Ǘ��̍X�V
	CPlayerManager::GetInstance()->Update();

	


	//�����蔻��
	CFieldManager::GetInstance()->GetRoad()->CheckCollision();
	CFieldManager::GetInstance()->GetWall()->CheckCollision();


	//====================
	//�J�����֘A
	//====================

	//�J�������_�E�����_�̑���
	camera_manager->Step();

	//�J�������_�E�����_�̔��f
	camera_manager->Update();

	//�e�J�����̋N������
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_C))
	{
		//���݂̃J����ID�ɂ���āA������U�蕪����
		switch (camera_manager->GetCameraID())
		{
		case CCameraManager::CAMERA_ID_PLAY:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
			//�f�o�b�O�J�����ɁA�v���C�J�����̍��W����
			VECTOR play_camera_pos = camera_manager->GetPlayCamera()->GetPosition();
			VECTOR play_camera_look = camera_manager->GetPlayCamera()->GetLook();
			camera_manager->GetDebugCamera()->Init(play_camera_pos, play_camera_look, VGet(0.0f, 1.0f, 0.0f));
			break;
		case CCameraManager::CAMERA_ID_DEBUG:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
			break;
		}
	}

	
	//-------------------------------
	//		�V�[���؂�ւ�
	//-------------------------------

	CInput* input = CInput::GetInstance();

	//�v���C���[�����񂾂�Q�[���I�[�o�[�V�[����
	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_BACK))
	{
		//�Q�[���I�[�o�[�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	//�v���C���[�̏�Ԃ��擾
	CPlayer* player_manager = CPlayerManager::GetInstance()->GetPlayer();

	//�v���C���[�̐����t���O���܂��Ă�����
	if (player_manager->GetAlive_Flg() == false)
	{
		//�Q�[���I�[�o�[�V�[���ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	//�N���A�t���O�������Ă�����
	if (player_manager->GetClearFlag())
	{
		//�Q�[���N���A�ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);

	}
}


//�`��
void CPlayScene::Draw()
{
	//�t�B�[���h�Ǘ��`��
	CFieldManager::GetInstance()->Draw();

	

	//�v���C���[�Ǘ��`��
	CPlayerManager::GetInstance()->Draw();


	//�G�l�~�[�Ǘ��`��
	CEnemyManager::GetInstance()->Draw();


	//�J�����Ǘ��`��
	CCameraManager::GetInstance()->Draw();

	
}


//�㏈��
void CPlayScene::Fin()
{
	//�v���C���[�Ǘ��̌㏈��
	//�v���C���[�Ǘ��擾
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	player_manager->Delete();	//�����I�ɍ폜���Ă�
	player_manager->Fin();		//�㏈��
	//�}�l�[�W���[�C���X�^���X�폜
	CPlayerManager::DeleteInstance();

	//�t�B�[���h�Ǘ��̌㏈��
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Delete();
	field_manager->Fin();
	CFieldManager::DeleteInstance();

	//�G�l�~�[�Ǘ��̌㏈��
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	enemy_manager->Delete();
	enemy_manager->Fin();
	CEnemyManager::DeleteInstance();


	//�J�����̌㏈��
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Fin();
	//�}�l�[�W���[�C���X�^���X�폜
	CCameraManager::DeleteInstance();

	//���㏈��
	CSound::FinSound();
}