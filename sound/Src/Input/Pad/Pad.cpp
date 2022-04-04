#include "Pad.h"

#include "DxLib.h"

//�C���X�^���X�̎��̐錾
CPad* CPad::pad_ = nullptr;

//�R���X�g���N�^
CPad::CPad()
	:current_button_buf_()
	, pre_button_buf_()
	, current_trigger_buf_()
	, pre_trigger_buf_()
	, stick_buf_()
{
}

//�f�X�g���N�^
CPad::~CPad()
{
}

//������
void CPad::Init()
{
	//-----�p�b�h��񏉊���-----//
	//�{�^��
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		current_button_buf_[button_index] = '\0';
		pre_button_buf_[button_index] = '\0';
	}

	//�g���K�[
	for (int trigger_index = 0; trigger_index < TRIGGER_MAX; trigger_index++)
	{
		current_trigger_buf_[trigger_index] = '\0';
		pre_trigger_buf_[trigger_index] = '\0';
	}

	//�X�e�B�b�N
	for (int stick_index = 0; stick_index < STICK_MAX; stick_index++)
	{
		stick_buf_[stick_index] = '\0';
	}
}

//�X�e�b�v
void CPad::Step()
{
	//-----�p�b�h���X�e�b�v-----//
	XINPUT_STATE input_pad;

	//�O�t���[���̃{�^�������L�^���Ă���
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		pre_button_buf_[button_index] = current_button_buf_[button_index];
	}

	//�O�t���[���̃g���K�[�����L�^���Ă���
	for (int trigger_index = 0; trigger_index < TRIGGER_MAX; trigger_index++)
	{
		pre_trigger_buf_[trigger_index] = current_trigger_buf_[trigger_index];
	}

	//�Q�[���p�b�h�̓��͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input_pad);


	//���͏����e�����o�ϐ��Ɉڂ�

	//�{�^��
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		current_button_buf_[button_index] = input_pad.Buttons[button_index];
	}
	
	//���E�̃g���K�[
	//unsigned char�^�̃T�C�Y���Ŋ��邱�ƂŁA�u0.0f�`1.0f�v�̒l�����ł���
	current_trigger_buf_[LEFT_TRIGGER] = (float)input_pad.LeftTrigger / UCHAR_MAX;
	current_trigger_buf_[RIGHT_TRIGGER] = (float)input_pad.RightTrigger / UCHAR_MAX;

	//���E�̃X�e�B�b�N
	//short�^�̃T�C�Y���Ŋ��邱�ƂŁA�u-1.0f�`1.0f�v�̒l�����ł���
	stick_buf_[LEFT_STICK_X] = (float)input_pad.ThumbLX / SHRT_MAX;
	stick_buf_[LEFT_STICK_Y] = (float)input_pad.ThumbLY / SHRT_MAX;
	stick_buf_[RIGHT_STICK_X] = (float)input_pad.ThumbRX / SHRT_MAX;
	stick_buf_[RIGHT_STICK_Y] = (float)input_pad.ThumbRY / SHRT_MAX;
}


//�������ꂽ��
bool CPad::IsPush(int button_code)
{
	//�O�t���ŉ�����Ă��Ȃ��@���@���t���ŉ�����Ă���
	if (pre_button_buf_[button_code] == 0 && current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//�P���ɉ����ꂽ��
bool CPad::IsDown(int button_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//�����������Ă��邩
bool CPad::IsKeep(int button_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (pre_button_buf_[button_code] == 1 && current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//���ܗ����ꂽ��
bool CPad::IsRelease(int button_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (pre_button_buf_[button_code] == 1 && current_button_buf_[button_code] == 0)
		return true;

	return false;
}

//�g���K�[�l�̎擾
//���O�ɋ߂Â��قǎア�������݁A�P�ɋ߂Â��قǋ�����������
float CPad::GetTriggerValue(PAD_TRIGGER trigger_kind)
{
	return current_trigger_buf_[trigger_kind];
}

//�X�e�B�b�N�l�̎擾
//���u�|�P�ȏ�O�����v�Ȃ獶�A�܂��͉�
//�@�u�O���傫���P�ȉ��v�Ȃ�E�A�܂��͏�ɌX���Ă���
float CPad::GetStickValue(PAD_STICK stick_kind)
{
	return stick_buf_[stick_kind];
}