#pragma once
#include "allVariableName.h"
#include <stdio.h>
#include "Map.h"
#include "Enemy.h"
#include "Generic.h"
#include "Message.h"
#include "mapping.h"

#define GX (c->x/CHIP_SIZE - m->x)
#define GY (c->y/CHIP_SIZE - m->y)


/*�W�����v�p�ϐ�*/
int temp = 0;
int y_temp = 0;
int y_prev = 0;

/*�W�����v�p�t���O*/
bool onGround = false;		//�W�����v����u��
bool jump = false;			//�W�����v���Ă��邩�ǂ���	

pokemon poke;
pokemon* c = &poke;


//�������Z�b�g
void setDirection(pokemon* me, int direction) {
	me->direction = direction;
}

/*�����p�̏���*/
void charaMove(pokemon* me, pokemon* enemy[ENEMYNUM], int x, int y) {

	//�����Ă���������Z�b�g
	if (x == 1)setDirection(me, RIGHT);
	else if (x == -1)setDirection(me, LEFT);

	if (y == 1)setDirection(me, DOWN);
	else if (y == -1)setDirection(me, UP);

	//�}�b�v�ړ��p
	int mx = 0;
	int my = 0;

	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[m->floor][GY + y][GX + x];

	/*�ȂȂ߈ړ��̂Ƃ�*/
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {

		int nextCell_x = mapping[m->floor][GY][GX + x];	//�����̍��E�ǂ��炩�̃Z���̏��
		int nextCell_y = mapping[m->floor][GY + y][GX];	//�����̏㉺�ǂ��炩�̃Z���̏��

														//�i�ސ悪��Q���ŁA���E�ǂ��炩�A�㉺�ǂ��炩�����ł���Ί���
		if (nextCell <= 0 && !keyState[KEY_INPUT_Y]) {
			if (nextCell_x > 0 && nextCell_y <= 0)y = 0;
			if (nextCell_y > 0 && nextCell_x <= 0)x = 0;
		}
	}

	//�}�b�v�̒[�ł���΃}�b�v�ړ�
	if (me->x == CHIP_SIZE * 2 && x == -1 || me->x == MAP_WIDTH && x == 1) {
		mx = x * -1;
		x = 0;
	}
	if (me->y == CHIP_SIZE * 2 && y == -1 || me->y == MAP_HEIGHT && y == 1) {
		my = y * -1;
		y = 0;
	}

	//nextCell�̍X�V
	nextCell = mapping[m->floor][GY + y][GX + x];

	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		/*�ړ���ɓG�����������ւ��*/
		for (int i = 0; i < ENEMYNUM; i++) {
			if (me->x / CHIP_SIZE + x == enemy[i]->x / CHIP_SIZE && me->y / CHIP_SIZE + y == enemy[i]->y / CHIP_SIZE) charaMoveEnemy(enemy[i], x*(-1), y*(-1));
		}
		me->x += x * CHIP_SIZE;
		me->y += y * CHIP_SIZE;
		for (int i = 0; i < ENEMYNUM; i++) {
			if (me->x / CHIP_SIZE == enemy[i]->x / CHIP_SIZE && me->y / CHIP_SIZE == enemy[i]->y / CHIP_SIZE) charaMoveEnemy(enemy[i], x * (-1), y * (-1));
		}
	}

	//�}�b�v�ړ��������
	if (!(mx == 0 && my == 0)) {
		mapMove(m, me, enemy, mx, my);
	}
}


