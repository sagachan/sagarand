#pragma once

#include "DxLib.h"
#include "../../Animation/Model/model.h"
#include "../EnemyCommon.h"

class CFallEnemy : public CModel
{
public:

public:
	CFallEnemy();
	~CFallEnemy();

public:
	void Init();
	void Load();
	void Set(VECTOR pos);
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

public:
	void	CheckCollision();							//�����蔻��v�Z
	int		GetFrameHandle() { return enemyInfo_.frame_handle; }//�t���[�����f���n���h�����擾
	void	SetStartEndPos(VECTOR start, VECTOR end) { startPos_ = start; endPos_ = end; }
	void	FallEnemy();
	

private:
	EnemyInfo	enemyInfo_;
	VECTOR		startPos_;
	VECTOR		endPos_;
	bool		fallFlg_;
};