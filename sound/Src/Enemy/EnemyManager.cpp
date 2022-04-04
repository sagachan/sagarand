#include "EnemyManager.h"

//CEnemyManagerの実体宣言、初期化
CEnemyManager* CEnemyManager::instance_ = nullptr;



//コンストラクタ
CEnemyManager::CEnemyManager()
{
	//CEnemyのコンストラクタは自動で呼ばれます
}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
	//CEnemyのデストラクタは自動で呼ばれます
}


//初期化
void CEnemyManager::Init()
{
	//ドッスンの初期化を呼ぶ
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Init();
	}

}


//読み込み
void CEnemyManager::Load()
{
	//ドッスンの読み込み
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Load();
	}
	
}


//セット
void CEnemyManager::Set()
{
	//ドッスンのセット
	fallEnemy_->GetFrameHandle();

	//フレームハンドルを取得
	int frame_handle = fallEnemy_->GetFrameHandle();

	//フレームの数を取得
	int frame_max = MV1GetFrameNum(frame_handle);

	int arrayNum = 0;

	for (int index = 0; index < frame_max; index++)
	{
		//奇数番号のボーンのみ通る
		if (index % 2 != 0)
		{
			//エネミーの最初の位置を取得
			VECTOR enemyPos = MV1GetFramePosition(frame_handle, index);

			//偶数番号のボーン番号
			index++;

			//エネミーの最後の位置を取得
			VECTOR endPos = MV1GetFramePosition(frame_handle, index);

			//エネミーの最初の位置と最後の位置をセット
			fallEnemy_[arrayNum].SetStartEndPos(enemyPos, endPos);

			//エネミーのセット
			fallEnemy_[arrayNum].Set(enemyPos);

			//配列番号
			arrayNum++;
		}
	}
	
}


//ステップ
void CEnemyManager::Step()
{
	//ドッスンのステップ
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Step();
	}
	
}


//反映
void CEnemyManager::Update()
{
	//ドッスンの反映
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Update();
	}
	
}


//描画
void CEnemyManager::Draw()
{
	//ドッスンの描画
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Draw();
	}
	
}


//削除
void CEnemyManager::Delete()
{
	//ドッスン削除
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Delete();
	}
}


//後処理
void CEnemyManager::Fin()
{
	//ドッスンの後処理を呼ぶ
	for (int num = 0; num < FALL_ENEMY_NUM; num++)
	{
		fallEnemy_[num].Fin();
	}
}