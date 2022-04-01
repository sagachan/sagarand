//Road.h
//���N���X

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Animation/Model/model.h"

class CRoad : public CModel
{
public:
	
public:
	CRoad();
	~CRoad();

public:
	void Init();
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

public:
	void	CheckCollision();							//�����蔻��v�Z
	bool	Is_in_Air() { return airFlg_; }			//�����݋󒆂ɂ��邩�ǂ����A�������Ă��Ȃ����ǂ�����Ԃ�
	int		GetFrameHandle() { return mapInfo_.frame_hamdle; }//�t���[�����f���n���h�����擾

private:
	MapInfo					mapInfo_;
	bool					airFlg_;
};