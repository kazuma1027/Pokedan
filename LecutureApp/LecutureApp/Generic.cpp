#pragma once
#include <random>
#include "Enemy.h"
#include "Character.h"
#include "allVariableName.h"
#include "Message.h"


double skillTable[17][17] = {
	//�m	//�ق�	//�݂�	//�ł�	//����	//����	//����	//�ǂ��@//����	//�Ђ�	//�G�X	//�ނ�	//����	//�S�[	//�h��	//����	//�͂���
	{1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		0.5,	0,		1,		1,		0.5},	//�m�[�}��
	{1,		0.5,	0.5,	1,		2,		2,		1,		1,		1,		1,		1,		2,		0.5,	1,		0.5,	1,		2},		//�ق̂�
	{1,		2,		0.5,	1,		0.5,	1,		1,		1,		2,		1,		1,		1,		2,		1,		0.5,	1,		1},		//�݂�
	{1,		1,		2,		0.5,	0.5,	1,		1,		1,		0,		2,		1,		1,		1,		1,		0.5,	1,		1},		//�ł�
	{1,		0.5,	2,		1,		0.5,	1,		1,		0.5,	2,		0.5,	1,		0.5,	2,		1,		0.5,	1,		0.5},	//��
	{1,		0.5,	0.5,	1,		2,		0.5,	1,		1,		2,		2,		1,		1,		1,		1,		2,		1,		0.5},	//������
	{2,		1,		1,		1,		1,		2,		1,		0.5,	1,		0.5,	0.5,	0.5,	2,		0,		1,		2,		2},		//�����Ƃ�
	{1,		1,		1,		1,		2,		1,		1,		0.5,	0.5,	1,		1,		1,		0.5,	0.5,	1,		1,		0},		//�ǂ�
	{1,		2,		1,		2,		0.5,	1,		1,		2,		1,		0,		1,		0.5,	2,		1,		1,		1,		2},		//���߂�
	{1,		1,		1,		0.5,	2,		1,		2,		1,		1,		1,		1,		2,		0.5,	1,		1,		1,		0.5},	//�Ђ���
	{1,		1,		1,		1,		1,		1,		2,		2,		1,		1,		0.5,	1,		1,		1,		1,		0,		0.5},	//�G�X�p�[
	{1,		0.5,	1,		1,		2,		1,		0.5,	0.5,	1,		0.5,	2,		1,		1,		0.5,	1,		2,		1},		//�ނ�
	{1,		2,		1,		1,		1,		2,		0.5,	1,		0.5,	2,		1,		2,		1,		1,		1,		1,		0.5},	//����
	{0,		1,		1,		1,		1,		1,		1,		1,		1,		1,		2,		1,		1,		2,		1,		0.5,	1},		//�S�[�X�g
	{1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		2,		1,		0.5},	//�h���S��
	{1,		1,		1,		1,		1,		1,		0.5,	1,		1,		1,		2,		1,		1,		2,		1,		0.5,	1},		//����
	{1,		0.5,	0.5,	0.5,	1,		2,		1,		1,		1,		1,		1,		1,		2,		1,		1,		1,		0.5}	//�͂���
};

char keyState[256];

int miniMapFlag[FLOORNUM][MAP_YNUM][MAP_XNUM];

/*�v���g�^�C�v�錾*/
void wait_key(int);
int getCountFrame();
void wait(int ms, char* s);
void wait(int ms);
int getRandom(int min, int max);
bool isPutMoveKey();
void levelUp(int level);
double skillCalc(int, int);

void wait_key(int key) {
	while (getCountFrame() == 0) {
		if (keyState[key] == 1) {
			break;
		}
	}
}

//�Z�З͐ݒ�
void levelUp(int level) {
	
	

	c->baseAttack = ba + level;
	
	for (int i = 0; i < 4; i++) {
		c->skill[i].count = c->skill[i].maxCount;
	}

	/*�̗͉�*/
	c->maxHp += 5;
	c->hp = c->maxHp;
}


/*�L�[��������Ă���t���[�����𐔂���*/
int getCountFrame() {
	char tmpKey[256];								// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);						// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {						// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			keyState[i]++;							// ���Z
			if (keyState[i] == 60)keyState[i] = 2;	//�ړ����̉摜�����Ɏg�p
		}
		else {										// ������Ă��Ȃ����
			keyState[i] = 0;						// 0�ɂ���
		}
	}
	return 0;
}

void wait(int ms, char* s) {
	int tmp = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetNowCount() - tmp < ms) {
		DrawFormatString(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, GetColor(255, 255, 255), "%s", s);
	}
}

void wait(int ms) {
	int tmp = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && GetNowCount() - tmp < ms) {

	}
}

/*0�`3�̗����𓾂�*/
int getRandom(int min, int max) {

	std::random_device rd;

	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dice(min, max);

	return dice(mt);
}


bool isPutMoveKey() {

	if (keyState[KEY_INPUT_Q] == 1 || keyState[KEY_INPUT_W] == 1 || keyState[KEY_INPUT_E] == 1 || keyState[KEY_INPUT_D] == 1 || keyState[KEY_INPUT_C] == 1 || keyState[KEY_INPUT_X] == 1 || keyState[KEY_INPUT_Z] == 1 || keyState[KEY_INPUT_A] == 1) {
		return true;
	}
	else {
		return false;
	}

}


//�G������ł��邩����
bool life(pokemon* enemy, pokemon* me) {
	int ex = 0;
	/*�����Ă��邩����ł��邩*/
	/*���S�m�F*/
	if (enemy->hp == 0 && enemy->isLive) {
		PlaySoundMem(down, DX_PLAYTYPE_BACK);
		PlaySoundMem(enemy->voice, DX_PLAYTYPE_BACK);
		c->experience += enemy->experience;
		sprintf_s(s, 256, "%s�͓|�ꂽ! �o���l%d���l��!", enemy->name, enemy->experience);
		setMessage(s);
		outMessage();
		wait(400);
		while (me->Max_ex < enemy->experience && ScreenFlip()==0) {

			enemy->experience = enemy->experience - me->Max_ex;
			me->level++;
			me->Max_ex += 30;
			PlaySoundMem(levelUP, DX_PLAYTYPE_NORMAL);
			sprintf_s(s, "%s�̓��x��%d�ɂȂ����I", me->name, me->level);
			setMessage(s);
			outMessage();
			wait(100);
			levelUp(me->level);

		}
		enemy->isLive = false;
		return TRUE;
	}
	return FALSE;
}

double skillCalc(int skillType, int enemyType) {
	return skillTable[skillType][enemyType];
}