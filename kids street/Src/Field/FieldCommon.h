//フィールド関係で共通に使う可能性のあるもの
#pragma once
#include "Dxlib.h"

//マップ情報
struct MapInfo
{
	int handle;						//画像ハンドル
	int col_handle;					//当たり判定用モデルハンドル
	VECTOR pos;						//座標
};