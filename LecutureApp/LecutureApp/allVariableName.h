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
extern int main;
extern int start;
extern int click;

/*�摜�t�@�C���������p�z��*/
extern int skillBox;			//�킴���j���[
extern int stairs_down;			//����K�i
extern int stairs_up;			//���K�i
extern int load;				//1�K�̓�
extern int load2;				//2�K�̓�
extern int messageBox;			//���̃��b�Z�[�W�{�b�N�X
extern int ball[2];
extern int tempTime;
extern int bl;
extern int title[2];
extern int over[3];

/*�R���\�[���\���p�ϐ�*/
extern char message1[256];		//���b�Z�[�W�{�b�N�X���̏�i
extern char message2[256];		//���i
extern char message3[256];		//���i
extern char s[256];				//sprintf_s�p�̔z��

/*�|�P�����\����*/
extern pokemon* b;								//�{�X���i�[����
extern pokemon* enemy[FLOORNUM - 1][ENEMYNUM];	//�G���i�[����

extern pokemon* c;								//�|�P������l���|�C���^
extern pokemon* z[3];
extern maps* m;									//�}�b�v�\���̃|�C���^

extern char keyState[256];						//������Ă���L�[���i�[����z��


extern bool messageflag;						//���b�Z�[�W��\�����邩

extern bool menuflag;

extern bool endflag;