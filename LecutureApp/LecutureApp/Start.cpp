#include "all.h"
#include "allVariableName.h"
#include "Message.h"
#include "Generic.h"
#include "FileIO.h"
#include "Init.h"

void prologue();
void setMainChara(int);
void gameStart();

bool continueflag = false;

void prologue() {
	int select = LoadSoundMem("���y/select.mp3");
	int f_num = 0;
	PlaySoundMem(main, DX_PLAYTYPE_LOOP);
	char logo[256] = "�͂��߂���";
	char logo2[256] = "�Â�����";

	FILE *fp;
	errno_t error;
	//�t�A�C�����J����=�t�@�C�������݂���
	error = fopen_s(&fp, "saveData.txt", "r");

	while (keyState[KEY_INPUT_A] == 0 && ScreenFlip() == 0 && getCountFrame() == 0 && ClearDrawScreen() == 0) {
		DrawRotaGraph(400, 250, 1.0, 0, title[0], false);
		DrawRotaGraph(400, 250, 1.5, 0, title[1], true);
		SetFontSize(32);                             //�T�C�Y��32�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
		if (continueflag && keyState[KEY_INPUT_LEFT] == 1) { continueflag = false; PlaySoundMem(select, DX_PLAYTYPE_BACK); }
		if (!continueflag && keyState[KEY_INPUT_RIGHT] == 1) { 
			if (error == 0) {
				continueflag = true; PlaySoundMem(select, DX_PLAYTYPE_BACK);
			}
			else {
				initMessage();
				setMessage("�Z�[�u�f�[�^���Ȃ��̂őI�ׂ܂���");
				outMessage();
				ScreenFlip();
				tempTime = GetNowCount();
			}
		}

		outMessage();

		if (!continueflag)DrawFormatString(230, 455, WHITE, "��");
		if (continueflag)DrawFormatString(500, 455, WHITE, "��");

		DrawFormatString(160, 420, RED, "%s", logo);
		DrawFormatString(430, 420, BLUE, "%s", logo2);
		/*1500ms(1.5�b)�Ɉ�x�摜�X�V*/
		if (GetNowCount() - tempTime > 1500)
		{	
			initMessage();
			if (f_num == 1) {
				f_num = 0;
				DrawRotaGraph(400, 250, 1.0, 0, title[0], false);
				DrawRotaGraph(400, 250, 1.5, 0, title[1], true);
				wait(100);
			}
			else {
				f_num = 1;
			}
			tempTime = GetNowCount();
		}
	}
	StopSoundMem(main);
	ChangeFont("���S�V�b�N�@Light");              //�ύX
	SetFontSize(20);                             //�T�C�Y��64�ɕύX
	SetFontThickness(4);                         //������8�ɕύX
	ClearDrawScreen();
	fclose(fp);
	if (!continueflag)gameStart();
}


