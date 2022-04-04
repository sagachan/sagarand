//TitleScene.cpp
//�^�C�g���V�[��

#include "TitleScene.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "../Input/Input.h"
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

CTitleScene::CTitleScene()
{
	Init();
}

CTitleScene::~CTitleScene()
{
}

//������
void CTitleScene::Init()
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
	bg->Load("Data/Title/opening.jpg");

	//��������
	CSound::InitSound();
}


//�ǂݍ���
void CTitleScene::Load()
{
	//�e�L�X�g�摜�ǂݍ���
	text_info_.handle = LoadGraph("Data/Graph/Title_Logo.png");

	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_TITLE);

}


//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CTitleScene::Set()
{
	text_info_.pos_x = WINDOW_W / 3 * 2;
	text_info_.pos_y = WINDOW_H / 5 * 4;
	text_info_.base_pos_y = WINDOW_H / 5 * 4;

	//���Đ�
	CSound::PlayBGM(CSound::BGM_TITLE);
}


//���t���[���Ăԏ���
void CTitleScene::Step()
{
	CInput* input = CInput::GetInstance();
	////Enter�L�[�������ꂽ ���� �t�F�[�h�C�����J�n����ĂȂ��Ȃ�
	//if (CInput::IsKeyPush(KEY_INPUT_RETURN) && CFade::IsFadeStart() == false)
	//{
	//	//�t�F�[�h�C���̊J�n����
	//	CFade::StartFade(CFade::FADE_IN, CFade::FADE_COLOR_WHITE);
	//}

	////�t�F�[�h�C�����I�������A�v���C�V�[����
	//if (CFade::IsFadeEnd() == true)
	//{
	//	//�v���C�V�[���֕ύX
	//	CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_PLAY);
	//}

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�v���C�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_PLAY);
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
void CTitleScene::Draw()
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
void CTitleScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	DeleteGraph(text_info_.handle);
	text_info_.handle = 0;

	//���㏈��
	CSound::FinSound();
}