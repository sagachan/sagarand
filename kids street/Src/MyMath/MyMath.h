#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "DxLib.h"

//�x�N�g���̏������}�N����`
#define ZERO_VECTOR VGet(0.0f, 0.0f, 0.0f)

class CMyMath {
public:
	

	////�x�N�g����s��̌v�Z�������܂Ƃ߂��N���X////

	//�Q�_�Ԃ̋��������߂�i�Q�c�j
	static float GetDistance(float x1, float y1, float x2, float y2);

	//pos1����pos2�܂ł̋������v�Z����
	static float GetDistance(VECTOR pos1, VECTOR pos2);

	//�ψʃx�N�g���̍쐬
	static VECTOR VecCreate(VECTOR start, VECTOR end);

	//pos1����pos2�����̉�]�n��Ԃ�
	static VECTOR GetRot(VECTOR pos1, VECTOR pos2);

	//�x�N�g���̒��������߂�
	static float VecLong(VECTOR vec);

	//�x�N�g���̉��Z
	static VECTOR VecAdd(VECTOR vec1, VECTOR vec2);

	//�x�N�g���̌��Z
	static VECTOR VecSub(VECTOR vec1, VECTOR vec2);

	//�x�N�g���̐��K��
	static VECTOR VecNormalize(VECTOR vec);

	//�x�N�g���̃X�J���[�{
	static VECTOR VecScale(VECTOR vec, float scale);

	//�x�N�g���̓���
	static float VecDot(VECTOR vec1, VECTOR vec2);

	//�x�N�g���̊O�ρi�Q�c�j
	static float VecCross2D(VECTOR vec1, VECTOR vec2);
	//�x�N�g���̊O�ρi�R�c�j
	static VECTOR VecCross(VECTOR vec1, VECTOR vec2);


	//��]�l���O�`�Q�΂̒l�ɂ���
	static float RadianNormalize(float rad);


	//�P�ʍs����擾����
	static MATRIX GetIdentityMatrix();

	//���s�ړ��s����擾����
	static MATRIX GetTranslateMatrix(VECTOR move);

	//�g�k�s����擾����
	static MATRIX GetScaleMatrix(VECTOR scale);

	//�w����]�s����擾����
	static MATRIX GetPitchMatrix(float rad);

	//�x����]�s����擾����
	static MATRIX GetYawMatrix(float rad);

	//�y����]�s����擾����
	static MATRIX GetRollMatrix(float rad);

	//�����œn���ꂽ�Q�̍s��𑫂��Z����
	static MATRIX MatAdd(MATRIX mat1, MATRIX mat2);

	//�����œn���ꂽ�Q�̍s��������Z����
	static MATRIX MatSub(MATRIX mat1, MATRIX mat2);

	//�����œn���ꂽ�s����X�J���[�{����
	static MATRIX MatScale(MATRIX mat, float scale);

	//�����œn���ꂽ�Q�̍s��̊|���Z���s��
	static MATRIX MatMult(MATRIX mat1, MATRIX mat2);

	//�s��~�x�N�g�����s���i�ϊ��v�Z�j
	static VECTOR MatTransform(MATRIX mat, VECTOR vec);

	//�s��]�u���s��
	static MATRIX MatTranspose(MATRIX mat);

	//�|���S���̖@���x�N�g��
	static VECTOR GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	//�ʂ̕��������珰�̍������v�Z
	static float GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	// ���ʏ�̕ǂ̍������v�Z
	static float GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	// ���ʏ�̕ǂ̍������v�Z
	static float GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);


	static float Abs(float val);

	//origin��+-rad���͈͓̔���target������Ȃ�true��Ԃ��v�Z(VECTOR)
	static bool RadiusCheck(VECTOR origin, float rad, VECTOR target);

	//origin��+-rad���͈͓̔���target������Ȃ�true��Ԃ��v�Z(float)
	static bool RadiusCheck(float origin, float rad, float target);

};

#endif
