
#include "../Player/PlayerManager.h"
#include "CollisionManager.h"
#include "../MyMath/MyMath.h"

//CEnemyManager‚ÌÀ‘ÌéŒ¾A‰Šú‰»
CCollisionManager* CCollisionManager::instance_ = nullptr;


CCollisionManager::CCollisionManager()
{
	//©“®‚ÅŒÄ‚Î‚ê‚é
	Init();
}

CCollisionManager::~CCollisionManager()
{
	//©“®‚ÅŒÄ‚Î‚ê‚é
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


