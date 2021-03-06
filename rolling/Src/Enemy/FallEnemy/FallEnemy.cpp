#include "FallEnemy.h"
#include "../../MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/Collision.h"

namespace
{
	//マップ関連
	const float MAP_FLOOR_NORM_Y(0.1f);	//法線のY成分がこの値以上であれば床
	const float MAP_CEIL_NORM_Y(-0.9f);	//法線のY成分がこの値以上であれば床
	const float MAP_WALL_NORM_Z(0.5f);	//法線のZ成分がこの値以上であれば壁
	const float	ENEMY_FALL_SPD = 2.0f;	//エネミーの落ちる速度
	const float ENEMY_UP_SPD = 0.1f;	//エネミーの上がる速度
}

//コンストラクタ
CFallEnemy::CFallEnemy()
{

}

//デストラクタ
CFallEnemy::~CFallEnemy()
{
}

void CFallEnemy::Init()
{
	// モデル読み込み
	enemyInfo_.handle = MV1LoadModel("Data/Enemy/Enemy.x");

	// 当たり判定モデル読み込み
	enemyInfo_.col_handle = MV1LoadModel("Data/Enemy/Enemy.x");

	//フレームモデルハンドル
	enemyInfo_.frame_handle = MV1LoadModel("Data/Map/enemyBorn.x");



	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(enemyInfo_.col_handle, -1, TRUE);


}


//読み込み
void CFallEnemy::Load()
{

}



//セット
void CFallEnemy::Set(VECTOR pos)
{
	MV1SetPosition(enemyInfo_.handle, pos);
	enemyInfo_.pos = pos;
	fallFlg_ = true;
}


//ステップ
void CFallEnemy::Step()
{
	Fall();
	CheckCollision();
}


//更新
void CFallEnemy::Update()
{
	MV1SetPosition(enemyInfo_.handle, enemyInfo_.pos);
	MV1SetPosition(enemyInfo_.col_handle, enemyInfo_.pos);
	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(enemyInfo_.col_handle, -1, TRUE);
}


//描画
void CFallEnemy::Draw()
{
	MV1DrawModel(enemyInfo_.handle);
}


//削除
void CFallEnemy::Delete()
{
}


//後処理
void CFallEnemy::Fin()
{
	MV1DeleteModel(enemyInfo_.handle);
	MV1DeleteModel(enemyInfo_.col_handle);
}

void CFallEnemy::Fall() 
{
	//エネミーを落とす処理

	//落ちる距離
	float fallDis = startPos_.y - endPos_.y;

	if (fallFlg_)
	{
		enemyInfo_.pos.y -= ENEMY_FALL_SPD;
		if (enemyInfo_.pos.y < endPos_.y)
		{
			fallFlg_ = false;
		}
	}
	else if (!fallFlg_)
	{
		enemyInfo_.pos.y += ENEMY_UP_SPD;
		if (enemyInfo_.pos.y > startPos_.y)
		{
			fallFlg_ = true;
		}
	}
}

void CFallEnemy::CheckCollision()
{

	// マップとの当たり判定/////////////////////////////////////////


	// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(enemyInfo_.col_handle, -1, TRUE);

	//プレイヤー情報を取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//プレイヤーの前向きベクトル取得
	VECTOR player_forward = CPlayerManager::GetInstance()->GetPlayer()->GetForward();


	// ポリゴンの数だけ繰り返す
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// ポリゴン情報を取得する
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// ポリゴンを形成する三角形の3頂点を取得する
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;


		// ポリゴン法線を算出する
		VECTOR norm = CMyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// 法線のY成分がMAP_FLOOR_NORM_Y_MIN以上であれば床
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]))
			{


				// 面の方程式から床の高さを計算
				float floor_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = player->GetPosition().y - player->GetRad();
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い かつ 足元と床との距離が離れすぎていないか
				if (dist < 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					//壁に当たるとゲームオーバー
					CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);

				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y) {
			// 天井の場合
			// 三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から天井の高さを計算
				float ceil_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの脳天の座標を計算
				float player_top = player->GetPosition().y + player->GetRad();
				// 天井から脳天までの距離を計算
				float dist = player_top - ceil_height;
				// 脳天の方が高い かつ 脳天と天井との距離が離れすぎていないか
				if (dist > 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					//壁に当たるとゲームオーバー
					CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
				}
			}
		}
		else {
			// そうでなければ壁
			// 法線とプレイヤーの移動ベクトルが向かい合っている場合のみ判定を取る
			/*if (CMyMath::VecDot(player_forward, norm) < 0.0f) {*/
			if (CMyMath::Abs(norm.z) >= MAP_WALL_NORM_Z) {
				// XY平面の壁
				if (CCollision::IsHitTriangleXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = CMyMath::GetTriangleHeightXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm.z < 0.0f ? player->GetPosition().z + player->GetRad() : player->GetPosition().z - player->GetRad();
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f)) {
							//壁に当たるとゲームオーバー
							CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
						}
					}
				}
			}
			else {
				// YZ平面の壁
				if (CCollision::IsHitTriangleYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// 平面上の壁の高さを算出
					float wall_height = CMyMath::GetTriangleHeightYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// 衝突点までの距離を算出
					float player_front = norm.x < 0.0f ? player->GetPosition().x + player->GetRad() : player->GetPosition().x - player->GetRad();
					float dist = player_front - wall_height;
					// 壁から離れすぎていないかチェック
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// 法線の向きに気を付けてめり込んでいるかチェックする
						if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f)) {
							//壁に当たるとゲームオーバー
							CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
						}
					}// if (MyMath::Abs(dist) <= PLAYER_RAD)
				}// if (CCollision::IsHitTriangleYZ(player_info_.pos, vertexs[0], vertexs[1], vertexs[2]))
			}// if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z_MIN) else
		//}// if (MyMath::VecDot(player_info_.forward, norm) < 0.0f)
		}// if (norm.y >= MAP_FLOOR_NORM_Y_MIN) else
	}// for (int i = 0; i < polygons.PolygonNum; i++)

}