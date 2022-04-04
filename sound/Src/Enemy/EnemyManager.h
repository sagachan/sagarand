#pragma once

#include "FallEnemy/FallEnemy.h"
#include "EnemyCommon.h"

class CEnemyManager
{
public:

	CEnemyManager();	//�R���X�g���N�^
	~CEnemyManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CEnemyManager; }
	//�C���X�^���X�擾
	static CEnemyManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	//������
	void Init();

	//�ǂݍ���
	void Load();

	//�Z�b�g
	void Set();

	//�X�e�b�v
	void Step();

	//���f
	void Update();

	//�`��
	void Draw();

	//�폜
	void Delete();

	//�㏈��
	void Fin();

	//�h�b�X���N���X���擾
	CFallEnemy* GetFallEnemy() { return fallEnemy_; }

private:
	static CEnemyManager* instance_;	//�C���X�^���X

	CFallEnemy fallEnemy_[FALL_ENEMY_NUM];	//�h�b�X���N���X

};