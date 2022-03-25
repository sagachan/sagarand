//SceneManager.cpp
//�V�[���Ǘ�
//�e�V�[���ւ̃A�N�Z�X�͕K��CSceneManager���o�R

#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

//CSceneManager�̎��̐錾�A������
CSceneManager* CSceneManager::instance_ = nullptr;

CSceneManager::CSceneManager()
:scene_(nullptr)
, m_eCurrentSceneState(SCENE_STATE_INIT)
{
}

CSceneManager::~CSceneManager()
{
}


//������
void CSceneManager::Init()
{
	//�����̓V�[���Ǘ��̏������ł����āA
	//�e�V�[���̏������ł͂Ȃ�
}


//���[�v
void CSceneManager::Loop()
{
	//���݂̃V�[���̏�Ԃɂ���āA������U�蕪����
	switch (m_eCurrentSceneState)
	{

	//�V�[��������
	case SCENE_STATE_INIT:
		scene_->Init();
		m_eCurrentSceneState = SCENE_STATE_LOAD;
		break;

	//�V�[���ǂݍ���
	case SCENE_STATE_LOAD:
		scene_->Load();
		m_eCurrentSceneState = SCENE_STATE_SET;
		break;

	//�V�[���Z�b�g
	case SCENE_STATE_SET:
		scene_->Set();
		m_eCurrentSceneState = SCENE_STATE_LOOP;

	//�V�[���J��Ԃ�
	case SCENE_STATE_LOOP:
		scene_->Step();
		scene_->Draw();	//�`��̓X�e�b�v�̌�ɌĂ�
		break;

	//�V�[���㏈��
	case SCENE_STATE_FIN:
		scene_->Fin();
		ChangeNextScene();
		break;
	}
}


//�㏈��
void CSceneManager::Fin()
{
}


//�P�ԍŏ��̃V�[�����J�n����
void CSceneManager::StartFirstScene(SCENE_ID sceneID)
{
	//���ɉ����V�[���������Ă�̂ł���Α��I��
	if (scene_)return;

	//�V�[���𐶐����ď���������J�n����
	CreateScene(sceneID);
	m_eCurrentSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_INIT;
}


//�����̃V�[���ɕύX����
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//���ɑJ�ڂ���V�[�����o���Ă����ďI��������
	m_eNextSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_FIN;
}


//�V�[���𐶐�����
void CSceneManager::CreateScene(SCENE_ID sceneID)
{
	//�V�[���𐶐�
	switch (sceneID) 
	{
	case SCENE_ID_TITLE: scene_ = new CTitleScene; break;
	case SCENE_ID_PLAY: scene_ = new CPlayScene; break;
	case SCENE_ID_GAME_OVER: scene_ = new CGameOverScene; break;
	case SCENE_ID_GAME_CLEAR: scene_ = new CGameClearScene; break;
	}
}


//���̃V�[���ɑJ��
void CSceneManager::ChangeNextScene()
{
	//�I�������V�[�����폜
	delete scene_;
	//���̃V�[���𐶐�
	CreateScene(m_eNextSceneID);
	//���݂̃V�[��ID�ݒ�
	m_eCurrentSceneID = m_eNextSceneID;
	//��Ԃ��������ɖ߂�
	m_eCurrentSceneState = SCENE_STATE_INIT;
}