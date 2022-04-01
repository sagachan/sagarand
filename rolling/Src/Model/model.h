#pragma once
#include <DxLib.h>



//---------------------------------------------
//	3D���f����1�̕\�����邽�߂̃N���X
//---------------------------------------------
class CModel{
protected:
	VECTOR	m_pos;			// ���W
	VECTOR	m_rot;			// ��]�p�x
	VECTOR	m_scale;		// �g��k����
	int		m_hndl;			// ���f���n���h��


public:
	CModel();
	virtual ~CModel();

	//		������
	virtual void	Init(void);
	//		�I������
	virtual void	Fin(void);
	//		���l�̍X�V����
	virtual void	Update(void);
	//		���f���`��
	virtual void	Draw(void);

	//***************************************
	//		�摜�ǂݍ��݊֘A
	//***************************************
	//		���f���ʏ탍�[�h
	//	fileName	:	�ǂݍ��݂������f���f�[�^��
	bool	LoadModel(const char* fileName);
	//		���f���R�s�[���[�h
	//	@memo		:	���łɓǂݍ���ł��郂�f���𕡐��\���������ꍇ�Ɏg�p���܂��B
	//	srcHndl	:	�ǂݍ��݂������f���̃n���h��
	bool	DuplicateModel(int srcHndl);
	//		���f���f�[�^�폜
	void	DeleteModel(void);


	//***************************************
	//		�擾�֐�
	//***************************************
	//		���f���n���h���擾
	//	@memo	:	��ɂ��̃��f�����R�s�[���Ďg���������̃N���X��
	//			:	�n�����߂̂��̂ł��B
	inline int		GetHandle(void){ return	m_hndl; }
	//		�ʒu�擾
	//	@return	:	���f���̍��W
	inline VECTOR	GetPosition(void){ return m_pos; }
	//		�X�P�[���擾
	//	@return	:	���f���̃X�P�[��
	inline VECTOR	GetScale(void){ return m_scale; }
	//		��]�p�x�擾
	//	@return	:	���f���̉�]�p�x
	inline VECTOR	GetRot(void){ return m_rot; }

	//***************************************
	//		�ݒ�֐�
	//***************************************
	//		�ʒu�ݒ�
	//	pos		:	���݂̈ʒu
	inline void	SetPosition(const VECTOR& pos){ m_pos = pos; }
	//		�X�P�[���ݒ�
	//	scale	:	���݂̃T�C�Y
	inline void	SetScale(const VECTOR& scale){ m_scale = scale; }
	inline void	SetScale(float scale){ m_scale.x = m_scale.y = m_scale.z = scale; }
	//		��]�p�x�ݒ�
	//	rot		:	���݂̊p�x
	inline void	SetRot(const VECTOR& rot){ m_rot = rot; }
};

