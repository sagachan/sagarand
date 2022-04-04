#include "model.h"

// ��`�֘A
static const VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };		// �I�[��0��VECTOR
static const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };	// �ʏ�X�P�[���̓I�[��1�Ȃ̂�


//------------------------------
//		�R���X�g���N�^
//------------------------------
CModel::CModel() : m_pos(VECTOR_ZERO), m_rot(VECTOR_ZERO), m_scale(DEFAULT_SCALE)
, m_hndl(-1)
{
}


//------------------------------
//		�f�X�g���N�^
//------------------------------
CModel::~CModel()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}


//---------------------------------
//		������
//---------------------------------
void	CModel::Init(void)
{
	Fin();
	m_pos = VECTOR_ZERO;
	m_rot = VECTOR_ZERO;
	m_scale = DEFAULT_SCALE;
}


//---------------------------------
//		�I������
//---------------------------------
void	CModel::Fin(void)
{
	DeleteModel();
}


//---------------------------------
//		�X�V����
//---------------------------------
void	CModel::Update(void)
{
	MV1SetPosition(m_hndl, m_pos);
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
}


//------------------------------
//		�f�[�^�ǂݍ���
//------------------------------
bool	CModel::LoadModel(const char* fileName)
{
	if (m_hndl != -1) return false;		// ���f���ǂݍ��ݍς�
	m_hndl = MV1LoadModel(fileName);
	if (m_hndl == -1) return false;		// ���f���̓ǂݍ��ݎ��s
	return true;
}


//------------------------------
//		�R�s�[�f�[�^�ǂݍ���
//------------------------------
bool	CModel::DuplicateModel(int srcHndl)
{
	if (m_hndl != -1) return false;		// ���f���ǂݍ��ݍς�
	m_hndl = MV1DuplicateModel(srcHndl);
	if (m_hndl == -1) return false;		// ���f���̓ǂݍ��ݎ��s
	return true;
}


//---------------------------------
//		���f���f�[�^�폜
//---------------------------------
void	CModel::DeleteModel(void)
{
	if (m_hndl == -1) return;

	MV1DeleteModel(m_hndl);
	m_hndl = -1;
}


//---------------------------------
//		���f���f�[�^�`��
//---------------------------------
void	CModel::Draw(void)
{
	MV1DrawModel(m_hndl);
}
