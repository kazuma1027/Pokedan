#include "all.h"
#include "allVariableName.h"
#include "Generic.h"

bool endflag = false;

void gameover() {
	sprintf_s(s, "�v���C���[�͎���ł��܂���");
	showDisplay(s);
	int tempTime = 0;
	char h[256];
	sprintf_s(h, "�Q�[�����I������:A");
	sprintf_s(s, "���g���C����:B");
	tempTime = GetNowCount();
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {
		/*if (GetNowCount() - tempTime > 500 && g_num!=3)
		{
		DrawRotaGraph(400, 300, 0.5, 0, over[0], false);
			if (g_num == 1) {
				DrawRotaGraph(400, 300, 0.5, 0, over[1], false);
				g_num = 2;
			}
			else if (g_num == 2) {
				DrawRotaGraph(400, 300, 0.5, 0, over[2], false);
				g_num = 3;
			}
			tempTime = GetNowCount();
		}
		else if (g_num == 3) {
			DrawRotaGraph(400, 300, 0.5, 0, over[2], false);
		}*/
		SetFontSize(26);                             //�T�C�Y��26�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
		DrawRotaGraph(400, 300, 1.5, 0, over[0], false);
		DrawFormatString(270, 470, GetColor(255, 0, 0), "%s", h);
		DrawFormatString(300, 520, GetColor(0, 255, 0), "%s", s);
		if (keyState[KEY_INPUT_A] == 1) { endflag = true; break; }
	}
}