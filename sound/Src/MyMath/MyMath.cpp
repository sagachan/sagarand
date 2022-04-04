#include "MyMath.h"
#include <math.h>
#include "../Collision/Collision.h"


// �_P(x1, y1)����_Q(x2, y2)�܂ł̋�����Ԃ�
float CMyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// �_P����_Q�܂ł̒������ΕӂƂ��钼�p�O�p�`�����A
	// �s�^�S���X�̒藝����Εӂ̒������v�Z����B
	// �@�܂��͒�ӂ̒������v�Z����
	float a = x2 - x1;

	// �A�������v�Z����
	float b = y2 - y1;

	// �B�Εӂ�2��̒l���v�Z����
	float double_c = a * a + b * b;

	// �C2��̒l�Ȃ̂ŕ��������v�Z���Ē����Ƃ���
	// �@��������<math.h>��sqrtf�֐��Ŏ擾�ł���
	return sqrtf(double_c);
}


//pos1����pos2�܂ł̋������v�Z����
float CMyMath::GetDistance(VECTOR pos1, VECTOR pos2)
{
	return VecLong(VecCreate(pos1, pos2));
}


//�ψʃx�N�g���̍쐬
VECTOR CMyMath::VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	//�e�����Łu�i�I�_�j�[�i�n�_�j�v������
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

//pos1����pos2�܂ł̌�����Ԃ�
VECTOR CMyMath::GetRot(VECTOR pos1, VECTOR pos2)
{
	VECTOR result;

	result = VecCreate(pos1, pos2);
	result = VecNormalize(result);

	return result;

}


//�x�N�g���̒��������߂�
float CMyMath::VecLong(VECTOR vec)
{
	float vec_long = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	return vec_long;
}


// �x�N�g���̑����Z
VECTOR CMyMath::VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// �@�e�����𑫂��Z����
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}


//�x�N�g���̌��Z�ivec1����vec2������)
VECTOR CMyMath::VecSub(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	//�e�����������Z����
	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;

	return result;
}


//�x�N�g���̐��K��
VECTOR CMyMath::VecNormalize(VECTOR vec)
{
	VECTOR result;
	float vec_long = VecLong(vec);	//�x�N�g���̒���

	//�e�����̒����Ŋ��萳�K������
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}


//�x�N�g���̃X�J���[�{
VECTOR CMyMath::VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	//�e�������X�J���[�{����
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}


//�x�N�g���̓���
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

//�x�N�g���̊O�ρi�Q�c�j
float CMyMath::VecCross2D(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

//�x�N�g���̊O�ρi�R�c�j
VECTOR CMyMath::VecCross(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return result;
}


//��]�l���O�`�Q�΂̒l�ɂ���
float CMyMath::RadianNormalize(float rad)
{
	float result = rad;
	if (result < 0.0f)
	{
		while (result < 0.0f)
		{
			result += DX_TWO_PI_F;
		}
	}
	else if (result >= DX_TWO_PI_F)
	{
		while (result > DX_TWO_PI_F)
		{
			result -= DX_TWO_PI_F;
		}
	}

	return result;
}


//�P�ʍs����擾����
MATRIX CMyMath::GetIdentityMatrix()
{
	MATRIX result = { 0 };

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}


//���s�ړ��s����擾����
MATRIX CMyMath::GetTranslateMatrix(VECTOR move)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][3] = move.x;
	result.m[1][3] = move.y;
	result.m[2][3] = move.z;

	return result;
}


//�g�k�s����擾����
MATRIX CMyMath::GetScaleMatrix(VECTOR scale)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}


//�w����]�s����擾����
MATRIX CMyMath::GetPitchMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[1][1] = cosf(rad);
	result.m[1][2] = -sinf(rad);
	result.m[2][1] = sinf(rad);
	result.m[2][2] = cosf(rad);

	return result;
}


//�x����]�s����擾����
MATRIX CMyMath::GetYawMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = cosf(rad);
	result.m[0][2] = sinf(rad);
	result.m[2][0] = -sinf(rad);
	result.m[2][2] = cosf(rad);

	return result;
}


