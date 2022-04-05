#include "DxLib.h"
#include "Score.h"

namespace
{
	// �����摜�̃t�@�C���p�X
	const char* SCORE_PATH = "Data/score/number16x32_01.png";

}

CScore::CScore()
	:digit_num_()
	,disp_score_()
	,handle_()
	,score_()
{
}

CScore::~CScore()
{

}


//������
void CScore::InitScore()
{
	for (int score_index = 0; score_index < NUMBER; score_index++)
	{
		handle_[score_index] = -1;
	}
	score_ = 0;
	disp_score_ = 0;
}



//�ǂݍ���
void CScore::LoadScore()
{

	LoadDivGraph(SCORE_PATH, 10, 10, 1, NUMBER_SIZE_X, NUMBER_SIZE_Y, handle_);

}


//�f�[�^�j��
void CScore::FinScore()
{
	for (int score_index = 0; score_index < NUMBER; score_index++)
	{
		if (handle_[score_index] != -1)
		{
			DeleteGraph(handle_[score_index]);
			handle_[score_index] = -1;
		}
	}
}

//�X�R�A�̕`��
void CScore::DrawScore()
{
	CalcDigitNum(disp_score_);
	int TempScore = disp_score_;
	for (int score_index = 0; score_index < digit_num_; score_index++)
	{
		//���܂���o��
		int Num = TempScore % 10;
		//�Ή����鐔�����摜�T�C�Y�ʂ�ɕ`��@
		DrawRotaGraph(30 - score_index *NUMBER_SIZE_X, NUMBER_SIZE_Y, 1.0, 0.0, handle_[Num], true);

		//�������炷
		TempScore /= 10;
	}
}

//�X�R�A���Z����
void CScore::AddScore(int score)
{
	score_ += score;
}

void CScore::AddAllScore(int score)
{
	score_ += score;
	disp_score_ += score;
}


//�X�R�A���Z�b�g
void CScore::SetScore(int score)
{
	disp_score_ = score;
	score_ = score;
}


void CScore::UpdateScore()
{
	//�\���X�R�A�Ɛ������X�R�A�ɍ�������Ȃ�
	if (score_ != disp_score_)
	{
		//�\���X�R�A�����Z
		disp_score_ += ADD_SCORE_SPD;

		//�����s���߂����Ȃ琳�����X�R�A�ɖ߂�
		if (disp_score_ > score_)
		{
			disp_score_ = score_;
		}
	}
}

void CScore::CalcDigitNum(int score)
{

	int ans;
	// score��0�̎��͉��̃��[�v��ʂ炸�ɕ\�������P�ɂ��ďI���
	if (score == 0)
	{
		digit_num_ = 1;
		return;
	}
	for (ans = 1, digit_num_ = 1; ans <= score; digit_num_++)
	{
		ans *= 10;
	}
	digit_num_ -= 1;


}