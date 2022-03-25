//GameUI.h
//UI�̃x�[�X�ƂȂ�N���X

#pragma once

//UI�̃x�[�X�ƂȂ�N���X
class CGameUI
{
public:
	CGameUI();
	virtual ~CGameUI();

public:
	virtual void Init(float pos_x, float pos_y) = 0;	//������
	virtual void Load(const char* file_path) = 0;		//�ǂݍ���
	virtual void Step() = 0;							//�X�e�b�v
	virtual void Draw() = 0;							//�`��
	virtual void Delete() = 0;							//�폜
	virtual void Fin() = 0;								//�㏈��

	void SetPosX(float pos_x) { pos_x_ = pos_x; }	//�w���W�ݒ�
	void SetPosY(float pos_y) { pos_y_ = pos_y; }	//�x���W�ݒ�

	float GetPosX()const { return pos_x_; }	//�w���W�擾
	float GetPosY()const { return pos_y_; }	//�x���W�擾

protected:
	float pos_x_;	//�w���W
	float pos_y_;	//�x���W
};