#pragma once
#include "Dxlib.h"

//敵情報
struct EnemyInfo
{
	int handle;						//画像ハンドル
	int col_handle;					//当たり判定用モデルハンドル
	int frame_handle;				//フレームモデルハンドル
	VECTOR pos;						//座標
};

#define FALL_ENEMY_NUM (4)

//奇数が上、偶数が下
