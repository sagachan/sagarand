#include <DxLib.h>
#include <math.h>
#include "Scene/SceneManager.h"
#include "Field/FieldManager.h"
#include "Input/Input.h"
#include "Common.h"


//-------------------------------------
// �O���[�o���ϐ�
//-------------------------------------

//�t���[�����[�g�֘A
int g_nCurrentTime = 0;				//���݂̎���
int g_nLastFrameTime = 0;			//�O��̃t���[�����s���̎���
int g_nFrameCnt = 0;				//�t���[���J�E���g�p
int g_nUpdateFrameRateTime = 0;		//�t���[�����[�g���X�V��������
float g_fFrameRate = 0.f;			//�t���[�����[�g�i�\���p�j

//-------------------------------------
// �O���[�o���֐�
//-------------------------------------

//�t���[�����[�g�v�Z
void CalcFrameRate();

//�t���[�����[�g�\���i�f�o�b�O�p�j
void DrawFrameRate();


//�v���O������ WinMain ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(true);	//�E�B���h�E�̏�Ԃ�ݒ肷��

	//--------------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�E�B���h�E�T�C�Y��ύX
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//���ߐF��ݒ�
	SetTransColor(0, 127, 127);



	//====================
	// �V�[���̏���
	//====================

	//�V�[���Ǘ�������
	CSceneManager::CreateInstance();
	CSceneManager* scene_manager = CSceneManager::GetInstance();

	//�ŏ��̓v���C�V�[����
	scene_manager->StartFirstScene(CSceneManager::SCENE_ID_TITLE);


	//--------------------------------------------
	//�L�[�{�[�h���͏�����
	CInput::GetInstance()->Init();

	//=============================================================================
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//�V�X�e���ɏ�����Ԃ�

		//���݂̎��Ԃ��擾
		g_nCurrentTime = GetNowCount();


		//���݂̎��Ԃ��A�O��̃t���[�������
		// 1000/60�~���b�i1/60�b)�ȏ�o�߂��Ă����珈�������s����
		if (g_nCurrentTime - g_nLastFrameTime >= 1000 / FRAME_RATE)
		{
			//�t���[�����s���̎��Ԃ��X�V
			g_nLastFrameTime = g_nCurrentTime;

			//�t���[�������J�E���g
			g_nFrameCnt++;


			if (CInput::GetInstance()->IsPush(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			//�L�[�{�[�h���͒ʏ폈��
			CInput::GetInstance()->Step();

			////�t�F�[�h�̃X�e�b�v
			//CFade::StepFade();


			//====================
			// �V�[���̏���
			//====================

			//�V�[���Ǘ��̃��[�v
			scene_manager->Loop();


			////�t�F�[�h�̕`��
			//CFade::DrawFade();


			//�t���[�����[�g�v�Z
			CalcFrameRate();

			//�t���[�����[�g�\���i�f�o�b�O�p�j
			DrawFrameRate();

			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}//�t���[�����[�g��if���I���
	}//���C�����[�v�̏I���

	//--------------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���

	//�V�[���Ǘ��̌㏈��
	scene_manager->Fin();
	CSceneManager::DeleteInstance();


	//�g�p�������ׂẲ摜��j��
	InitGraph();

	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}//WinMain�֐��̏I���


//�t���[�����[�g�v�Z
void CalcFrameRate()
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;

	//�O��̃t���[�����[�g�X�V����
	//�P�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if (nDifTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float fFrameCnt = (float)(g_nFrameCnt * 1000);

		//�t���[�����[�g�����߂�
		//���z�ʂ�Ȃ� 60000 / 1000 �� 60 �ƂȂ�
		g_fFrameRate = fFrameCnt / nDifTime;

		//�t���[���J�E���g���N���A
		g_nFrameCnt = 0;

		//�t���[�����[�g�X�V���Ԃ��X�V
		g_nUpdateFrameRateTime = g_nCurrentTime;
	}
}


//�t���[�����[�g�\���i�f�o�b�O�p�j
void DrawFrameRate()
{
	
}