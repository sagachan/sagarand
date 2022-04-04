//Sky.h
//��N���X

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Animation/Model/model.h"

class CSky : public CModel
{
public:

public:
	CSky();
	~CSky();

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
	int		GetFrameHandle() { return mapInfo_.frame_handle; }//�t���[�����f���n���h�����擾
	int		GetFrameClearHandle() { return mapInfo_.frame_clear_handle; }//�N���A�t���[�����f�����擾

private:
	MapInfo					mapInfo_;
	bool					airFlg_;
};