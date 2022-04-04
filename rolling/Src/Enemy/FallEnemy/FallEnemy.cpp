#include "FallEnemy.h"
#include "../../MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/Collision.h"

namespace
{
	//�}�b�v�֘A
	const float MAP_FLOOR_NORM_Y(0.1f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_CEIL_NORM_Y(-0.9f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_WALL_NORM_Z(0.5f);	//�@����Z���������̒l�ȏ�ł���Ε�
	const float	ENEMY_FALL_SPD = 2.0f;	//�G�l�~�[�̗����鑬�x
	const float ENEMY_UP_SPD = 0.1f;	//�G�l�~�[�̏オ�鑬�x
}

//�R���X�g���N�^
CFallEnemy::CFallEnemy()
{

}

//�f�X�g���N�^
CFallEnemy::~CFallEnemy()
{
}

void CFallEnemy::Init()
{
	// ���f���ǂݍ���
	enemyInfo_.handle = MV1LoadModel("Data/Enemy/Enemy.x");

	// �����蔻�胂�f���ǂݍ���
	enemyInfo_.col_handle = MV1LoadModel("Data/Enemy/Enemy.x");

	//�t���[�����f���n���h��
	enemyInfo_.frame_handle = MV1LoadModel("Data/Map/enemyBorn.x");



	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(enemyInfo_.col_handle, -1, TRUE);


}


//�ǂݍ���
void CFallEnemy::Load()
{

}



//�Z�b�g
void CFallEnemy::Set(VECTOR pos)
{
	MV1SetPosition(enemyInfo_.handle, pos);
	enemyInfo_.pos = pos;
	fallFlg_ = true;
}


//�X�e�b�v
void CFallEnemy::Step()
{
	Fall();
	CheckCollision();
}


//�X�V
void CFallEnemy::Update()
{
	MV1SetPosition(enemyInfo_.handle, enemyInfo_.pos);
	MV1SetPosition(enemyInfo_.col_handle, enemyInfo_.pos);
	// �|���S�������X�V����
	MV1RefreshReferenceMesh(enemyInfo_.col_handle, -1, TRUE);
}


//�`��
void CFallEnemy::Draw()
{
	MV1DrawModel(enemyInfo_.handle);
}


//�폜
void CFallEnemy::Delete()
{
}


//�㏈��
void CFallEnemy::Fin()
{
	MV1DeleteModel(enemyInfo_.handle);
	MV1DeleteModel(enemyInfo_.col_handle);
}

void CFallEnemy::Fall() 
{
	//�G�l�~�[�𗎂Ƃ�����

	//�����鋗��
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

	// �}�b�v�Ƃ̓����蔻��/////////////////////////////////////////


	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(enemyInfo_.col_handle, -1, TRUE);

	//�v���C���[�����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�v���C���[�̑O�����x�N�g���擾
	VECTOR player_forward = CPlayerManager::GetInstance()->GetPlayer()->GetForward();


	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// �|���S�������擾����
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// �|���S�����`������O�p�`��3���_���擾����
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;


		// �|���S���@�����Z�o����
		VECTOR norm = CMyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// �@����Y������MAP_FLOOR_NORM_Y_MIN�ȏ�ł���Ώ�
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]))
			{


				// �ʂ̕��������珰�̍������v�Z
				float floor_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = player->GetPosition().y - player->GetRad();
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ ���� �����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���
				if (dist < 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					//�ǂɓ�����ƃQ�[���I�[�o�[
					CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);

				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y) {
			// �V��̏ꍇ
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕���������V��̍������v�Z
				float ceil_height = CMyMath::GetTriangleHeightXZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̔]�V�̍��W���v�Z
				float player_top = player->GetPosition().y + player->GetRad();
				// �V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				// �]�V�̕������� ���� �]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���
				if (dist > 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					//�ǂɓ�����ƃQ�[���I�[�o�[
					CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
				}
			}
		}
		else {
			// �����łȂ���Ε�
			// �@���ƃv���C���[�̈ړ��x�N�g���������������Ă���ꍇ�̂ݔ�������
			/*if (CMyMath::VecDot(player_forward, norm) < 0.0f) {*/
			if (CMyMath::Abs(norm.z) >= MAP_WALL_NORM_Z) {
				// XY���ʂ̕�
				if (CCollision::IsHitTriangleXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = CMyMath::GetTriangleHeightXY(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm.z < 0.0f ? player->GetPosition().z + player->GetRad() : player->GetPosition().z - player->GetRad();
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f)) {
							//�ǂɓ�����ƃQ�[���I�[�o�[
							CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
						}
					}
				}
			}
			else {
				// YZ���ʂ̕�
				if (CCollision::IsHitTriangleYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = CMyMath::GetTriangleHeightYZ(player->GetPosition(), vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm.x < 0.0f ? player->GetPosition().x + player->GetRad() : player->GetPosition().x - player->GetRad();
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (CMyMath::Abs(dist) <= player->GetRad()) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f)) {
							//�ǂɓ�����ƃQ�[���I�[�o�[
							CPlayerManager::GetInstance()->GetPlayer()->SetAlive_Flg(false);
						}
					}// if (MyMath::Abs(dist) <= PLAYER_RAD)
				}// if (CCollision::IsHitTriangleYZ(player_info_.pos, vertexs[0], vertexs[1], vertexs[2]))
			}// if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z_MIN) else
		//}// if (MyMath::VecDot(player_info_.forward, norm) < 0.0f)
		}// if (norm.y >= MAP_FLOOR_NORM_Y_MIN) else
	}// for (int i = 0; i < polygons.PolygonNum; i++)

}