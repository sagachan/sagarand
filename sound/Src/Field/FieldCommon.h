//�t�B�[���h�֌W�ŋ��ʂɎg���\���̂������
#pragma once
#include "Dxlib.h"

//�}�b�v���
struct MapInfo
{
	int handle;						//�摜�n���h��
	int col_handle;					//�����蔻��p���f���n���h��
	int frame_handle;				//�t���[�����f���n���h��
	int frame_clear_handle;			//�N���A�t���[�����f���n���h��
	VECTOR pos;						//���W
};

#define MAP_POS VGet(0.0f, -10.0f, 0.0f)