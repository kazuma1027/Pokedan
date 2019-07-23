#include "all.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <map>
#include <stack>
#include <stdio.h>
#include "Enemy.cpp"
#include "Character.cpp"
#include "Map.cpp"
#include "Generic.cpp"


/*�֐��v���g�^�C�v�錾*/
/********************************Generic.cpp************************************/
int init();										//������
int getRandom(int,int);							//int max�`int min�͈̔͂ŗ������擾
void wait(int);									//int���ԑ҂�
void wait(int,char* s);							//int���ԑ҂A���S�ɕ����\��
void w_press();									//K�{�^����������i
void setDirection(pokemon*, int);						//�L�����̌����Ă���������Z�b�g����
void skillfull(int experience);					//�Z�З͐ݒ�
void drawCharacter(pokemon*,int d_num);
bool isPutMoveKey();


/*********************************Character.cpp**********************************/
void attack(pokemon*, pokemon*);			//�U������
void attack_for(pokemon* me);	//�v���C���[�p�U��
void turnToPokemon(pokemon*, pokemon*);			//�|�P�����̕�������
void moveJump(pokemon*);						//Jump����
void charaMove(pokemon*,pokemon*[ENEMYNUM],maps*,char[256], int, int);		//�L�����ړ��A�����p�@����ւ��l��
pokemon* getFrontEnemy();


/*********************************Enemy.cpp**************************************/
void enemyMove(pokemon*);					//�G�̓���
bool isNearPokemon(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool isNearPokemon2(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool findPokemon(pokemon*, pokemon*);			//�G�������ł���߂��ɂ�����
bool life(pokemon* enemy, pokemon* me);			//�G����ł��邩�ǂ���
void randomEnemyPut(pokemon*[ENEMYNUM]);
void sortEnemy();
//A*�A���S���Y���G�ǔ�
int h(NODE*, NODE*);		//�q���[���X�e�B�b�N�֐��l��Ԃ��A�}���n�b�^������
void setNode(NODE* child, int x, int y, NODE* parent, int cost, int f);		//�m�[�h�̏�����C�ɐݒ肷��
int getCost();				//�ړ��R�X�g��Ԃ��A���̏ꍇ��1��Ԃ�
NODE* Astar(pokemon*);			//A*�A���S���Y���K�p��A���ɐi�ރZ���̃m�[�h��Ԃ�
void charaMove(pokemon*, int, int);				//�L�����ړ��A�G�p
bool isNearEnemy(pokemon*,int ,int);


/*********************************Message.cpp************************************/
void initConsole();								//���b�Z�[�W�{�b�N�X������������
void setMessage(char[]);						//�\�����������b�Z�[�W���Z�b�g����
void outMessage();								//���b�Z�[�W��\������
void initMessage();


/**********************************Map.cpp**************************************/
void mapMove(maps*,pokemon*,pokemon*[ENEMYNUM], int, int);	//�}�b�v�ړ��A�����|����l��
void drawMap();
void drawMiniMap();

/**********************************Menu.cpp*************************************/
void drawMenu();

/*�U�����鑊���Ԃ�*/

/*�L�[��������Ă���t���[�����ɂ���ĕ\������摜��ύX����*/
/*
int getDnum(int key) {
	if (keyState[key] % 60 >= 1 && keyState[key] % 60 < 30) return 0;
	else return 1;
}
*/



/*
void Screen() {
	while () {
		sprintf_s(s, "�悤�����|�P�����̐��E��");

		messageflag = true;
		setMessage(s);
		outMessage();
	}
}*/



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
			charaMove(c,enemy[m->floor],m,keyState,1,0);
		}
		/*Left*/
		else if (!menuflag && keyState[KEY_INPUT_A]==1) { 
			charaMove(c,enemy[m->floor],m,keyState, -1, 0);
		}
		/*Up*/
		else if (!menuflag && keyState[KEY_INPUT_W]==1) {
			charaMove(c,enemy[m->floor],m,keyState, 0, -1);
		}
		/*Down*/
		else if (!menuflag && keyState[KEY_INPUT_X]==1) {
			charaMove(c,enemy[m->floor],m,keyState, 0, 1);
		}
		/*RightUp*/
		else if (!menuflag && keyState[KEY_INPUT_E] == 1) {
			charaMove(c, enemy[m->floor],m,keyState, 1, -1);
		}
		/*RightDown*/
		else if (!menuflag && keyState[KEY_INPUT_C] == 1) {
			charaMove(c, enemy[m->floor],m,keyState, 1, 1);
		}
		/*LeftUp*/
		else if (!menuflag && keyState[KEY_INPUT_Q] == 1) {
			charaMove(c, enemy[m->floor],m,keyState, -1, -1);
		}
		/*LeftDown*/
		else if (!menuflag && keyState[KEY_INPUT_Z] == 1) {
			charaMove(c, enemy[m->floor],m,keyState, -1, 1);
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
					charaMove(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
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
				
				charaMove(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
				//�ړ���A�O�A�E�A���̂ǂ��炩�ɂ����Ƃ�
				if (isNearPokemon(enemy[m->floor][i], c) && (GX + (m->x - tmp_mx) != SX(enemy[m->floor][i]) && GY + (m->y - tmp_my) != SY(enemy[m->floor][i]))) {
					turnToPokemon(enemy[m->floor][i], c);
					attack(enemy[m->floor][i], c);
				}
				//�ȂȂ߂ɂ���Ƃ�
				else if (!isNearPokemon(enemy[m->floor][i],c) && isNearPokemon2(enemy[m->floor][i], c)) {
					charaMove(enemy[m->floor][i], (c->x - enemy[m->floor][i]->x) / CHIP_SIZE, (c->y - enemy[m->floor][i]->y) / CHIP_SIZE);
				}
				//8���ɂ���Ƃ�
				else if (isNearPokemon(enemy[m->floor][i], c)) {
					turnToPokemon(enemy[m->floor][i], c);
				}
				
				else {
					NODE* n = Astar(enemy[m->floor][i]);
					if (n != NULL)charaMove(enemy[m->floor][i], n->x - SX(enemy[m->floor][i]), n->y - SY(enemy[m->floor][i]));
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







