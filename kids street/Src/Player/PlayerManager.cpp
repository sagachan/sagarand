//PlayerManager.cpp
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R

#include "PlayerManager.h"

//CPlayerManager�̎��̐錾�A������
CPlayerManager* CPlayerManager::instance_ = nullptr;


//�R���X�g���N�^
CPlayerManager::CPlayerManager()
{
	//CPlayer�̃R���X�g���N�^�͎����ŌĂ΂�܂�
}

//�f�X�g���N�^
CPlayerManager::~CPlayerManager()
{
	//CPlayer�̃f�X�g���N�^�͎����ŌĂ΂�܂�
}


//������
void CPlayerManager::Init()
{
	//�v���C���[�̏��������Ă�
	player_.Init();
}


//�ǂݍ���
void CPlayerManager::Load()
{
	//�v���C���[�̓ǂݍ���
	player_.Load();
}


//�Z�b�g
void CPlayerManager::Set()
{
	//�v���C���[�̃Z�b�g
	player_.Set();
}


//�X�e�b�v
void CPlayerManager::Step()
{
	//�v���C���[�̃X�e�b�v
	player_.Step();
}


//���f
void CPlayerManager::Update()
{
	//�v���C���[�̔��f
	player_.Update();
}


//�`��
void CPlayerManager::Draw()
{
	//�v���C���[�̕`��
	player_.Draw();
}


//�폜
void CPlayerManager::Delete()
{
	//�v���C���[�폜
	player_.Delete();
}


//�㏈��
void CPlayerManager::Fin()
{
	//�v���C���[�̌㏈�����Ă�
	player_.Fin();
}