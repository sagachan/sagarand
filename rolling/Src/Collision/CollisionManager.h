#pragma once

#include "Collision.h"
#include "DxLib.h"


class CCollisionManager
{
public:
	struct CollisionData
	{
		VECTOR pos_;
		float rad_;
	};

	struct ITEM_DATA
	{
		VECTOR pos_;
		float rad_;
		bool useflg_;
	};

	enum COLLISION_TYPE
	{
		INIT,
		ALLHIT,
		THROUGH,
		PAWN,
		STATIC,
		DYNAMIC
	};

	enum COLLISION_KIND
	{
		PLAYER,
		ITEM,
		ENEMY,
		BOSS
	};

public:
	CCollisionManager();	//�R���X�g���N�^
	~CCollisionManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//�C���X�^���X�擾
	static CCollisionManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	//�X�e�b�v
	void Step();
	//�폜
	void Delete();
	//�㏈��
	void Fin();
	
public:
	void BossHit();
	void BossItemHit(VECTOR pos, float rad);

public:
	

	//�Ǘ����Ă���N���X�̃A�h���X���i�[
	CCollision* GetCollision() { return &collision_; }

private:
	static CCollisionManager*	instance_;					//�C���X�^���X
	CCollision					collision_;
	
	
};