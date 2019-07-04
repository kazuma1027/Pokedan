#include "DxLib.h"

char keyState[256];

/*�L�[��������Ă���t���[�����𐔂���*/
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			keyState[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			keyState[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	DxLib_Init();   // DX���C�u��������������
	//SettingAfterInit();
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	int Handle;     // �摜�i�[�p�n���h��
	Handle = LoadGraph("�摜/chara.jpg"); // �摜�̃��[�h

	int x = 100;
	int	y = 100;
	bool flag = false;

	DrawRotaGraph(x, y, 0.01, 0, Handle, TRUE);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {

		DrawRotaGraph(x,y,0.2, 0,Handle, TRUE);

		if (keyState[KEY_INPUT_Q]!=0) {flag = true;}
		else if(keyState[KEY_INPUT_D]>2&&keyState[KEY_INPUT_D]<20){ }
		else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_D]) { x += 3; }
		else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_A]) { x -= 3; }
		else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_W]) { y -= 3; }
		else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_X]) { y += 3; }
		else if (keyState[KEY_INPUT_D]) { x++; }
		else if (keyState[KEY_INPUT_A]) { x--; }
		else if (keyState[KEY_INPUT_W]) { y--; }
		else if (keyState[KEY_INPUT_X]) { y++; }

		//switch (*keyState) {
		//case KEY_INPUT_D: x++; break;
		//case KEY_INPUT_W: y++; break;
		//case KEY_INPUT_A: x--; break;
		//case KEY_INPUT_X: y--; break;
		//case KEY_INPUT_Q: flag = true; break;
		//default: break;
		//}

		if (flag) {
			break;
		}
	}
	DxLib_End();    // DX���C�u�����I������
	return 0;
}