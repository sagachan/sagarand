//GameOverScene.cpp
//�Q�[���I�[�o�[�V�[��

#include "GameOverScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "DxLib.h"
#include <math.h>
#include "../Common.h"
#include "../MyMath/MyMath.h"
#include "../UI/GameUIManager.h"
#include "../Sound/Sound.h"

namespace
{
	const float TEXT_MAX_SIZE = 1.0f;	//�����̍ő�T�C�Y
	const float TEXT_ADD_SIZE = 0.01f;	//�����̉��Z�����T�C�Y��
	const float TEXT_MOVE_Y = 30.0f;	//������Y���W�ړ���

	//�g�`�̊p�x�̕ς��̑����i�T�b�ň���j
	const float WAVE_ANGLE_SPD = (DX_TWO_PI_F / FRAME_RATE) / 5.0f;
}


CGameOverScene::CGameOverScene()
{
	Init();
}

CGameOverScene::~CGameOverScene()
{
}

//������
void CGameOverScene::Init()
{
	//�e�L�X�g�摜�֘A������
	text_info_.handle = 0;
	text_info_.pos_x = 0.0f;
	text_info_.pos_y = 0.0f;
	text_info_.base_pos_y = 0.0f;
	text_info_.size = 0.0f;
	text_info_.wave_angle = 0.0f;


	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/gameover.png");

	//��������
	CSound::InitSound();
}

//�ǂݍ���
void CGameOverScene::Load()
{
	//�Q�[���I�[�o�[�V�[���̉摜�ǂݍ���
	text_info_.handle = LoadGraph("Data/Graph/GameOver_Logo.png");

	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_GAMEOVER);
}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CGameOverScene::Set()
{
	text_info_.pos_x = WINDOW_W / 3 * 2;
	text_info_.pos_y = WINDOW_H / 2;
	text_info_.base_pos_y = WINDOW_H / 2;

	//���Đ�
	CSound::PlayBGM(CSound::BGM_GAMEOVER);
}

//���t���[���Ăԏ���
void CGameOverScene::Step()
{
	//Enter�L�[�������ꂽ��^�C�g���V�[����
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�^�C�g���V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TITLE);
	}


	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();


	//�����̃T�C�Y���K��l�܂Ŋg��
	if (text_info_.size < TEXT_MAX_SIZE)
	{
		text_info_.size += TEXT_ADD_SIZE;
	}

	//�����̃T�C�Y���K��l�ɒB������
	//sin�J�[�u�𗘗p���āA�������㉺�ɓ�����
	if (text_info_.size >= TEXT_MAX_SIZE)
	{
		//�K�؂Ȉړ��ʂɂ��āA���W�ɑ��
		text_info_.pos_y = text_info_.base_pos_y + sinf(text_info_.wave_angle) * TEXT_MOVE_Y;

		//�p�x�����Z�i5�b���ƂɊ�_�ɖ߂�j
		text_info_.wave_angle += WAVE_ANGLE_SPD;

		//�p�x���O�`�Q�΂̒l�͈̔͊O�ɂȂ����ꍇ�A
		//�O�`�Q�΂͈̔͂ɖ߂�
		if (text_info_.wave_angle < 0.0f)
			text_info_.wave_angle = CMyMath::RadianNormalize(text_info_.wave_angle);
		else if (text_info_.wave_angle > DX_TWO_PI_F)
			text_info_.wave_angle = CMyMath::RadianNormalize(text_info_.wave_angle);
	}
}


//�`��
void CGameOverScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();

	//�����摜
	DrawRotaGraph((int)text_info_.pos_x, (int)text_info_.pos_y,
		text_info_.size, 0.0f, text_info_.handle, true);

	//������`��
	DrawString(10, 10, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(10, 30, "Enter��������Play��", GetColor(255, 255, 0));
}


//�㏈��
void CGameOverScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	DeleteGraph(text_info_.handle);
	text_info_.handle = 0;

	//���㏈��
	CSound::FinSound();
}