//FieldManager.cpp
//�t�B�[���h�Ǘ�
//CField�ւ̃A�N�Z�X�͕K��CFieldManager���o�R

#include "FieldManager.h"
//CFieldManager�̎��̐錾�A������
CFieldManager* CFieldManager::instance_ = nullptr;

//�R���X�g���N�^
CFieldManager::CFieldManager()
{
}

//�f�X�g���N�^
CFieldManager::~CFieldManager()
{
}

void CFieldManager::Init()
{
	road_.Init();
	wall_.Init();
}


//�ǂݍ���
void CFieldManager::Load()
{
	road_.Load();
	wall_.Load();
}



//�Z�b�g
void CFieldManager::Set()
{
	road_.Set();
	wall_.Set();
}


//�X�e�b�v
void CFieldManager::Step()
{
	road_.Step();
	wall_.Step();
}


//�X�V
void CFieldManager::Update()
{
	
	road_.Update();
	wall_.Update();
}


//�`��
void CFieldManager::Draw()
{
	
	road_.Draw();
	wall_.Draw();
}


//�폜
void CFieldManager::Delete()
{
	
	road_.Delete();
	wall_.Delete();
}


//�㏈��
void CFieldManager::Fin()
{
	road_.Fin();
	wall_.Fin();
}

