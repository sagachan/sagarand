//GameUIButton.h
//UI�{�^���N���X

#include "GameUI.h"

//UI�{�^���N���X
class CGameUIButton :public CGameUI
{
public:
	CGameUIButton();
	~CGameUIButton();

public:
	void Init(float pos_x, float pos_y) override;	//������
	void Load(const char* file_path) override;		//�ǂݍ���
	void Step() override;							//�X�e�b�v
	void Draw() override;							//�`��
	void Delete() override;							//�폜
	void Fin() override;							//�㏈��

private:
	int handle_;	//�摜�n���h��
};