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

		ClearDrawScreen();
		/*bgm�Đ��J�n*/
		if (m->floor != 2) {
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		}
		else {
			PlaySoundMem(boss_bgm, DX_PLAYTYPE_LOOP);
		}
		for (int i = 0; i < 256; i++) {
			SetDrawBright(i, i, i);
			allView(d_num);
			wait(10);
		}
		if (!continueflag) {
			talk(c, "�u������...?�v");
			initMessage();
			drawExplain();
		}
		isReturn = true;
		over = false;
		clear = false;
		story = false;
		messageflag = false;
		continueflag = false;
		endflag = false;
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
			

			//���������񂾂�
			if (c->hp == 0) { over = true; break; }

			/*��l���̓����A�ړ���U���A�K�i�ړ�*/
			mainCharaMove();
			if (m->floor != 2) {
				allView(d_num);
			}
			/*�G�̓����A�ړ���U��*/
			if (m->floor != 2) {
				mainEnemyMove(tmp_mx, tmp_my);
			}
			/*���b�Z�[�W�͏�ɏo��*/
			outMessage();
			/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
			showMenu();

			if (endflag) { break; }
		}
		if (m->floor == 2 && !isReturn) {
			for (int i = 0; i < 256; i++) {
				SetDrawBright(i, i, i);
				allView(d_num);
				wait(10);
			}
			
			talk(lastboss, "�悭�����܂ŗ�����");
			wait(10);
			talk(lastboss, "�����A����|���Ă݂�");
			wait(10);
			ClearDrawScreen();
			allView(d_num);
			talk(c, "���X�{�X������...");
			
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


			if (!lastboss->isLive) { clear = true; break; }

			//���������񂾂�
			if (c->hp == 0) { over = true; break; }


			/*��l���̓����A�ړ���U���A�K�i�ړ�*/
			mainCharaMove();
			allView(d_num);
			/*�G�̓����A�ړ���U��*/
			mainBossMove(tmp_mx, tmp_my);

			/*���b�Z�[�W�͏�ɏo��*/
			outMessage();
			/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
			showMenu();

			/*space�L�[�ŏI���*/
			if (endflag) { break; }
		}
		StopSoundMem(boss_bgm);
		StopSoundMem(bgm);
		if (endflag && !isReturn)break;
		else if (over)gameover();
		else if(clear)gameClear();
		if (endflag && !isReturn)break;
	}
	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}