//�y����]�s����擾����
MATRIX CMyMath::GetRollMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = cosf(rad);
	result.m[0][1] = -sinf(rad);
	result.m[1][0] = sinf(rad);
	result.m[1][1] = cosf(rad);

	return result;
}


//�����œn���ꂽ�Q�̍s��𑫂��Z����
MATRIX CMyMath::MatAdd(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	//�Ή�����v�f���m�ő����Z
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat1.m[i][j] + mat2.m[i][j];
		}
	}

	return result;
}

//�����œn���ꂽ�Q�̍s��������Z����
MATRIX CMyMath::MatSub(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	//�Ή�����v�f���m�ň����Z
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat1.m[i][j] - mat2.m[i][j];
		}
	}

	return result;
}


//�����œn���ꂽ�s����X�J���[�{����
MATRIX CMyMath::MatScale(MATRIX mat, float scale)
{
	MATRIX result = { 0 };

	//�e�v�f���A�X�J���[�l�Ŋ|���Z
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat.m[i][j] * scale;
		}
	}

	return result;
}


//�����œn���ꂽ�Q�̍s��̊|���Z���s��
MATRIX CMyMath::MatMult(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += (mat1.m[i][k] * mat2.m[k][j]);
			}
		}
	}

	return result;
}


//�s��~�x�N�g�����s���i�ϊ��v�Z�j
VECTOR CMyMath::MatTransform(MATRIX mat, VECTOR vec)
{
	float work[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec;
	work[0] = vec.x;
	work[1] = vec.y;
	work[2] = vec.z;
	work[3] = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			result_buf[i] += (mat.m[i][k] * work[k]);
		}
	}

	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}


//�s��]�u���s��
MATRIX CMyMath::MatTranspose(MATRIX mat)
{
	MATRIX result = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[j][i] = mat.m[i][j];
		}
	}

	return result;
}

//�|���S���̖@���x�N�g��
VECTOR CMyMath::GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	VECTOR vecABAC = VecCross(vecAB, vecAC);
	return VecNormalize(vecABAC);
}

float CMyMath::GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	//�ӂɉ������x�N�g��AB��AC���v�Z
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);

	//�ʖ@�����v�Z
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);

	//���ʂ̕��������獂���iY���W���v�Z�j
	float y = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.z * (point.z - vertexA.z) + vecNorm.y * vertexA.y) / vecNorm.y;



	//VECTOR vecNorm = GetPolygonNormalVec(vertexA, vertexB, vertexC);

	//float y = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.z * (point.z - vertexA.z) + vecNorm.y * vertexA.y) / vecNorm.y;

	return y;
}

// ���ʏ�̕ǂ̍������Z�o
float CMyMath::GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	//�ӂɉ������x�N�g��AB��AC���v�Z
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);

	//�ʖ@�����v�Z
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);

	//���ʂ̕��������獂���iZ���W���v�Z�j
	float z = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.y * (point.y - vertexA.y) + vecNorm.z * vertexA.z) / vecNorm.z;

	return z;
}

// ���ʏ�̕ǂ̍������v�Z
float CMyMath::GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �ӂɉ������x�N�g��AB��AC���v�Z
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	// �ʖ@�����v�Z
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);
	// ���ʂ̕��������獂���iY���W���v�Z�j
	float x = (-vecNorm.y * (point.y - vertexA.y) - vecNorm.z * (point.z - vertexA.z) + vecNorm.x * vertexA.x) / vecNorm.x;

	return x;
}


float CMyMath::Abs(float val)
{
	if (val < 0.0f)
	{
		return -val;
	}

	return val;
}

bool CMyMath::RadiusCheck(VECTOR origin, float rad, VECTOR target)
{
	if (RadiusCheck(origin.x, rad, target.x)&&
		RadiusCheck(origin.y, rad, target.y)&&
		RadiusCheck(origin.z, rad, target.z))
	{
		return true;
	}

	return false;
}

bool CMyMath::RadiusCheck(float origin, float rad, float target)
{
	if (origin + rad > target &&
		origin - rad < target)
	{
		return true;
	}

	return false;
}