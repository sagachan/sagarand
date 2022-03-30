//Road.cpp
//���N���X

#include "Road.h"
#include "../../MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/Collision.h"

namespace
{
	//�}�b�v�֘A
	const float MAP_FLOOR_NORM_Y(0.1f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_CEIL_NORM_Y(-0.9f);	//�@����Y���������̒l�ȏ�ł���Ώ�
	const float MAP_WALL_NORM_Z(0.5f);	//�@����Z���������̒l�ȏ�ł���Ε�
}

//�R���X�g���N�^
CRoad::CRoad()
{
	airFlg_ = false;
	mapInfo_ = { 0 };
}

//�f�X�g���N�^
CRoad::~CRoad()
{
}

void CRoad::Init()
{
	// ���f���ǂݍ���
	mapInfo_.handle = MV1LoadModel("Data/Map/ground.x");

	// �����蔻�胂�f���ǂݍ���
	mapInfo_.col_handle = MV1LoadModel("Data/Map/ground.x");

	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(mapInfo_.col_handle, -1, TRUE);


}


//�ǂݍ���
void CRoad::Load()
{

}



//�Z�b�g
void CRoad::Set()
{
}


//�X�e�b�v
void CRoad::Step()
{
	
}


//�X�V
void CRoad::Update()
{
	//�}�b�v�̍��W
	MV1SetPosition(mapInfo_.handle, VGet(0.0f, -10.0f, 0.0f));
	MV1SetPosition(mapInfo_.col_handle, VGet(0.0f, -11.5f, 0.0f));
	// �|���S�������X�V����
	MV1RefreshReferenceMesh(mapInfo_.col_handle, -1, TRUE);
}


//�`��
void CRoad::Draw()
{
	MV1DrawModel(mapInfo_.handle);
}


//�폜
void CRoad::Delete()
{
}


//�㏈��
void CRoad::Fin()
{
	MV1DeleteModel(mapInfo_.handle);
	MV1DeleteModel(mapInfo_.col_handle);
}

void CRoad::CheckCollision()
{

	// �}�b�v�Ƃ̓����蔻��/////////////////////////////////////////

	//���̓����蔻�肪���݋@�\���Ă��邩���m�F����ϐ�������
	airFlg_ = true;

	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(mapInfo_.col_handle, -1, TRUE);

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
				// �����̕����Ⴂ ���� �����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = floor_height + player->GetRad();
					player->Set(pos);

					//���ɂ������Ă��邩��󒆂ɂ͂��Ȃ�
					airFlg_ = false;
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
				// �]�V�̕������� ���� �]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && CMyMath::Abs(dist) <= player->GetRad()) {
					VECTOR pos = player->GetPosition();
					pos.y = ceil_height - player->GetRad();
					player->Set(pos);
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
							// �@���̕����ɂ߂荞��ł��镪���������o��
							VECTOR push = CMyMath::VecScale(norm, CMyMath::Abs(dist));
							VECTOR pos = player->GetPosition();
							pos = CMyMath::VecAdd(player->GetPosition(), push);
							player->Set(pos);
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
							// �@���̕����ɂ߂荞��ł��镪���������o��
							VECTOR push = CMyMath::VecScale(norm, CMyMath::Abs(dist));
							VECTOR pos = player->GetPosition();
							pos = CMyMath::VecAdd(player->GetPosition(), push);
							player->Set(pos);
						}
					}// if (MyMath::Abs(dist) <= PLAYER_RAD)
				}// if (CCollision::IsHitTriangleYZ(player_info_.pos, vertexs[0], vertexs[1], vertexs[2]))
			}// if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z_MIN) else
		//}// if (MyMath::VecDot(player_info_.forward, norm) < 0.0f)
		}// if (norm.y >= MAP_FLOOR_NORM_Y_MIN) else
	}// for (int i = 0; i < polygons.PolygonNum; i++)

}