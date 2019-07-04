#include "DxLib.h"

#define SCREEN_WIDTH     (1280)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (720)                          // ��ʂ̏c��
#define CHIP_SIZE        (32)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // �}�b�v�̏c��


char keyState[256];

int FrameStartTime = 0;

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
	
	
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
	SetBackgroundColor(100, 0, 100);
	ChangeWindowMode(TRUE);
	DxLib_Init();					// DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);  //�`���𗠉�ʂɐݒ�

	
	/*�摜�t�@�C���ǂݍ��݂̑O�ɓ��ߏ���*/
	SetTransColor(255, 255, 255);
	
	
	int Mario;     // �摜�i�[�p�n���h��
	Mario = LoadGraph("�摜/Mario.png"); // �摜�̃��[�h
	

	double temp = 0;
	double y_temp = 0;
	double y_prev = 0;
	double f = 0;

	double x = 100;
	double	y = 100;
	bool endflag = false;
	bool onGround = false;
	bool jump = false;
	bool bigFlag = true;
	bool xVec = false;

	SetWaitVSyncFlag(FALSE);
	FrameStartTime = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		
		ClsDrawScreen();

		/*60�t���[���Œ�*/
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		FrameStartTime = GetNowCount();

		DrawRotaGraph((int)x,(int)y,0.2, 0, Mario, TRUE);

		if (bigFlag) {

			if (keyState[KEY_INPUT_Q] != 0) { endflag = true; }
			/*B�_�b�V��*/
			else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_D]) { if(x<SCREEN_WIDTH-30) x += 5; }
			else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_A]) { if(x>30) x -= 5; }
			else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_W]) { if(y>30) y -= 5; }
			else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_X]) { if(y<SCREEN_HEIGHT-30) y += 5; }
			else if (keyState[KEY_INPUT_D]) { if(x<SCREEN_WIDTH-30) x++; }
			else if (keyState[KEY_INPUT_A]) { if(x>30) x--; }
			else if (keyState[KEY_INPUT_W]) { if(y>30) y--; }
			else if (keyState[KEY_INPUT_X]) { if(y<SCREEN_HEIGHT-30) y++; }
			
			/*�W�����v����*/
			if (keyState[KEY_INPUT_SPACE] == 1) { 
				y_prev = y; temp = y;
				xVec = true; onGround = true; bigFlag = false; 
			}

		}

		if (onGround) {
			if (y >= 260) {
				f = -40;
				y_temp = y;
				y += (y - y_prev) + f;
				y_prev = y_temp;
			}
			else {
				y_temp = 30;
				y = 30;
				y_prev = y_temp;
			}
			
			jump = true;
			onGround = false;
		}

		if (jump) {
			f = 3;
			y_temp = y;
			y += (y - y_prev) + f;
			y_prev = y_temp;
			if (y >= temp) {
				y = temp;
				bigFlag = true;
				jump = false;
				xVec = false;
			}
		}

		if (xVec) {
			if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_D]) { if(x<SCREEN_WIDTH-30) x += 5; }
			else if (keyState[KEY_INPUT_B] && keyState[KEY_INPUT_A]) { if(x>30) x -= 5; }
			else if (keyState[KEY_INPUT_D])if(x<SCREEN_WIDTH-30)x++;
			else if (keyState[KEY_INPUT_A])if(x>30)x--;
		}

		if (endflag) {
			break;
		}
	}
	DxLib_End();    // DX���C�u�����I������
	return 0;
}