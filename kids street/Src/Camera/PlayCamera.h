//PlayCamera.h
//プレイシーンでのカメラ

#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

class CPlayCamera
{
	
public:
	CPlayCamera();	//コンストラクタ
	~CPlayCamera();	//デストラクタ

public:
	//初期化
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//毎フレーム呼ぶ処理（操作）
	void Step();

	//カメラ情報の更新処理
	void Update();

	//後処理
	void Fin();

	//座標取得
	VECTOR GetPos() { return cameraInfo.pos; }

	//注視点取得
	VECTOR GetLook() { return cameraInfo.look; }

private:

	//カメラ情報
	struct CameraInfo
	{
		VECTOR	pos;		//視点
		VECTOR	look;		//注視点
		VECTOR	up;			//アップベクトル
		float fRotX;		//水平角度(X軸角度)
		float fRotY;		//垂直角度(Y軸角度)
	};

	CameraInfo cameraInfo;
};