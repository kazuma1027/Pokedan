#include "all.h"
#include "allVariableName.h"
#include "Generic.h"
#include "Message.h"

bool endflag = false;
bool startflag = false;

void gameover() {
	StopSoundMem(bgm);
	StopSoundMem(boss_bgm);
	int overSound = LoadSoundMem("���y/over.mp3");
	char h[256];
	sprintf_s(s, "�v���C���[�͎���ł��܂���!");
	initMessage();
	messageflag = true;
	setMessage(s);
	outMessage();
	ScreenFlip();
	PlaySoundMem(overSound, DX_PLAYTYPE_NORMAL);
	wait_key(KEY_INPUT_A);
	sprintf_s(h, "�Q�[�����I������:A");
	sprintf_s(s, "���g���C����:B");
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {
		SetFontSize(26);                             //�T�C�Y��26�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
		DrawRotaGraph(400, 300, 1.5, 0, over[0], false);
		DrawFormatString(270, 470, GetColor(255, 0, 0), "%s", h);
		DrawFormatString(300, 520, GetColor(0, 255, 0), "%s", s);
		if (keyState[KEY_INPUT_A] == 1) { endflag = true; break; }
		if (keyState[KEY_INPUT_B] == 1) { break; }
	}
}

void gameClear() {
	StopSoundMem(boss_bgm);
	int clearSound = LoadSoundMem("���y/clear.mp3");
	char h[256];
	char clear[256];
	sprintf_s(s, "�_���W�����𐧔e����!!!");
	initMessage();
	messageflag = true;
	setMessage(s);
	outMessage();
	ScreenFlip();
	wait_key(KEY_INPUT_A);
	sprintf_s(h, "�Q�[�����I������:A");
	sprintf_s(s, "���g���C����:B");
	sprintf_s(clear, "GameClear!!!");
	PlaySoundMem(clearSound, DX_PLAYTYPE_NORMAL);
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {
		SetFontSize(26);                             //�T�C�Y��26�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
		DrawFormatString(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2, WHITE, "%s", clear);
		DrawFormatString(270, 470, RED, "%s", h);
		DrawFormatString(300, 520, BLUE, "%s", s);
		if (keyState[KEY_INPUT_A] == 1) { endflag = true; break; }
		if (keyState[KEY_INPUT_B] == 1) { break; }
	}
}