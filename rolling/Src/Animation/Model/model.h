#pragma once
#include <DxLib.h>



//---------------------------------------------
//	3D���f����1�̕\�����邽�߂̃N���X
//---------------------------------------------
class CModel {
protected:
	VECTOR	m_pos_;			// ���W
	VECTOR  m_old_pos_;		// �ړ��O���W
	VECTOR	m_rot_;			// ��]�p�x
	VECTOR	m_scale_;		// �g��k����
	float	m_rad_;			// ���a
	int		m_hndl_;		// ���f���n���h��


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


	//�擾
	//��ɂ��̃��f�����R�s�[���Ďg���������̃N���X��
	//�n�����߂̂��̂ł��B
	inline int		GetHandle(void) { return m_hndl_; }

	//���f���̍��W
	inline VECTOR	GetPosition(void) { return m_pos_; }

	//���f���̃X�P�[��
	inline VECTOR	GetScale(void) { return m_scale_; }

	//���f���̉�]�p�x
	inline VECTOR	GetRot(void) { return m_rot_; }


	//�ݒ�
	//���݂̈ʒu
	inline void	SetPosition(const VECTOR& pos) { m_pos_ = pos; }
	//���݂̃T�C�Y
	inline void	SetScale(const VECTOR& scale) { m_scale_ = scale; }
	inline void	SetScale(float scale) { m_scale_.x = m_scale_.y = m_scale_.z = scale; }
	//���݂̊p�x
	inline void	SetRot(const VECTOR& rot) { m_rot_ = rot; }
};

