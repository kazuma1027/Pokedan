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
	
	prologue();

	SetFontSize(16);
	SetFontThickness(4);

	/*bgm�Đ��J�n*/
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	pokemon* tmp = new pokemon;

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

		DrawFormatString(500, 0, WHITE, "1(%d,%d)", SX(enemy[m->floor][0]),SY(enemy[m->floor][0]));
		DrawFormatString(500, 20, WHITE, "2(%d,%d)", SX(enemy[m->floor][1]),SY(enemy[m->floor][1]));
		DrawFormatString(500, 40, WHITE, "3(%d,%d)", SX(enemy[m->floor][2]),SY(enemy[m->floor][2]));

		drawCharacter(c, d_num);
		
		for (int i = 0; i < ENEMYNUM; i++) {
			drawCharacter(enemy[m->floor][i], d_num);
		}

		/*���b�Z�[�W�o��*/
		outMessage();

		/*i�������ƃ��j���[�\���A�ēx�������Z��I�ԂƏ���*/
		showMenu();
		
		/*��l���̓����A�ړ���U���A�K�i�ړ�*/
		mainCharaMove();

		/*�G�̓����A�ړ���U��*/
		mainEnemyMove(tmp_mx,tmp_my);

		if (c->hp == 0)gameover();

		/*space�L�[�ŏI���*/
		if (keyState[KEY_INPUT_SPACE] == 1) { endflag = true; }

		if (endflag)break;

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







