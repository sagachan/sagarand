//PlayCamera.cpp
//プレイシーンでのカメラ

#include "PlayCamera.h"
#include <math.h>
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Input/Pad/Pad.h"

//カメラ関連
#define CAMERA_OFFSET_Z			(-12.0f)		//カメラの注視点からの手前オフセット値
#define CAMERA_LOOK_OFFSET_Y	(4.0f)		//カメラの注視点の高さオフセット
#define CAMERA_ROT_SPEED		(0.052f)	//カメラの回転速度

namespace
{
	//カメラの回転スピード
	const float PLAY_CAMERA_ROTATION = (2.0f * DX_PI_F / 180.0f);
	//カメラの回転値最大
	const float PLAY_CAMERA_ROTATION_MAX = (2.0f * DX_PI_F);
	//カメラのX回転値最大
	const float PLAY_CAMERA_ROTATION_MAX_X = (20.0f * 2.0f * DX_PI_F / 180.0f);
	//カメラのX回転値最小
	const float PLAY_CAMERA_ROTATION_MIN_X = (-10.0f * 2.0f * DX_PI_F / 180.0f);

	//カメラのサイズ
	const float PLAY_CAMERA_SIZE_H = 1.0f;
	const float PLAY_CAMERA_SIZE_W = 1.0f;
	const float PLAY_CAMERA_SIZE_D = 1.0f;
	const float PLAY_CAMERA_SIZE_R = 1.0f;
}

//コンストラクタ
CPlayCamera::CPlayCamera()
{
	cameraInfo = { 0 };
}

//デストラクタ
CPlayCamera::~CPlayCamera()
{
}


//初期化（引数なし）
void CPlayCamera::Init()
{
	cameraInfo = { 0 };
}


//初期化（引数あり）
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	cameraInfo.pos = pos;
	cameraInfo.look = look;
	cameraInfo.up = up;
}


//毎フレーム呼ぶ処理（操作）
void CPlayCamera::Step()
{
	//プレイヤーの情報を取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//入力操作クラス取得
	CInput* input = CInput::GetInstance();

	VECTOR player_rot = player->GetRot();	//回転値を取得
	VECTOR player_pos = player->GetPos();	//座標を取得

	//----------------------------
	// カメラの注視点
	//----------------------------
	cameraInfo.look = player->GetPos();
	cameraInfo.look.y = player->GetPos().y + CAMERA_LOOK_OFFSET_Y;	//プレイヤーの少し上を見る

	//
	//カメラの回転
	//

	//スティックの値を取得
	float stick_x = CInput::GetInstance()->GetStickValue(RIGHT_STICK_X);
	float stick_y = CInput::GetInstance()->GetStickValue(RIGHT_STICK_Y);


	// 注視点を原点に平行移動する行列を作成
	MATRIX origin_look_mat =
		CMyMath::GetTranslateMatrix(VGet(-cameraInfo.look.x, -cameraInfo.look.y, -cameraInfo.look.z));

	//カメラを注視点より手前に移動させる平行移動行列を作成
	MATRIX fore_look_mat =
		CMyMath::GetTranslateMatrix(VGet(0.0f, 0.0f, CAMERA_OFFSET_Z));

	//カメラのX軸回転行列を作成
	MATRIX pitch_mat = CMyMath::GetPitchMatrix(cameraInfo.fRotX);

	//カメラのY軸回転行列を作成
	MATRIX yaw_mat = CMyMath::GetYawMatrix(cameraInfo.fRotY);

	// 注視点を元の位置に平行移動する行列を作成
	MATRIX default_look_mat = CMyMath::GetTranslateMatrix(cameraInfo.look);

	//各行列を合成（掛け算の順番に注意！！）
	MATRIX mult_mat = CMyMath::MatMult(default_look_mat, yaw_mat);
	mult_mat = CMyMath::MatMult(mult_mat, pitch_mat);
	mult_mat = CMyMath::MatMult(mult_mat, fore_look_mat);
	mult_mat = CMyMath::MatMult(mult_mat, origin_look_mat);

	//注視点に行列を掛けてカメラの座標を算出
	cameraInfo.pos = CMyMath::MatTransform(mult_mat, cameraInfo.look);
}


//カメラ情報の更新処理
void CPlayCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(cameraInfo.pos, cameraInfo.look, cameraInfo.up);
}


//後処理
void CPlayCamera::Fin()
{
}