void gameStart() {
	int select = LoadSoundMem("���y/select.mp3");
	/*�����~�߂�*/

	char tmpString[256];
	for (int i = 0; i < 256; i++) {
		tmpString[i] = '\0';
	}

	int e = 0;

	PlaySoundMem(startSound, DX_PLAYTYPE_LOOP);
	showMessage("�悤�����|�P�����̐��E��");
	showMessage("�����炠�Ȃ��ɂ̓_���W�������N���A���Ă��炤");
	showMessage("�ł͏��߂Ƀv���C����|�P������I��ł��炨��");

	double angle = 0;
	int e_num = 0;
	int count = 0;
	DrawRotaGraph(400, 100, 3.0, 0, ball[0], true);
	DrawRotaGraph(600, 350, 3.0, 0, ball[0], true);
	DrawRotaGraph(200, 350, 3.0, 0, ball[0], true);
	ScreenFlip();
	bool flag[3] = { false,false,false };
	bool opFlag = true;
	while (opFlag && getCountFrame() == 0 && ScreenFlip() == 0 && ProcessMessage() == 0) {

		initMessage();
		sprintf_s(tmpString, 256, "�ł͏��߂Ƀv���C����|�P������I��ł��炨��");
		setMessage(tmpString);
		outMessage();


		if (flag[0]) {
			PlaySoundMem(select, DX_PLAYTYPE_BACK);
			e = 1;
			PlaySoundMem(z[e - 1]->voice, DX_PLAYTYPE_BACK);
			DrawString(390, 150, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_LEFT] && !keyState[KEY_INPUT_RIGHT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{
					switch (count % 4) {
					case 0:angle = 0; break;
					case 1:angle = PI / 4; break;
					case 2:angle = 0; break;
					case 3:angle = -PI / 4; break;
					}
					count++;
					if (count == 4)count = 0;
				}

				DrawRotaGraph(400, 100, 3.0, angle, ball[0], true);

				/*500ms(0.5�b)�Ɉ�x�摜�X�V*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				DrawRotaGraph(400, 300, 2.5, 0, z[0]->moveTexture[DOWN][e_num], true);
			}
			keyState[KEY_INPUT_UP] = 0;
			angle = 0;
			e_num = 0;
			count = 0;
			DrawRotaGraph(400, 100, 3.0, 0, ball[0], true);
			DrawRotaGraph(400, 170, 0.2, 0, bl, true);
		}

		if (flag[1]) {
			PlaySoundMem(select, DX_PLAYTYPE_BACK);
			e = 2;
			PlaySoundMem(z[e - 1]->voice, DX_PLAYTYPE_BACK);
			DrawString(190, 400, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_UP] && !keyState[KEY_INPUT_RIGHT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{
					switch (count % 4) {
					case 0:angle = 0; break;
					case 1:angle = PI / 4; break;
					case 2:angle = 0; break;
					case 3:angle = -PI / 4; break;
					}
					count++;
					if (count == 4)count = 0;
				}
				DrawRotaGraph(200, 350, 3.0, angle, ball[0], true);
				/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				DrawRotaGraph(400, 300, 2.5, 0, z[1]->moveTexture[DOWN][e_num], true);
				if (keyState[KEY_INPUT_A] == 1)opFlag = false;
			}
			keyState[KEY_INPUT_LEFT] = 0;
			angle = 0;
			e_num = 0;
			count = 0;
			DrawRotaGraph(200, 350, 3.0, 0, ball[0], true);
			DrawRotaGraph(200, 420, 0.2, 0, bl, true);
		}
		if (flag[2]) {
			PlaySoundMem(select, DX_PLAYTYPE_BACK);
			e = 3;
			PlaySoundMem(z[e - 1]->voice, DX_PLAYTYPE_BACK);
			DrawString(590, 400, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_UP] && !keyState[KEY_INPUT_LEFT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{
					switch (count % 4) {
					case 0:angle = 0; break;
					case 1:angle = PI / 4; break;
					case 2:angle = 0; break;
					case 3:angle = -PI / 4; break;
					}
					count++;
					if (count == 4)count = 0;
				}
				DrawRotaGraph(600, 350, 3.0, angle, ball[0], true);
				/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				DrawRotaGraph(400, 300, 2.5, 0, z[2]->moveTexture[DOWN][e_num], true);
			}
			keyState[KEY_INPUT_RIGHT] = 0;
			angle = 0;
			e_num = 0;
			count = 0;
			DrawRotaGraph(600, 350, 3.0, 0, ball[0], true);
			DrawRotaGraph(600, 420, 0.2, 0, bl, true);
		}


		if (keyState[KEY_INPUT_UP] == 1) {
			flag[0] = true;
			flag[1] = false;
			flag[2] = false;
		}
		if (keyState[KEY_INPUT_LEFT] == 1) {
			flag[0] = false;
			flag[1] = true;
			flag[2] = false;
		}
		if (keyState[KEY_INPUT_RIGHT] == 1) {
			flag[0] = false;
			flag[1] = false;
			flag[2] = true;
		}
		if ((flag[0] || flag[1] || flag[2]) && keyState[KEY_INPUT_A]) {
			PlaySoundMem(select, DX_PLAYTYPE_BACK);
			sprintf_s(tmpString, "%s�ł�������?", z[e - 1]->name);
			setMessage(tmpString);
			setMessage("YES��Y");
			setMessage("NO��N");
			messageflag = true;
			while (getCountFrame() == 0 && ScreenFlip() == 0 && ProcessMessage() == 0) {
				outMessage();
				if (keyState[KEY_INPUT_Y]) {
					flag[0] = false;
					flag[1] = false;
					flag[2] = false;
					opFlag = false;
					initConsole();
					initMessage();
					break;
				}
				if (keyState[KEY_INPUT_N]) {
					flag[0] = false;
					flag[1] = false;
					flag[2] = false;
					initConsole();
					initMessage();
					break;
				}
			}
		}
	}
	setMainChara(e);
	messageflag = false;
	initMessage();
	SetFontSize(18);
	StopSoundMem(startSound);

}

void setMainChara(int e) {
	if (e == 1) {
		c->name = MAINCHARANAME1;
	}
	else if (e == 2) {
		c->name = MAINCHARANAME2;
	}
	else if (e == 3) {
		c->name = MAINCHARANAME3;
	}
	charaSet(c);
}