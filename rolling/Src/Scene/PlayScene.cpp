//PlayScene.cpp
//プレイシーン

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Field/FieldManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"
#include "../MyMath/MyMath.h"
#include "../Collision/Collision.h"
#include "../Collision/CollisionManager.h"


CPlayScene::CPlayScene()
{
	map_handle = 0;
	map_pos = { 0 };
}

CPlayScene::~CPlayScene()
{
}




//初期化
void CPlayScene::Init()
{
	//プレイヤー管理初期化
	//マネージャーインスタンス生成
	CPlayerManager::CreateInstance();
	//生成したインスタンスを取得
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	//マネージャー初期化
	player_manager->Init();


	
	

	////アニメーション初期化
	//CAnim3D::Init;


	//フィールド管理初期化
	CFieldManager::CreateInstance();
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Init();

	//エネミー管理初期化
	CEnemyManager::CreateInstance();
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	enemy_manager->Init();


	//カメラ管理初期化
	CCameraManager::CreateInstance();
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Init();
	camera_manager->SetNearFar(2.0f, 1500.0f);	//ニアファー設定

	//プレイカメラに変更
	camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	////フェードアウトの開始処理
	//CFade::StartFade(CFade::FADE_OUT, CFade::FADE_COLOR_WHITE);

	//音初期化
	CSound::InitSound();

	//当たり判定モデル読み込み
	map_handle = MV1LoadModel("Data/Model/Field/done/Field.x");

	//当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(map_handle, -1, TRUE);
	map_pos = { 0.0f, -2.0f, 0.0f };

	//マップの回転
	MV1SetPosition(map_handle, map_pos);

	//当たり判定用モデルのポリゴン情報をセットアップ
	MV1RefreshReferenceMesh(map_handle, -1, TRUE);

	//当たり判定管理初期化
	CCollisionManager::CreateInstance();


	////フォグを有効にする
	//SetFogEnable(TRUE);
	//SetFogColor(255, 255, 255);
	//SetFogStartEnd(400.0f, 600.0f);
	
}


//読み込み
void CPlayScene::Load()
{	
	//フィールド管理読み込み
	CFieldManager::GetInstance()->Load();

	//プレイヤー管理読み込み
	CPlayerManager::GetInstance()->Load();

	//エネミー管理読み込み
	CEnemyManager::GetInstance()->Load();


	//音読み込み
	CSound::LoadBGM(CSound::BGM_PLAY);
}


//各変数などの初期値を設定
void CPlayScene::Set()
{	
	//フィールド管理セット
	CFieldManager::GetInstance()->Set();

	//プレイヤー管理セット
	CPlayerManager::GetInstance()->Set();
	
	//エネミー管理セット
	CEnemyManager::GetInstance()->Set();

	//音再生
	CSound::PlayBGM(CSound::BGM_PLAY);
}


//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	CCameraManager* camera_manager = CCameraManager::GetInstance();

	//====================
	//オブジェクト関連
	//====================

	//ステップ
	//プレイカメラ中なら（デバッグカメラ中は、プレイヤーは動かせない）
	if (camera_manager->GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//プレイヤー管理ステップ
		CPlayerManager::GetInstance()->Step();
	}

	
	//フィールド管理ステップ
	CFieldManager::GetInstance()->Step();

	//エネミー管理ステップ
	CEnemyManager::GetInstance()->Step();

	//当たり判定管理ステップ
	CCollisionManager::GetInstance()->Step();

	//フィールド管理の更新
	CFieldManager::GetInstance()->Update();

	//更新
	//プレイヤー管理の更新
	CPlayerManager::GetInstance()->Update();

	


	//当たり判定
	CFieldManager::GetInstance()->GetRoad()->CheckCollision();
	CFieldManager::GetInstance()->GetWall()->CheckCollision();


	//====================
	//カメラ関連
	//====================

	//カメラ視点・注視点の操作
	camera_manager->Step();

	//カメラ視点・注視点の反映
	camera_manager->Update();

	//各カメラの起動処理
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_C))
	{
		//現在のカメラIDによって、処理を振り分ける
		switch (camera_manager->GetCameraID())
		{
		case CCameraManager::CAMERA_ID_PLAY:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
			//デバッグカメラに、プレイカメラの座標を代入
			VECTOR play_camera_pos = camera_manager->GetPlayCamera()->GetPosition();
			VECTOR play_camera_look = camera_manager->GetPlayCamera()->GetLook();
			camera_manager->GetDebugCamera()->Init(play_camera_pos, play_camera_look, VGet(0.0f, 1.0f, 0.0f));
			break;
		case CCameraManager::CAMERA_ID_DEBUG:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
			break;
		}
	}

	
	//-------------------------------
	//		シーン切り替え
	//-------------------------------

	CInput* input = CInput::GetInstance();

	//プレイヤーが死んだらゲームオーバーシーンへ
	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_BACK))
	{
		//ゲームオーバーシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	//プレイヤーの状態を取得
	CPlayer* player_manager = CPlayerManager::GetInstance()->GetPlayer();

	//プレイヤーの生存フラグが折られていたら
	if (player_manager->GetAlive_Flg() == false)
	{
		//ゲームオーバーシーン変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	//クリアフラグが立っていたら
	if (player_manager->GetClearFlag())
	{
		//ゲームクリア変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);

	}
}


//描画
void CPlayScene::Draw()
{
	//フィールド管理描画
	CFieldManager::GetInstance()->Draw();

	

	//プレイヤー管理描画
	CPlayerManager::GetInstance()->Draw();


	//エネミー管理描画
	CEnemyManager::GetInstance()->Draw();


	//カメラ管理描画
	CCameraManager::GetInstance()->Draw();

	
}


//後処理
void CPlayScene::Fin()
{
	//プレイヤー管理の後処理
	//プレイヤー管理取得
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	player_manager->Delete();	//明示的に削除を呼ぶ
	player_manager->Fin();		//後処理
	//マネージャーインスタンス削除
	CPlayerManager::DeleteInstance();

	//フィールド管理の後処理
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Delete();
	field_manager->Fin();
	CFieldManager::DeleteInstance();

	//エネミー管理の後処理
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	enemy_manager->Delete();
	enemy_manager->Fin();
	CEnemyManager::DeleteInstance();


	//カメラの後処理
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Fin();
	//マネージャーインスタンス削除
	CCameraManager::DeleteInstance();

	//音後処理
	CSound::FinSound();
}