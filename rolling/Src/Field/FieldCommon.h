//フィールド関係で共通に使う可能性のあるもの
#pragma once
#include "Dxlib.h"

//マップ情報
struct MapInfo
{
	int handle;						//画像ハンドル
	int col_handle;					//当たり判定用モデルハンドル
	int frame_handle;				//フレームモデルハンドル
	int frame_clear_handle;			//クリアフレームモデルハンドル
	VECTOR pos;						//座標
};

#define MAP_POS VGet(0.0f, -10.0f, 0.0f)