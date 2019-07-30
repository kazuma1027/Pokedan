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



void showMessage(char s[]) {
	int sound = LoadSoundMem("���y/string.mp3");
	char tmpSt[256];
	//�ꉞ�������A\0�ł͕����������N�����̂ŋ󔒂ŏ�����
	for (int i = 0; i < 256; i++) { tmpSt[i] = ' '; }

	messageflag = true;
	for (int k = 0; s[k] != '\0'; k++) {
		initMessage();
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		tmpSt[k] = s[k];
		//setMessage���g�p����ƃG���[���N�����̂Ŏ蓮�œ����
		for (int i = 0; i < 256; i++)message1[i] = tmpSt[i];
		messageflag = true;		
		outMessage();
		ScreenFlip();
		wait(3);
	}
	initMessage();
	setMessage(s);
	outMessage();
	ScreenFlip();
	wait_key(KEY_INPUT_A);
	initMessage();
}

void talk(pokemon* me,char s[]) {
	int sound = LoadSoundMem("���y/string.mp3");
	char tmpSt[256];
	//�ꉞ�������A\0�ł͕����������N�����̂ŋ󔒂ŏ�����
	for (int i = 0; i < 256; i++) { tmpSt[i] = ' '; }
	int tmp = 0;
	int tmp2 = 0;
	messageflag = true;
	initConsole();
	for (int i = 0; i < 256; i++) { message1[i] = me->name[i]; }
	DrawFormatString(100, 487, RED, "%s", message1);
	ScreenFlip();
	for (int k = 0; s[k] != '\0'; k++) {
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		tmpSt[k] = s[k];
		//setMessage���g�p����ƃG���[���N�����̂Ŏ蓮�œ����
		for (int i = 0; i < 256; i++) { message2[i] = tmpSt[i]; }
		DrawFormatString(100, 517, WHITE, "%s", message2);
		messageflag = true;
		ScreenFlip();
		wait(3);
	}
	DrawFormatString(100, 517, WHITE, "%s", s);
	ScreenFlip();
	wait_key(KEY_INPUT_A);
	initMessage();
}
