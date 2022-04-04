#ifndef __COLLISION_H__
#define __COLLISION_H__

class CCollision {
public:
	//�����̂̓����蔻��
	static bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

	//���̓����蔻��
	static bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

	//�O�p�`�̓����蔻��
	// ����
	// point :�Ώۂ̍��W
	// vertexA :�O�p�`�̒��_A
	// vertexB :�O�p�`�̒��_B
	// vertexC :�O�p�`�̒��_C
	static bool IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	enum DmType
	{
		INIT,
		DM_SMALL,
		DM_MIDDLE,
		DM_BIG
	};
	
};

#endif