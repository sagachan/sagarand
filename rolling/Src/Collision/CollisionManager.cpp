
#include "../Player/PlayerManager.h"
#include "CollisionManager.h"
#include "../MyMath/MyMath.h"

//CEnemyManager�̎��̐錾�A������
CCollisionManager* CCollisionManager::instance_ = nullptr;


CCollisionManager::CCollisionManager()
{
	//�����ŌĂ΂��
	Init();
}

CCollisionManager::~CCollisionManager()
{
	//�����ŌĂ΂��
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


