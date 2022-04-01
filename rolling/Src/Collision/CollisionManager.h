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
	CCollisionManager();	//コンストラクタ
	~CCollisionManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//インスタンス取得
	static CCollisionManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	//ステップ
	void Step();
	//削除
	void Delete();
	//後処理
	void Fin();
	
public:
	void BossHit();
	void BossItemHit(VECTOR pos, float rad);

public:
	

	//管理しているクラスのアドレスを格納
	CCollision* GetCollision() { return &collision_; }

private:
	static CCollisionManager*	instance_;					//インスタンス
	CCollision					collision_;
	
	
};