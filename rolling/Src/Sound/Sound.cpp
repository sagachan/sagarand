#include "DxLib.h"
#include "Sound.h"

CSound::BGMInfo CSound::bgm[BGM_NUM];
//CSound::SEInfo CSound::se[SE_NUM];


//BGM�̃t�@�C���p�X
const char bgm_FilePath[CSound::BGM_NUM][256] =
{
 "Data/Sound/",  //�^�C�g������BGM
 "Data/Sound/",  //�v���C����BGM
 "Data/Sound/",  //�N���A����BGM
 "Data/Sound/",  //�Q�[���I�[�o�[����BGM
};

////���ʉ��̃t�@�C���p�X
//const char se_FilePath[CSound::SE_NUM][256] =
//{
// ,   //�e���ˌ��ʉ�
// ,  //���j���ʉ�
// , //������ʉ�
//};


//�T�E���h�̏�����
void CSound::InitSound()
{
    //BGM�̏�����
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        bgm[bgm_index].handle = 0;
        bgm[bgm_index].kind = BGM_NONE;
    }

    ////���ʉ��̏�����
    //for (int se_index = 0; se_index < SE_NUM; se_index++)
    //{
    //    se[se_index].handle = 0;
    //    se[se_index].kind = SE_NONE;
    //}
}

void CSound::LoadBGM(BGM_KIND kind)
{
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        //���g�p�Ȃ�
        if (bgm[bgm_index].handle == 0)
        {
            //�ǂݍ���
            bgm[bgm_index].handle = LoadSoundMem(bgm_FilePath[kind]);
            bgm[bgm_index].kind = kind;

            break;
        }
    }
}

////���ʉ��T�E���h�̓ǂݍ���
//void CSound::LoadSE(SE_KIND kind)
//{
//    for (int se_index = 0; se_index < SE_NUM; se_index++)
//    {
//        //���g�p�Ȃ�
//        if (se[se_index].handle == 0)
//        {
//            //�ǂݍ���
//            se[se_index].handle = LoadSoundMem(se_FilePath[kind]);
//            se[se_index].kind = kind;
//
//            break;
//        }
//    }
//}

//BGM�̍Đ�
void CSound::PlayBGM(BGM_KIND kind)
{
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        //�Y����BGM����
        if (bgm[bgm_index].kind == kind)
        {
            ////---���ʉ�����---//
            //if (kind == BGM_PLAY)
            //{
            //    //�e�̌��ʉ�����
            //    ChangeVolumeSoundMem(140, bgm[bgm_index].handle);
            //}
            
            PlaySoundMem(bgm[bgm_index].handle, DX_PLAYTYPE_LOOP, true);
            break;
        }
    }
}

////���ʉ��̍Đ�
//void CSound::PlaySE(SE_KIND kind)
//{
//    for (int se_index = 0; se_index < SE_NUM; se_index++)
//    {
//        //�Y���̌��ʉ�����
//        if (se[se_index].kind == kind)
//        {
//
//            PlaySoundMem(se[se_index].handle, DX_PLAYTYPE_BACK, true);
//            break;
//        }
//    }
//}

//�T�E���h�̌㏈��
void CSound::FinSound()
{
    //BGM��S�Ē�~���Ĕj��
    for (int bgm_index = 0; bgm_index < BGM_NUM; bgm_index++)
    {
        StopSoundMem(bgm[bgm_index].handle);
        DeleteSoundMem(bgm[bgm_index].handle);
    }

    ////���ʉ���S�Ĕj��
    //for (int se_index = 0; se_index < SE_NUM; se_index++)
    //{
    //    DeleteSoundMem(se[se_index].handle);
    //}
}