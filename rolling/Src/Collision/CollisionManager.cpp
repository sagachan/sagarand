
#include "../Player/PlayerManager.h"
#include "CollisionManager.h"
#include "../MyMath/MyMath.h"

//CEnemyManagerの実体宣言、初期化
CCollisionManager* CCollisionManager::instance_ = nullptr;


CCollisionManager::CCollisionManager()
{
	//自動で呼ばれる
	Init();
}

CCollisionManager::~CCollisionManager()
{
	//自動で呼ばれる
	Delete();
}

void CCollisionManager::Init()
{
	
}

void CCollisionManager::Step()
{
	
}

void CCollisionManager::Delete()
{
	Fin();
}

void CCollisionManager::Fin()
{
	
}


