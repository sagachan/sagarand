//Sky.cpp
//���N���X

#include "Sky.h"


//�R���X�g���N�^
CSky::CSky()
{
	mapInfo_ = { 0 };
}

//�f�X�g���N�^
CSky::~CSky()
{
}

void CSky::Init()
{
	
}


//�ǂݍ���
void CSky::Load()
{
	// ���f���ǂݍ���
	mapInfo_.handle = MV1LoadModel("Data/Map/sky.x");
}



//�Z�b�g
void CSky::Set()
{
	//���f���Z�b�g
	MV1SetPosition(mapInfo_.handle, MAP_POS);
}


//�X�e�b�v
void CSky::Step()
{

}


//�X�V
void CSky::Update()
{

}


//�`��
void CSky::Draw()
{
	MV1DrawModel(mapInfo_.handle);
}


//�폜
void CSky::Delete()
{
}


//�㏈��
void CSky::Fin()
{
	MV1DeleteModel(mapInfo_.handle);
}