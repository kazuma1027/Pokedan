#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include "allVariableName.h"
#include "allMethod.h"

/***********************      Main�̏���      *********************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	bool over;
	bool clear;
	bool story;
	int tmp_mx = m->x;
	int tmp_my = m->y;
	int d_num = 0;
	int tempTime = 0;
	int hpColor = 0;
	/*����������*/
	if (init() == -1) { return -1; }

	while (true) {


		prologue();

		charaInit();

		SetFontSize(16);
		SetFontThickness(4);

		over = false;
		clear = false;
		story = false;
		ClearDrawScreen();
		/*bgm�Đ��J�n*/
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		for (int i = 0; i < 256; i++) {
			SetDrawBright(i, i, i);
			allView(d_num);
			wait(10);
		}

		talk(c, "�u������...?�v");
		initMessage();
		drawExplain();
		messageflag = false;
		/*�`�悷��*/
		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0 && m->floor != 2) {

			tmp_mx = m->x;
			tmp_my = m->y;

			/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
			if (GetNowCount() - tempTime > 500)
			{
				if (d_num == 1)d_num = 0;
				else d_num = 1;
				tempTime = GetNowCount();
			}

			//�n�}��L�����Ȃǂ̕`��֐�
			allView(d_num);
			
			/*���b�Z�[�W�͏�ɏo��*/
			outMessage();

			//���������񂾂�
			if (c->hp == 0) { over = true; break; }

			/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
			showMenu();


			/*��l���̓����A�ړ���U���A�K�i�ړ�*/
			mainCharaMove();
			/*�G�̓����A�ړ���U��*/
			if (m->floor != 2) {
				mainEnemyMove(tmp_mx, tmp_my);
			}

			/*space�L�[�ŏI���*/
			if (keyState[KEY_INPUT_SPACE] == 1) { endflag = true; break; }
			if (keyState[KEY_INPUT_DOWN] == 1) { stairsMove(1); }

		}
		if (m->floor == 2) {
			for (int i = 0; i < 256; i++) {
				SetDrawBright(i, i, i);
				allView(d_num);
				wait(10);
			}
			
			talk(lastboss, "�悭�����܂ŗ�����");
			wait(10);
			talk(lastboss, "�����A����|���Ă݂�");
			wait(10);
			talk(c, "�N��˂�...");
			
		}
		//�{�X�p
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0 && m->floor == 2) {
			tmp_mx = m->x;
			tmp_my = m->y;

			/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
			if (GetNowCount() - tempTime > 500)
			{
				if (d_num == 1)d_num = 0;
				else d_num = 1;
				tempTime = GetNowCount();
			}

			//�n�}��L�����Ȃǂ̕`��֐�
			allView(d_num);

			/*���b�Z�[�W�͏�ɏo��*/
			outMessage();

			if (!lastboss->isLive) { clear = true; break; }

			//���������񂾂�
			if (c->hp == 0) { over = true; break; }

			/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
			showMenu();

			/*��l���̓����A�ړ���U���A�K�i�ړ�*/
			mainCharaMove();

			/*�G�̓����A�ړ���U��*/
			mainBossMove(tmp_mx, tmp_my);

			/*space�L�[�ŏI���*/
			if (keyState[KEY_INPUT_SPACE] == 1) { endflag = true; break; }
		}

		if (endflag)break;
		else if (over)gameover();
		else if(clear)gameClear();
		if (endflag)break;
	}
	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}







