#pragma once
#include "all.h"

#define GX (c->x/CHIP_SIZE - m->x)
#define GY (c->y/CHIP_SIZE - m->y)
#define SX(a) (a->x/CHIP_SIZE - m->x)
#define SY(a) (a->y/CHIP_SIZE - m->y)

/*�����t�@�C���������p�z��*/
extern int slap;
extern int bgm;
extern int down;

/*�摜�t�@�C���������p�z��*/
extern int skillBox;
extern int stairs_down;
extern int stairs_up;
extern int load;
extern int load2;

/*�R���\�[���\���p�ϐ�*/
extern char message1[256];
extern char message2[256];
extern char message3[256];
extern char s[256];				//sprintf_s�p�̔z��

/*�|�P�����\����*/
extern pokemon* b;
extern pokemon* enemy[FLOORNUM - 1][ENEMYNUM];

extern pokemon* c;

extern int messageBox;

extern bool messageflag;	//���b�Z�[�W��\�����邩

extern bool menuflag;

extern maps* m;

extern char keyState[256];			//������Ă���L�[���i�[