/*attack(����,�G,�U���̎��)*/
void attack(pokemon* me, pokemon* enemy) {

	//turnToPokemon(me, enemy);//�G�̕�������
	int value = getRandom(me->skill[me->attackNum].min, me->skill[me->attackNum].max);	//�킴���o�����тɗ�������
	if (me->skill[me->attackNum].count > 0) {
		//�G�̕��������Ă���ꍇ
		if (enemy->isLive && isNearPokemon(me, enemy) && ((me->y == enemy->y && ((me->x > enemy->x && me->direction == LEFT) || (me->x < enemy->x && me->direction == RIGHT))) || (me->x == enemy->x && ((me->y > enemy->y && me->direction == UP || me->y<enemy->y && me->direction == DOWN))))) {
			/*2%�̊m���ōU�����O���*/
			if (getRandom(1, 100) < 98) {
				enemy->hp -= value;
				if (enemy->hp < 0)enemy->hp = 0;//hp���}�C�i�X�ɂȂ�̂�h��
				sprintf_s(s, "%s��%s! %s��%d�̃_���[�W!%s��HP:%d", me->name, me->skill[me->attackNum].name, enemy->name, value, enemy->name, enemy->hp);
				PlaySoundMem(slap, DX_PLAYTYPE_BACK);
			}
			else {
				sprintf_s(s, "%s��%s!�������U���͊O�ꂽ", me->name, me->skill[me->attackNum].name);
				PlaySoundMem(slap, DX_PLAYTYPE_BACK);
			}
		}//�G�̕��������Ă��Ȃ��ꍇ
		else {
			/*�U�����O���*/
			sprintf_s(s, "%s��%s!�������U���͊O�ꂽ", me->name, me->skill[me->attackNum].name);
			PlaySoundMem(slap, DX_PLAYTYPE_BACK);
		}
	}
	else {
		sprintf_s(s, "%s�͂����g���Ȃ�!", me->skill[me->attackNum].name);
	}
	me->skill[me->attackNum].count -= 1;
	if (me->skill[me->attackNum].count < 0)me->skill[me->attackNum].count = 0;	//�}�C�i�X��h��
	messageflag = true;
	setMessage(s);
	outMessage();

}

//�v���C���[�U���p,�G������ɂ��炸�U�����K���O���ꍇ
void attack_for(pokemon* me) {

	if (me->skill[me->attackNum].count > 0) {

		/*�U�����O���*/
		sprintf_s(s, "%s��%s!�������U���͊O�ꂽ", me->name, me->skill[me->attackNum].name);
		PlaySoundMem(slap, DX_PLAYTYPE_BACK);
	}
	else {
		sprintf_s(s, "%s�͂����g���Ȃ�!", me->skill[me->attackNum].name);
	}
	me->skill[me->attackNum].count -= 1;
	if (me->skill[me->attackNum].count < 0)me->skill[me->attackNum].count = 0;	//�}�C�i�X��h��
	messageflag = true;
	setMessage(s);
	outMessage();
}


/*�W�����v����*/
void moveJump(pokemon* me) {

	int f;
	/*�W�����v�����u��*/
	if (onGround) {
		/*��ւ̓����蔻��*/
		if (me->y >= 140) {
			f = -30;
			y_temp = me->y;
			me->y += (me->y - y_prev) + f;
			y_prev = y_temp;
		}
		else {
			y_temp = 30;
			me->y = 30;
			y_prev = y_temp;
		}
	}
	/*�󒆂̏���*/
	else {
		f = 3;
		y_temp = me->y;
		me->y += (me->y - y_prev) + f;
		y_prev = y_temp;
		/*���̈ʒu�ɖ߂�΃W�����v�����I��*/
		if (me->y >= temp) {
			me->y = temp;
			jump = false;
		}
	}
	onGround = false;
}


pokemon* getFrontEnemy() {

	for (int i = 0; i < ENEMYNUM; i++) {

		if (c->direction == UP) {
			if (c->x == enemy[m->floor][i]->x && c->y - CHIP_SIZE == enemy[m->floor][i]->y) {
				if (enemy[m->floor][i]->isLive) {
					return enemy[m->floor][i];
				}
			}
		}
		else if (c->direction == RIGHT) {
			if (c->y == enemy[m->floor][i]->y && c->x + CHIP_SIZE == enemy[m->floor][i]->x) {
				if (enemy[m->floor][i]->isLive) {
					return enemy[m->floor][i];
				}
			}
		}
		else if (c->direction == DOWN) {
			if (c->x == enemy[m->floor][i]->x && c->y + CHIP_SIZE == enemy[m->floor][i]->y) {
				if (enemy[m->floor][i]->isLive) {
					return enemy[m->floor][i];
				}
			}
		}
		else if (c->direction == LEFT) {
			if (c->y == enemy[m->floor][i]->y && c->x - CHIP_SIZE == enemy[m->floor][i]->x) {
				if (enemy[m->floor][i]->isLive) {
					return enemy[m->floor][i];
				}
			}
		}
	}
	return NULL;
}