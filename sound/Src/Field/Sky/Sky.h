//Sky.h
//空クラス

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
	void	CheckCollision();							//当たり判定計算
	bool	Is_in_Air() { return airFlg_; }			//今現在空中にいるかどうか、当たっていないかどうかを返す
	int		GetFrameHandle() { return mapInfo_.frame_handle; }//フレームモデルハンドルを取得
	int		GetFrameClearHandle() { return mapInfo_.frame_clear_handle; }//クリアフレームモデルを取得

private:
	MapInfo					mapInfo_;
	bool					airFlg_;
};