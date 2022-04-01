#pragma once
#include "DxLib.h"



class CSound {
public:

	//BGM�̎��
	enum BGM_KIND
	{
		BGM_NONE = -1,

		BGM_TITLE = 0,  //�^�C�g���V�[����BGM
		BGM_PLAY,   //�v���C�V�[����BGM
		BGM_CLEAR,   //�N���A�V�[����BGM
		BGM_GAMEOVER,  //�Q�[���I�[�o�[�V�[����BGM
		MOVE,    //�ړ���
		BGM_NUM,   //BGM�̌�
	};

	//enum SE_KIND
	//{
	//	SE_NONE = -1,


	//	SHOT,    //���ˉ�
	//	DEFEAT,    //���j��
	//	DECISION,   //����
	//	SE_NUM,
	//};

	//�T�E���h������
	static void InitSound();

	//�T�E���h�ǂݍ���
	static void LoadBGM(BGM_KIND kind);
	/*static void LoadSE(SE_KIND kind);*/

	//�T�E���h�Đ�
	static void PlayBGM(BGM_KIND kind);
	/*static void PlaySE(SE_KIND kind);*/

	//�T�E���h�㏈��
	static void FinSound();

private:

	//BGM���
	struct BGMInfo
	{
		BGM_KIND kind;
		int handle;
	};

	////���ʉ����
	//struct SEInfo
	//{
	//	SE_KIND kind;
	//	int handle;
	//};

	static BGMInfo bgm[BGM_NUM];
	/*static SEInfo se[SE_NUM];*/

};