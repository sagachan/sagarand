#pragma once


namespace {
	const int NUMBER = 10;
	const int NUMBER_SIZE_X = 16;
	const int NUMBER_SIZE_Y = 32;
	const int ADD_SCORE_SPD = 1;
}

class CScore
{
public:
	CScore();
	~CScore();

	//�X�R�A�̏�����
	void InitScore();

	//�X�R�A�摜�̃��[�h
	void LoadScore();

	//��ʕ\���X�R�A�̍X�V
	void UpdateScore();

	//�X�R�A�̕`��
	void DrawScore();

	//�X�R�A�摜�̔j��
	void FinScore();

	//�X�R�A�����Z�@��ʕ\���p�X�R�A�ɂ͉��Z���Ȃ�
	void AddScore(int score);
	//��ʕ\���p�X�R�A���܂߂ĉ��Z
	void AddAllScore(int score);

	//�X�R�A���Z�b�g����
	void SetScore(int score);

	//�X�R�A���擾
	int GetScore() { return score_; };

	void CalcDigitNum(int score);

private:
	int handle_[10];
	int score_;
	//��ʕ\���X�R�A
	int disp_score_;
	int digit_num_;
};

