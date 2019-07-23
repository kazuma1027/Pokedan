#include "all.h"
#include "allVariableName.h"
#include "Message.h"
#include "Generic.h"

void prologue();
void setMainChara(int);


void prologue() {
	int f_num = 0;
	PlaySoundMem(main, DX_PLAYTYPE_LOOP);
	char d[500] = "<Press A Botton>";
	int e = 0;
	while (keyState[KEY_INPUT_A] == 0 && ScreenFlip() == 0 && getCountFrame() == 0 && ClearDrawScreen() == 0) {
		DrawRotaGraph(400, 250, 1.0, 0, title[0], false);
		DrawRotaGraph(400, 250, 1.5, 0, title[1], true);
		SetFontSize(32);                             //�T�C�Y��32�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
		DrawFormatString(230, 420, GetColor(255, 0, 0), "%s", d);
		/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
		if (GetNowCount() - tempTime > 1500)
		{
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
	PlaySoundMem(start, DX_PLAYTYPE_LOOP);
	ChangeFont("���S�V�b�N�@Light");              //�ύX
	SetFontSize(20);                             //�T�C�Y��64�ɕύX
	SetFontThickness(4);                         //������8�ɕύX
	DrawRotaGraph(400, 300, 3.5, 0, bl, true);
	sprintf_s(s, "�悤�����|�P�����̐��E��");
	showDisplay(s);
	initMessage();
	sprintf_s(s, "�����炠�Ȃ��ɂ̓_���W�������N���A���Ă��炤");
	showDisplay(s);
	initMessage();
	sprintf_s(s, "�ł͏��߂Ƀv���C����|�P������I��ł��炨��");
	showDisplay(s);
	initMessage();
	double c_num = 0;
	int e_num = 0;
	int count = 0;
	DrawRotaGraph(400, 100, 3.0, 0, ball[0], true);
	DrawRotaGraph(600, 350, 3.0, 0, ball[0], true);
	DrawRotaGraph(200, 350, 3.0, 0, ball[0], true);
	ScreenFlip();
	bool flag[3] = { false,false,false };
	bool opFlag = true;
	while (opFlag && getCountFrame() == 0 && ScreenFlip() == 0) {

		if (keyState[KEY_INPUT_UP] == 1) {
			flag[0] = true;
			flag[1] = false;
			flag[2] = false;
		}
		if (keyState[KEY_INPUT_LEFT] == 1) {
			flag[0] = false;
			flag[1] = true;
			flag[2] = false;
			DrawString(390, 150, "��", BLACK);
		}
		if (keyState[KEY_INPUT_RIGHT] == 1) {
			flag[0] = false;
			flag[1] = false;
			flag[2] = true;
			DrawString(390, 150, "��", BLACK);
		}

		if (flag[0]) {
			DrawString(390, 150, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_LEFT] && !keyState[KEY_INPUT_RIGHT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{
					switch (count % 4) {
					case 0:c_num = 0; break;
					case 1:c_num = PI / 4; break;
					case 2:c_num = 0; break;
					case 3:c_num = -PI / 4; break;
					}
					count++;
					if (count == 4)count = 0;
				}
				DrawRotaGraph(400, 100, 3.0, c_num, ball[0], true);
				/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				e = 1;
				DrawRotaGraph(400, 300, 2.5, 0, z[0]->moveTexture[DOWN][e_num], true);
			}
			c_num = 0;
			count = 0;
			DrawRotaGraph(400, 100, 3.0, 0, ball[0], true);
			DrawString(390, 150, "��", BG);
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
			if (keyState[KEY_INPUT_A] == 1) {
				flag[0] = false;
				flag[1] = false;
				flag[2] = false;
				opFlag = false;
			}
		}

		if (flag[1]) {
			DrawString(190, 400, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_UP] && !keyState[KEY_INPUT_RIGHT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{	
					switch (count % 4) {
					case 0:c_num = 0; break;
					case 1:c_num = PI / 4; break;
					case 2:c_num = 0; break;
					case 3:c_num = -PI/4; break;
					}
					count++;
					if (count == 4)count = 0;
				}
				DrawRotaGraph(200, 350, 3.0, c_num, ball[0], true);
				/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				e = 2;
				DrawRotaGraph(400, 300, 2.5, 0, z[1]->moveTexture[DOWN][e_num], true);
				if (keyState[KEY_INPUT_A] == 1)opFlag = false;
			}
			c_num = 0;
			e_num = 0;
			count = 0;
			DrawRotaGraph(200, 350, 3.0, 0, ball[0], true);
			DrawString(190, 400, "��", BG);
			if (keyState[KEY_INPUT_UP] == 1) {
				flag[0] = true;
				flag[1] = false;
				flag[2] = false;
			}
			if (keyState[KEY_INPUT_RIGHT] == 1) {
				flag[0] = false;
				flag[1] = false;
				flag[2] = true;
			}
			if (keyState[KEY_INPUT_A] == 1) {
				flag[0] = false;
				flag[1] = false;
				flag[2] = false;
				opFlag = false;
			}
		}
		if (flag[2]) {
			DrawString(590, 400, "��", RED);
			DrawRotaGraph(400, 300, 0.5, 0, bl, true);
			while (ScreenFlip() == 0 && getCountFrame() == 0 && !keyState[KEY_INPUT_UP] && !keyState[KEY_INPUT_LEFT] && !keyState[KEY_INPUT_A]) {

				if (GetNowCount() - tempTime > 500)
				{
					switch (count % 4) {
					case 0:c_num = 0; break;
					case 1:c_num = PI / 4; break;
					case 2:c_num = 0; break;
					case 3:c_num = -PI / 4; break;
					}
					count++;
					if (count == 4)count = 0;
				}
				DrawRotaGraph(600, 350, 3.0, c_num, ball[0], true);
				/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
				if (GetNowCount() - tempTime > 500)
				{
					if (e_num == 1)e_num = 0;
					else e_num = 1;
					tempTime = GetNowCount();
				}
				e = 3;
				DrawRotaGraph(400, 300, 2.5, 0, z[2]->moveTexture[DOWN][e_num], true);
				if (keyState[KEY_INPUT_A] == 1)opFlag = false;
			}
			c_num = 0;
			e_num = 0;
			count = 0;
			DrawRotaGraph(600, 350, 3.0, 0, ball[0], true);
			DrawString(590, 400, "��", BG);
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
			if (keyState[KEY_INPUT_A] == 1) {
				flag[0] = false;
				flag[1] = false;
				flag[2] = false;
				opFlag = false;
			}
		}
	}
	setMainChara(e);
	messageflag = false;
	initMessage();
	SetFontSize(18);
	StopSoundMem(start);

}


void setMainChara(int e) {
	if (e == 1) {
		c->moveTexture[DOWN][0] = LoadGraph("�摜/�s�J�`���Ed_1.png");
		c->moveTexture[DOWN][1] = LoadGraph("�摜/�s�J�`���Ed_2.png");
		c->moveTexture[UP][0] = LoadGraph("�摜/�s�J�`���Eu_1.png");
		c->moveTexture[UP][1] = LoadGraph("�摜/�s�J�`���Eu_2.png");
		c->moveTexture[LEFT][0] = LoadGraph("�摜/�s�J�`���El_1.png");
		c->moveTexture[LEFT][1] = LoadGraph("�摜/�s�J�`���El_2.png");
		c->moveTexture[RIGHT][0] = LoadGraph("�摜/�s�J�`���Er_1.png");
		c->moveTexture[RIGHT][1] = LoadGraph("�摜/�s�J�`���Er_2.png");
	}
	else if (e == 2) {
		c->moveTexture[DOWN][0] = LoadGraph("�摜/�q�m�A���Vd_1.png");
		c->moveTexture[DOWN][1] = LoadGraph("�摜/�q�m�A���Vd_2.png");
		c->moveTexture[UP][0] = LoadGraph("�摜/�q�m�A���Vu_1.png");
		c->moveTexture[UP][1] = LoadGraph("�摜/�q�m�A���Vu_2.png");
		c->moveTexture[LEFT][0] = LoadGraph("�摜/�q�m�A���Vl_1.png");
		c->moveTexture[LEFT][1] = LoadGraph("�摜/�q�m�A���Vl_2.png");
		c->moveTexture[RIGHT][0] = LoadGraph("�摜/�q�m�A���Vr_1.png");
		c->moveTexture[RIGHT][1] = LoadGraph("�摜/�q�m�A���Vr_2.png");
	}
	else if (e == 3) {
		c->moveTexture[DOWN][0] = LoadGraph("�摜/�[�j�K��d_1.png");
		c->moveTexture[DOWN][1] = LoadGraph("�摜/�[�j�K��d_2.png");
		c->moveTexture[UP][0] = LoadGraph("�摜/�[�j�K��u_1.png");
		c->moveTexture[UP][1] = LoadGraph("�摜/�[�j�K��u_2.png");
		c->moveTexture[LEFT][0] = LoadGraph("�摜/�[�j�K��l_1.png");
		c->moveTexture[LEFT][1] = LoadGraph("�摜/�[�j�K��l_2.png");
		c->moveTexture[RIGHT][0] = LoadGraph("�摜/�[�j�K��r_1.png");
		c->moveTexture[RIGHT][1] = LoadGraph("�摜/�[�j�K��r_2.png");
	}

}