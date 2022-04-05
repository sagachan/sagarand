#pragma once
#include "Score.h"

class CScoreManager
{

public:
	CScoreManager();		//�R���X�g���N�^
	~CScoreManager();		//�f�X�g���N�^

public:
	static void CreateInstance() { if (!instance_)instance_ = new CScoreManager; }
	static CScoreManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:


	//�X�R�A�̏�����
	void Init();

	//�X�R�A�摜�̃��[�h
	void Load();

	//��ʕ\���X�R�A�̍X�V
	void Update();

	//�X�R�A�̕`��
	void Draw();

	//�X�R�A�摜�̔j��
	void Fin();

	//�X�R�A�����Z true��n����AllAdd���Ă�
	void AddScore(int score, bool all_add_flg = false);

	//�X�R�A�������I�ɃZ�b�g����
	void SetScore(int score);

	//�X�R�A���擾
	int GetScore() { return score_.GetScore(); }

	//CScore* GetScore() { return &score_; }

private:
	static CScoreManager* instance_;
	CScore score_;

};