#pragma once
#include "allVariableName.h"
#include "Generic.h"

char message1[256];
char message2[256];
char message3[256];
char s[256];				//sprintf_s�p�̔z��

int messageBox;
bool menuflag = false;
bool messageflag = false;

void showDisplay(char[]);

/*���̃R���\�[��������*/
void initConsole() {

	/*���b�Z�[�W�t���O�������Ă���΁A���b�Z�[�W�{�b�N�X�\��*/
	/*�㏑�����Ă���*/
	if (messageflag) {
		DrawRotaGraph(SCREEN_WIDTH / 2, 500, 1, 0, messageBox, true);
	}
}

/*�\�����郁�b�Z�[�W���Z�b�g*/
void setMessage(char s[]) {

	messageflag = true;

	char temp[256];
	/*������*/
	for (int i = 0; i < 256; i++)temp[i] = '\0';

	/*������R�s�[*/
	for (int i = 0; s[i] != '\0'; i++) { temp[i] = s[i]; }

	/*message1->��i�Amessage2->���i�Amessage3->���i*/
	if (message1[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message1[i] = temp[i]; }
	else if (message2[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message2[i] = temp[i]; }
	else if (message3[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message3[i] = temp[i]; }
	/*�S�Ė��܂��Ă���΁A���e����i���グ�ĕ\������*/
	else {
		for (int i = 0; i < 256; i++) { message1[i] = '\0'; }
		for (int i = 0; i < 256; i++) { message1[i] = message2[i]; }

		for (int i = 0; i < 256; i++)message2[i] = '\0';
		for (int i = 0; i < 256; i++) { message2[i] = message3[i]; }

		for (int i = 0; i < 256; i++) { message3[i] = temp[i]; }
	}
}

/*���b�Z�[�W�\��*/
void outMessage() {

	initConsole();
	/*�R���\�[���\��*/
	DrawFormatString(100, 487, GetColor(255, 255, 255), "%s", message1);
	DrawFormatString(100, 517, GetColor(255, 255, 255), "%s", message2);
	DrawFormatString(100, 547, GetColor(255, 255, 255), "%s", message3);
}



//���b�Z�[�W������
void initMessage() {
	messageflag = false;
	for (int i = 0; i < 256; i++) {
		message1[i] = '\0';
		message2[i] = '\0';
		message3[i] = '\0';
	}
}


void showDisplay(char ss[]) {
	int sound = LoadSoundMem("���y/string.mp3");
	char tmp[256];
	//�ꉞ������
	for (int i = 0; i < 256; i++) { tmp[i] = '\0'; }

	messageflag = true;

	for (int i = 0; ss[i] != '\0'; i++) {
		ScreenFlip();
		wait(10);
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		tmp[i] = ss[i];
		initMessage();
		setMessage(tmp);
		outMessage();
	}
	initMessage();
	setMessage(ss);
	outMessage();
	ScreenFlip();
	wait_key(KEY_INPUT_A);
}