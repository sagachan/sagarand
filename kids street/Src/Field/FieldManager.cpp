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
}


//�ǂݍ���
void CFieldManager::Load()
{
	road_.Load();
}



//�Z�b�g
void CFieldManager::Set()
{
	road_.Set();
}


//�X�e�b�v
void CFieldManager::Step()
{
	road_.Step();
}


//�X�V
void CFieldManager::Update()
{
	
	road_.Update();
	
}


//�`��
void CFieldManager::Draw()
{
	
	road_.Draw();
	
}


//�폜
void CFieldManager::Delete()
{
	
	road_.Delete();
}


//�㏈��
void CFieldManager::Fin()
{
	road_.Fin();
}

