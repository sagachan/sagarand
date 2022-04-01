#include "Player.h"
#include "../Common.h"
#include <math.h>
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Animation/Animation.h"
#include "../Field/FieldManager.h"


namespace
{
	//プレイヤー関連
	const VECTOR PLAYER_START_POS = VGet(0.0f, 1.0f, 0.0f);	//プレイヤーの座標
	const float PLAYER_SPD = 1.0f;			//プレイヤーの移動速度
	const float PLAYER_ADDSPD = 10.6f;		//白線上プレイヤー速度
	const float PLAYER_m_rot_SPD = 0.01f;		//プレイヤーの回転速度
	const float PLAYER_m_rot_RETURN_SPEED = 1.5f; //プレイヤーの回転の戻るスピード
	const float PLAYER_MAX_ROT = 30.0f;		//プレイヤーの最大回転角度（３０度まで）
	const float PLAYER_MIN_ROT = -30.0f;	//プレイヤーの最小回転角度（－３０度まで）
	const float PLAYER_JUMP_POWER = 0.5f;	//プレイヤーのジャンプ力
	const float PLAYER_G_POWER = 0.5;		//プレイヤーにかかる重力の強さ設定（中の数値は仮）
	const bool  HIT_INIT_FLG = false;		//プレイヤーに外部から変更可能な当たり判定フラグの初期値

	const int	PLAYER_BULLET_INTERVAL = 10;//プレイヤーの通常弾発射時間
	const float PLAYER_W = 4.0f;			//プレイヤーの横幅
	const float PLAYER_H = 4.0f;			//プレイヤーの高さ
	const float PLAYER_D = 4.0f;			//プレイヤーの奥行き
	const float PLAYER_R = 4.5f;			//プレイヤーの半径

	const float	 PLAYER_DEAD_MIN_POS_Y = -30.0f;//プレイヤーが死亡する最小Y座標

	//画面範囲関連
	const float RANGE_MAX_WIDTH = 14.0f;	//横幅の最大範囲
	const float RANGE_MIN_WIDTH = -14.0f;	//横幅の最小範囲
	const float RANGE_MAX_HEIGHT = 12.0f;	//縦幅の最大範囲
	const float RANGE_MIN_HEIGHT = -12.0f;	//縦幅の最大範囲

	//ジャンプ関連
	const float ORIGIN_POS = 0.0f;			//原点座標
	const float JUMP_TOP = 25.0f;			//ジャンプの最高地点
	const float PLAYER_JUMP_TIME = 0.35f;	//プレイヤーの飛ぶ時間
	const float PLAYER_JUMP_VAL = 0.0f;		//ジャンプ量
	const float GRAVITY = 1.0f;				//重力
	const float JUMP_CHARGE = 10.0f;		//ジャンプ時の溜め硬直時間
	const float JUMP_LANDING = 40.0f;		//ジャンプ後の着地硬直時間

	const float FRAME_DIS = 10.0f;
}




//コンストラクタ
CPlayer::CPlayer()
{
	Init();
}

//デストラクタ
CPlayer::~CPlayer()
{
	Fin();
}



//初期化
void CPlayer::Init()
{
	m_hndl_ = 0;					//モデルハンドル
	m_pos_ = { 0.0f };				//座標
	m_old_pos_ = { 0.0f };			//移動前の座標
	move_ = { 0.0f };				//移動量
	m_rot_ = { 0.0f };				//回転値
	clear_flag_ = false;
}



//読み込み（ロード）
void CPlayer::Load()
{
	//モデル読み込み
	m_hndl_ = MV1LoadModel("Data/Player/playerBall.x");
}



//各変数などに初期値を設定（セット）
void CPlayer::Set()
{
	m_pos_ = PLAYER_START_POS;
	state_ = PLAYER_STAND;			//ステータス
	is_alive_ = true;				//生存フラグ
	size_ = VGet(PLAYER_W, PLAYER_H, PLAYER_D);
	m_rad_ = PLAYER_R;
	m_rot_ = { 0.0f, 0.2f, 0.0f };
}


