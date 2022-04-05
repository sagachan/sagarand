#include "ScoreManager.h"

CScoreManager* CScoreManager::instance_ = nullptr;


CScoreManager::CScoreManager()
{

}

CScoreManager::~CScoreManager()
{

}

void CScoreManager::Init()
{
	score_.InitScore();
}

void CScoreManager::Load()
{
	score_.LoadScore();
}

void CScoreManager::Update()
{
	score_.UpdateScore();
}

void CScoreManager::Draw()
{
	score_.DrawScore();
}

void CScoreManager::Fin()
{
	score_.FinScore();
}

void CScoreManager::AddScore(int score, bool all_add_flg)
{
	if (all_add_flg == true)
		score_.AddAllScore(score);
	else
		score_.AddScore(score);
}

void CScoreManager::SetScore(int set_score)
{
	score_.SetScore(set_score);
}