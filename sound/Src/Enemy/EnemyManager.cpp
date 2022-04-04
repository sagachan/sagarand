#include "EnemyManager.h"

//CEnemyManager�̎��̐錾�A������
CEnemyManager* CEnemyManager::instance_ = nullptr;



//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	//CEnemy�̃R���X�g���N�^�͎����ŌĂ΂�܂�
}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	//CEnemy�̃f�X�g���N�^�͎����ŌĂ΂�܂�
}


//������
void CEnemyManager::Init()
{
	//�h�b�X���̏��������Ă�
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Init();
	}

}


//�ǂݍ���
void CEnemyManager::Load()
{
	//�h�b�X���̓ǂݍ���
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Load();
	}
	
}


//�Z�b�g
void CEnemyManager::Set()
{
	//�h�b�X���̃Z�b�g
	fallEnemy_->GetFrameHandle();

	//�t���[���n���h�����擾
	int frame_handle = fallEnemy_->GetFrameHandle();

	//�t���[���̐����擾
	int frame_max = MV1GetFrameNum(frame_handle);

	int arrayNum = 0;

	for (int index = 0; index < frame_max; index++)
	{
		//��ԍ��̃{�[���̂ݒʂ�
		if (index % 2 != 0)
		{
			//�G�l�~�[�̍ŏ��̈ʒu���擾
			VECTOR enemyPos = MV1GetFramePosition(frame_handle, index);

			//�����ԍ��̃{�[���ԍ�
			index++;

			//�G�l�~�[�̍Ō�̈ʒu���擾
			VECTOR endPos = MV1GetFramePosition(frame_handle, index);

			//�G�l�~�[�̍ŏ��̈ʒu�ƍŌ�̈ʒu���Z�b�g
			fallEnemy_[arrayNum].SetStartEndPos(enemyPos, endPos);

			//�G�l�~�[�̃Z�b�g
			fallEnemy_[arrayNum].Set(enemyPos);

			//�z��ԍ�
			arrayNum++;
		}
	}
	
}


//�X�e�b�v
void CEnemyManager::Step()
{
	//�h�b�X���̃X�e�b�v
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Step();
	}
	
}


//���f
void CEnemyManager::Update()
{
	//�h�b�X���̔��f
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Update();
	}
	
}


//�`��
void CEnemyManager::Draw()
{
	//�h�b�X���̕`��
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Draw();
	}
	
}


//�폜
void CEnemyManager::Delete()
{
	//�h�b�X���폜
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Delete();
	}
}


//�㏈��
void CEnemyManager::Fin()
{
	//�h�b�X���̌㏈�����Ă�
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Fin();
	}
}