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
		/*bgm�Đ��J�n*/
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

		/*�`�悷��*/
		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

			tmp_mx = m->x;
			tmp_my = m->y;

			//�}�b�v�`��
			drawMap();
			//�~�j�}�b�v�`��
			drawMiniMap();

			/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
			if (GetNowCount() - tempTime > 500)
			{
				if (d_num == 1)d_num = 0;
				else d_num = 1;
				tempTime = GetNowCount();
			}

			/*�K�w�Alevel�AHP�\��(�Œ�)*/
			DrawFormatString(0, 0, WHITE, "B%dF", m->floor + 1);
			DrawFormatString(50, 0, WHITE, "Lv: %d", c->level);
			DrawFormatString(120, 0, WHITE, "HP: %d/ %d", c->hp, c->maxHp);
			DrawFormatString(360, 0, WHITE, "�Z�b�g�킴�� : %s", c->skill[c->attackNum].name);
			DrawFormatString(600, 0, WHITE, "�}�b�v(%d,%d)", m->x, m->y);
			DrawFormatString(600, 20, WHITE, " �s�J�`���E(%d,%d)", GX * CHIP_SIZE ,GY*CHIP_SIZE);
			for (int i = 0; i < ENEMYNUM; i++) {
				if (enemy[m->floor][i]->name == "�~���E�c�[") { DrawFormatString(600, 40, WHITE, " �~���E�c�[(%d,%d)", SX(enemy[m->floor][i])*CHIP_SIZE, SY(enemy[m->floor][i]) * CHIP_SIZE); }
			}
			
			if (c->hp <= c->maxHp / 3) { hpColor = RED; }
			else if (c->hp <= c->maxHp / 2) { hpColor = YELLOW; }
			else { hpColor = GREEN; }
			DrawBox(230, 1, c->maxHp + 230, 15, BLACK, true);
			DrawBox(230, 1, c->hp + 230, 15, hpColor, true);
			DrawBox(230, 0, c->maxHp + 231, 16, WHITE, false);
			
			

			drawCharacter(c, d_num);

			for (int i = 0; i < ENEMYNUM; i++) {
				drawCharacter(enemy[m->floor][i], d_num);
			}

			/*���b�Z�[�W�o��*/
			outMessage();

			if (m->floor == 2) {
				pokemon* tmp = new pokemon;
				for (int i = 0; i < ENEMYNUM; i++) {
					if (enemy[m->floor][i]->name=="�~���E�c�[") { tmp = enemy[m->floor][i]; break; }
				}
				//�{�X�����񂾂�
				if (!tmp->isLive) { clear = true; break; }
			}

			//���������񂾂�
			if (c->hp == 0) { over = true; break; }

			/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
			showMenu();

			/*��l���̓����A�ړ���U���A�K�i�ړ�*/
			mainCharaMove();

			/*�G�̓����A�ړ���U��*/
			mainEnemyMove(tmp_mx, tmp_my);

			/*space�L�[�ŏI���*/
			if (keyState[KEY_INPUT_SPACE] == 1) { endflag = true; break; }

			/*���܂��̃W�����v����*/
			//if (!jump && keyState[KEY_INPUT_SPACE] == 1) { 
			//	y_prev = c->y; temp = c->y;
			//	jump = true;  onGround = true;
			//}

			/*�W�����v�����{��*/
			//if (jump) {
				//moveJump(c);
			//}

		}

		if (endflag)break;
		else if (over)gameover();
		else if(clear)gameClear();
		if (endflag)break;
	}
	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}







