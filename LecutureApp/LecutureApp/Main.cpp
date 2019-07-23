#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include "allVariableName.h"
#include "allMethod.h"

/***********************      Main�̏���      *********************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	/*����������*/
	if (init() == -1) { return -1; }

	int d_num = 0;
	int tempTime = 0;

	m->floor = 0;
	int tmp_mx = m->x;
	int tmp_my = m->y;
	
	int distance = 0;

	/*bgm�Đ��J�n*/
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	pokemon* tmp = new pokemon;

	/*�`�悷��*/
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

		tmp_mx = m->x;
		tmp_my = m->y;

		drawMap();
		drawMiniMap();

		/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
		if (GetNowCount() - tempTime> 500) 
		{	
			if (d_num == 1)d_num = 0;
			else d_num = 1;
			tempTime = GetNowCount(); 
		}

		/*�K�w�Alevel�AHP�\��(�Œ�)*/
		DrawFormatString(0	, 0, WHITE, "B%dF",m->floor + 1);
		DrawFormatString(50	, 0, WHITE, "Lv: %d",c->level);
		DrawFormatString(120, 0, WHITE, "HP: %d/ %d",c->hp,c->maxHp);
		DrawFormatString(220, 0, WHITE, "�Z�b�g�킴�� : %s",c->skill[c->attackNum].name);

		DrawFormatString(500, 0, WHITE, "1(%d,%d)", enemy[m->floor][0]->x,enemy[m->floor][0]->y);
		DrawFormatString(500, 20, WHITE, "2(%d,%d)", enemy[m->floor][1]->x,enemy[m->floor][1]->y);
		DrawFormatString(500, 40, WHITE, "3(%d,%d)",enemy[m->floor][2]->x,enemy[m->floor][2]->y);

		drawCharacter(c, d_num);
		
		for (int i = 0; i < ENEMYNUM; i++) {
			drawCharacter(enemy[m->floor][i], d_num);
		}

		/*���b�Z�[�W�o��*/
		outMessage();

		/*space�L�[�ŏI���*/
		if (keyState[KEY_INPUT_SPACE] == 1) { break; }
		
		/*�킴�\������*/
		if (menuflag && keyState[KEY_INPUT_I] == 1) {
			menuflag = false;
		}

		/*�킴�\��\��*/
		else if (!menuflag && keyState[KEY_INPUT_I] == 1) {
			menuflag = true;
		}

		if (menuflag) {
			drawMenu();
		}
		
		/*Attack*/
		if (!menuflag && keyState[KEY_INPUT_J] == 1) {

			tmp = getFrontEnemy();
			if (tmp != NULL)attack(c, tmp);
			else attack_for(c);

			for (int i = 0; i < ENEMYNUM; i++) {
				if (life(enemy[m->floor][i], c) == FALSE) {
					enemyMove(enemy[m->floor][i]);
				}
			}
		}
		/*Right*/
		if (!menuflag && keyState[KEY_INPUT_D]==1) {
			charaMove(c,enemy[m->floor],1,0);
		}
		/*Left*/
		else if (!menuflag && keyState[KEY_INPUT_A]==1) { 
			charaMove(c,enemy[m->floor],-1, 0);
		}
		/*Up*/
		else if (!menuflag && keyState[KEY_INPUT_W]==1) {
			charaMove(c,enemy[m->floor], 0, -1);
		}
		/*Down*/
		else if (!menuflag && keyState[KEY_INPUT_X]==1) {
			charaMove(c,enemy[m->floor], 0, 1);
		}
		/*RightUp*/
		else if (!menuflag && keyState[KEY_INPUT_E] == 1) {
			charaMove(c, enemy[m->floor], 1, -1);
		}
		/*RightDown*/
		else if (!menuflag && keyState[KEY_INPUT_C] == 1) {
			charaMove(c, enemy[m->floor], 1, 1);
		}
		/*LeftUp*/
		else if (!menuflag && keyState[KEY_INPUT_Q] == 1) {
			charaMove(c, enemy[m->floor], -1, -1);
		}
		/*LeftDown*/
		else if (!menuflag && keyState[KEY_INPUT_Z] == 1) {
			charaMove(c, enemy[m->floor], -1, 1);
		}

		
		if (!menuflag && isPutMoveKey() && tmp_mx == m->x && tmp_my == m->y) {
			if (keyState[KEY_INPUT_Y] == 0) {
				sortEnemy();
				
				for (int i = 0; i < ENEMYNUM; i++) {
					enemyMove(enemy[m->floor][i]);
				}
			}
		}
		/*�}�b�v�ړ���*/
		else if (!menuflag && isPutMoveKey() && (tmp_mx != m->x || tmp_my != m->y)) {
			
			sortEnemy();

			tmp = NULL;
			
			//����ւ�菈����D�悳����
			for (int i = 0; i < ENEMYNUM; i++) {
				if (GX == SX(enemy[m->floor][i]) + (m->x - tmp_mx) && GY == SY(enemy[m->floor][i]) + (m->y - tmp_my) ) {
					charaMoveEnemy(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
					enemy[m->floor][i]->x += (m->x - tmp_mx) * CHIP_SIZE; enemy[m->floor][i]->y += (m->y - tmp_my)*CHIP_SIZE;
					turnToPokemon(enemy[m->floor][i], c);
					attack(enemy[m->floor][i], c);
					tmp = enemy[m->floor][i];
				}
			}
			for (int i = 0; i < ENEMYNUM; i++) {
				if (tmp == enemy[m->floor][i])continue;
				if (isNearEnemy(enemy[m->floor][i], 0, 0)) {
					enemy[m->floor][i]->x += (m->x - tmp_mx) * CHIP_SIZE; enemy[m->floor][i]->y += (m->y - tmp_my) * CHIP_SIZE;
				}
			}
			
			for (int i = 0; i < ENEMYNUM; i++) {
				if (tmp == enemy[m->floor][i])continue;
				
				charaMoveEnemy(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
				//�ړ���A�O�A�E�A���̂ǂ��炩�ɂ����Ƃ�
				if (isNearPokemon(enemy[m->floor][i], c) && (GX + (m->x - tmp_mx) != SX(enemy[m->floor][i]) && GY + (m->y - tmp_my) != SY(enemy[m->floor][i]))) {
					turnToPokemon(enemy[m->floor][i], c);
					attack(enemy[m->floor][i], c);
				}
				//�ȂȂ߂ɂ���Ƃ�
				else if (!isNearPokemon(enemy[m->floor][i],c) && isNearPokemon2(enemy[m->floor][i], c)) {
					charaMoveEnemy(enemy[m->floor][i], (c->x - enemy[m->floor][i]->x) / CHIP_SIZE, (c->y - enemy[m->floor][i]->y) / CHIP_SIZE);
				}
				//8���ɂ���Ƃ�
				else if (isNearPokemon(enemy[m->floor][i], c)) {
					turnToPokemon(enemy[m->floor][i], c);
				}
				
				else {
					NODE* n = Astar(enemy[m->floor][i]);
					if (n != NULL)charaMoveEnemy(enemy[m->floor][i], n->x - SX(enemy[m->floor][i]), n->y - SY(enemy[m->floor][i]));
				}
				
			}
		}


		/*�K�i�ړ�����*/
		if (mapping[m->floor][GY][GX] == 100) {
			stairsMove(1);
		}

		if (mapping[m->floor][GY][GX] == 101) {
			stairsMove(-1);
		}

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

	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}







