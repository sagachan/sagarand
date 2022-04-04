#include <DxLib.h>
#include "Collision.h"
#include "../MyMath/MyMath.h"

//�����̂̓����蔻��
// _V1				�c �Ώ�A��X,Y,Z���W�i���f���̒��S���W�j
// _W1, _H1, _D1	�c �Ώ�A��W,H,D�i�����A�����A���s���j
// _V2				�c �Ώ�B��X,Y,Z���W�i���f���̒��S���W�j
// _W2, _H2, _D2	�c �Ώ�B��W,H,D�i�����A�����A���s���j
bool CCollision::IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	if (v1.x + w1 / 2 > v2.x - w2 / 2 &&
		v1.x - w1 / 2 < v2.x + w2 / 2 &&
		v1.y - h1 / 2 < v2.y + h2 / 2 &&
		v1.y + h1 / 2 > v2.y - h2 / 2 &&
		v1.z - d1 / 2 < v2.z + d2 / 2 &&
		v1.z + d1 / 2 > v2.z - d2 / 2)
	{
		return true;
	}

	return false;
}

//���̓����蔻��
bool CCollision::IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2)
{
	if ((r1 + r2) * (r1 + r2) > (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z))
		return true;

	return false;
}

//XY
bool CCollision::IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.z = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.z = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.z = 0.0f;

	//�e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.z = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.z = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.z = 0.0f;


	//�Ή�����x�N�g���ǂ����ŊO�ς��v�Z����
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	//�e�O�ς�Z������0�ȉ��ł���Γ������Ă���
	if (vecABAP.z >= 0 && vecBCBP.z >= 0 && vecCACP.z >= 0)
	{
		return true;
	}

	//���Α����}��
	if (vecABAP.z <= 0 && vecBCBP.z <= 0 && vecCACP.z <= 0)
	{
		return true;
	}

	return false;

}


//XZ
bool CCollision::IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.y = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.y = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.y = 0.0f;

	//�e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.y = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.y = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.y = 0.0f;


	//�Ή�����x�N�g���ǂ����ŊO�ς��v�Z����
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	//�e�O�ς�Z������0�ȉ��ł���Γ������Ă���
	if (vecABAP.y >= 0 && vecBCBP.y >= 0 && vecCACP.y >= 0)
	{
		return true;
	}

	//���Α����}��
	if (vecABAP.y <= 0 && vecBCBP.y <= 0 && vecCACP.y <= 0)
	{
		return true;
	}

	return false;

}

//YZ
bool CCollision::IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.x = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.x = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.x = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.x = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.x = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.x = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	// �e�O�ς�X������0�ȉ��ł���Γ������Ă���
	if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0) {
		return true;
	}
	// �e�O�ς�X������0�ȉ��ł���Γ������Ă���
	if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0) {
		return true;
	}

	return false;
}