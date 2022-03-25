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
	const VECTOR PLAYER_START_POS = VGet(5.0f, 1.0f, 250.0f);	//プレイヤーの座標
	const float PLAYER_SPD = 0.2f;			//プレイヤーの移動速度
	const float PLAYER_ADDSPD = 10.6f;		//白線上プレイヤー速度
	const float PLAYER_m_rot_SPD = 0.01f;		//プレイヤーの回転速度
	const float PLAYER_m_rot_RETURN_SPEED = 1.5f; //プレイヤーの回転の戻るスピード
	const float PLAYER_MAX_ROT = 30.0f;		//プレイヤーの最大回転角度（３０度まで）
	const float PLAYER_MIN_ROT = -30.0f;	//プレイヤーの最小回転角度（−３０度まで）
	const float PLAYER_JUMP_POWER = 0.5f;	//プレイヤーのジャンプ力
	const float PLAYER_G_POWER = 0.5;		//プレイヤーにかかる重力の強さ設定（中の数値は仮）
	const bool  HIT_INIT_FLG = false;		//プレイヤーに外部から変更可能な当たり判定フラグの初期値

	const int	PLAYER_BULLET_INTERVAL = 10;//プレイヤーの通常弾発射時間
	const float PLAYER_W = 4.0f;			//プレイヤーの横幅
	const float PLAYER_H = 4.0f;			//プレイヤーの高さ
	const float PLAYER_D = 4.0f;			//プレイヤーの奥行き
	const float PLAYER_R = 2.0f;			//プレイヤーの半径

	//画面範囲関連
	const float RANGE_MAX_WIDTH = 14.0f;	//横幅の最大範囲
	const float RANGE_MIN_WIDTH = -14.0f;	//横幅の最小範囲
	const float RANGE_MAX_HEIGHT = 12.0f;	//縦幅の最大範囲
	const float RANGE_MIN_HEIGHT = -12.0f;	//縦幅の最大範囲

	//ジャンプ関連
	const float ORIGIN_POS = 0.0f;			//原点座標
	const float PLAYER_JUMP_TIME = 0.35f;	//プレイヤーの飛ぶ時間
	const float PLAYER_JUMP_VAL = 0.0f;		//ジャンプ量
	const float GRAVITY = 0.3f;				//重力
	const float JUMP_CHARGE = 10.0f;		//ジャンプ時の溜め硬直時間
	const float JUMP_LANDING = 40.0f;		//ジャンプ後の着地硬直時間
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
	jump_time_ = 0.0f;				//ジャンプの時間
	hit_flg_ = HIT_INIT_FLG;		//当たり判定フラグ初期化
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
	m_radius = PLAYER_R;			//半径
	state_ = PLAYER_STAND;			//ステータス
	move_flg_ = true;
	is_alive_ = true;				//生存フラグ
	size_ = VGet(PLAYER_W, PLAYER_H, PLAYER_D);
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
	//プレイヤーに常に重力をかける
	m_pos_.y -= GRAVITY;
	
	//プレイヤーの移動前の座標を記録
	m_old_pos_ = m_pos_;
	move_ = { 0 };

	if(move_flg_ == true)
	StepInput();

	//プレイヤーの座標ベクトルを、行列から取得
	m_pos_ = CMyMath::VecAdd(m_pos_, move_);
	
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
	
	//--------------------------------
	//    プレイヤーの移動処理
	//--------------------------------
	float add = PLAYER_SPD;	//プレイヤーの移動速度設定

	m_old_pos_ = m_pos_;//処理前座標を保持

	//向きベクトルを求める
	forward_.x = sinf(m_rot_.y);
	forward_.z = cosf(m_rot_.y);

	
	//向いている方向へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_W))
	{
		

		//向きベクトルを適切な大きさに変更して座標に加算
		m_pos_.x += forward_.x * add;
		m_pos_.z += forward_.z * add;
	}
	
	//左回転
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A))
	{
		m_rot_.y -= 0.1f;
	}
	//右回転
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D))
	{
		m_rot_.y += 0.1f;
	}
	//向いている方向とは逆へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_S))
	{
		//向きベクトルを適切な大きさ・向きに変更して座標に加算
		m_pos_.x -= forward_.x * add;
		m_pos_.z -= forward_.z * add;
	}

	
}