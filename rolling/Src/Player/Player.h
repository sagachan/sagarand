//Player.h
//プレイヤークラス

#pragma once

#include "DxLib.h"
#include "../Animation/Animation.h"


class CPlayer : public CAnim3D
{
public:

	enum PLAYER_ANIM_STATE
	{
		PLAYER_INIT,
		PLAYER_STAND,
		PLAYER_WALK,
		PLAYER_RUN,
		PLAYER_JUMP,
		PLAYER_THROW,
		PLAYER_RELOAD
	};

	enum PLAYER_ANIM_NO
	{
		INIT,
		THROW,
		ARMATURE,
		JUMP,
		STAND,
		WALK,
		RELOAD,
		ANIM_MAX_NUM
	};

public:
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

public:
	void Init();			//初期化
	void Load();			//読み込み（ロード）
	void Set();				//各変数などに初期値を設定（セット）
	void Set(VECTOR pos);
	void HitSet();			//当たり判定用関数、oldposに戻す
	void Step();			//毎フレーム呼ぶ処理（操作）
	void Update();			//更新
	void Draw();			//描画
	void Delete();			//削除
	void Fin();				//後処理

	void StepInput();		//入力ステップ
	void StepDead();		//死亡処理
	void StepJump();		//ジャンプ処理
	void StepClearCheck();	//クリアのチェック処理

public:
	VECTOR GetSize() { return size_; }
	VECTOR GetForward() { return move_; }										//プレイヤーの加算ベクトルを取得
	VECTOR GetForwardVec() { return forward_; }
	float GetRad() { return m_rad_; }											//プレイヤーの半径を取得
	bool GetAlive_Flg() { return is_alive_; }									//プレイヤーの生存フラグをを取得
	bool GetClearFlag() { return clear_flag_; }									//クリアフラグを取得する
	bool SetJumpFlag(bool flg) { return jumpFlg_ = flg; }
	void SetAlive_Flg(bool flg) { is_alive_ = flg; }
	
private:
	VECTOR			move_;				//移動量
	VECTOR			forward_;			//プレイヤーの向きベクトル格納
	VECTOR			posSave;			//移動前の地点のセーブ
	VECTOR			size_;				//大きさ
	bool			moveFlg_;			//現在移動可能かどうか
	bool			is_alive_;			//生存フラグ
	bool			hitFlg_;			//別クラス当たり判定フラグ
	bool			jumpFlg_;
	float			jumpTime_;			//ジャンプの時間
	bool			clear_flag_;		//クリアフラグ

	PLAYER_ANIM_STATE	state_;			//状態（ステータス）
	PLAYER_ANIM_STATE	old_state_;		//前ループ状態（ステータス）
	
};