//引数をプレイヤー位置座標へ
void CPlayer::Set(VECTOR pos)
{
	m_pos_ = pos;
}


//プレイヤーが当たり判定の影響を受ける処理
void CPlayer::HitSet()
{
	m_pos_.x = m_old_pos_.x;
	m_pos_.z = m_old_pos_.z;
}





//毎フレーム呼ぶ処理（操作）
void CPlayer::Step()
{
	StepClearCheck();

	//プレイヤーに常に重力をかける
	m_pos_.y -= GRAVITY;
	//m_pos_.y

	//プレイヤーの移動前の座標を記録
	m_old_pos_ = m_pos_;
	move_.x = 0.0f;
	move_.z = 0.0f;
	m_rot_.x += 0.3f;
	
	StepInput();

	if(jumpFlg_ == false)
		StepJump();
	else
	{
		move_.y *= 0.9f;
	}


	if (m_pos_.y > JUMP_TOP)
	{
		move_.y = 0.0f;
	}


	//前に自動的に進む
	move_.z += PLAYER_SPD;


	//プレイヤーの座標ベクトルを、行列から取得
	m_pos_ = CMyMath::VecAdd(m_pos_, move_);
	StepDead();//死亡処理
}


//更新
void CPlayer::Update()
{
	//アニメーション更新
	CAnim3D::UpdateAnim();

	//プレイヤーの回転
	MV1SetRotationXYZ(m_hndl_, m_rot_);

	//プレイヤーの座標
	MV1SetPosition(m_hndl_, m_pos_);
}


//描画
void CPlayer::Draw()
{
	//プレイヤーの描画
	MV1DrawModel(m_hndl_);
	
}


//削除
void CPlayer::Delete()
{
	//プレイヤーモデル削除
	MV1DeleteModel(m_hndl_);

	//削除したら0を代入しておく
	m_hndl_ = 0;
}


//後処理
void CPlayer::Fin()
{
	//Deleteが呼ばれていないなら
	if (m_hndl_ != 0)
	{
		//削除を呼んでおく
		Delete();
	}
}


//入力ステップ
void CPlayer::StepInput()
{
	CInput* input = CInput::GetInstance();
	CRoad* field = CFieldManager::GetInstance()->GetRoad();
	
	m_old_pos_ = m_pos_;//処理前座標を保持

	//左移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A))
	{
		move_.x -= PLAYER_SPD;
	}
	//右移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D))
	{
		move_.x += PLAYER_SPD;

	}
}

//死亡処理
void CPlayer::StepDead()
{
	//一定距離落下したら
	if (m_pos_.y < PLAYER_DEAD_MIN_POS_Y)
	{
		is_alive_ = false;//フラグを折る
	}
}

void CPlayer::StepJump()
{
	CRoad* field = CFieldManager::GetInstance()->GetRoad();

	//フレームハンドルを取得
	int frame_handle = field->GetFrameHandle();

	//フレームの数を取得
	int frame_max = MV1GetFrameNum(frame_handle);

	for(int index = 0; index < frame_max; index++)
	{
		VECTOR targetPos = MV1GetFramePosition(frame_handle, index);

		//対象フレームまでの座標を作成
		float dis = CMyMath::GetDistance(targetPos, m_pos_);

		if (dis < FRAME_DIS)
		{
			move_.y = 5.0f;
			jumpFlg_ = true;

		}

	}

}

void CPlayer::StepClearCheck()
{
	CRoad* field = CFieldManager::GetInstance()->GetRoad();

	//フレームハンドルを取得
	int frame_clear_handle = field->GetFrameClearHandle();

	//フレームの数を取得
	int frame_max = MV1GetFrameNum(frame_clear_handle);

	for (int index = 0; index < frame_max; index++)
	{
		VECTOR targetPos = MV1GetFramePosition(frame_clear_handle, index);

		//対象フレームまでの座標を作成
		float dis = CMyMath::GetDistance(targetPos, m_pos_);

		if (dis < FRAME_DIS)
		{
			clear_flag_ = true;
		}

	}

}