#include "all.h"
#include "allVariableName.h"
#include "Generic.h"
#include "Enemy.h"
#include "FileIO.h"
#include "Message.h"

/*�����t�@�C���������p�z��*/
int slap;
int bgm;
int down;
int main;
int click;
int boss_bgm;
int startSound;
int levelUP;

/*�摜�t�@�C���������p�z��*/
int skillBox;
int stairs_down;
int stairs_up;
int load;
int load2;
int load3;
int ball[2];
int tempTime = 0;
int bl;
int title[2];
int over[3];

int init();
void charaInit();
void nameSet(pokemon*, char*);
void charaSet(pokemon*);

int init() {
	/*�E�C���h�E�̑傫���w��*/
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
	/*�w�i�F�`��(��Ƀ}�b�v)*/
	SetBackgroundColor(20, 20, 20);
	/*�E�B���h�E���[�h�Ɏw��*/
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0) { return -1; }	// DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);			//�`���𗠉�ʂɐݒ�
	SetUseDirectDrawFlag(FALSE);			//�������y�����邽�߂Ɏg�p
	SetWaitVSyncFlag(FALSE);

	m->floor = 0;

	nameSet(z[0], MAINCHARANAME1);
	nameSet(z[1], MAINCHARANAME2);
	nameSet(z[2],MAINCHARANAME3);
	

	for (int i = 0; i < 3; i++) {
		charaSet(z[i]);
	}


	/*�K�i�̉摜*/
	stairs_down = LoadGraph("�摜/stairs.png");
	stairs_up = LoadGraph("�摜/stairs2.png");

	/*�摜�̃��[�h*/
	SetTransColor(255, 255, 255);
	ball[0] = LoadGraph("�摜/�����X�^�[�{�[��.png");
	title[0] = LoadGraph("�摜/back.png");
	title[1] = LoadGraph("�摜/title2.png");

	over[0] = LoadGraph("�摜/over.png");
	bl = LoadGraph("�摜/black.png");

	/*���F�̓���*/
	SetTransColor(255, 255, 255);
	/*���b�Z�[�W�{�b�N�X*/
	messageBox = LoadGraph("�摜/messageBox.png");
	SetTransColor(255, 0, 0);
	/*�킴�I���{�b�N�X*/
	skillBox = LoadGraph("�摜/skillBox.png");

	load  = LoadGraph("�摜/load.png");
	load2 = LoadGraph("�摜/load2.png");
	load3 = LoadGraph("�摜/load3.png");

	/*���������[�h*/
	slap = LoadSoundMem("���y/slap1.mp3");
	bgm = LoadSoundMem("���y/bgm.mp3");
	down = LoadSoundMem("���y/down1.mp3");
	boss_bgm = LoadSoundMem("���y/bossBGM.mp3");
	main = LoadSoundMem("���y/main.mp3");
	startSound = LoadSoundMem("���y/start.mp3");
	levelUP = LoadSoundMem("���y/���x���A�b�v.mp3");

	return 0;
}

void charaInit() {
	
	/*�}�b�v������*/
	m->floor = 0;
	m->x = 0;
	m->y = 0;

	enemy[0][0]->name = ENEMYNAME1;
	enemy[0][1]->name =	ENEMYNAME2;
	enemy[0][2]->name = ENEMYNAME3;
	enemy[1][0]->name = ENEMYNAME4;
	enemy[1][1]->name = ENEMYNAME5;
	enemy[1][2]->name = ENEMYNAME6;
	
	lastboss->name = BOSSNAME;

	if (continueflag) {
		if (readData() == -1) {
			setMessage("�f�[�^��ǂݍ��߂܂���ł���");
			outMessage();
			ScreenFlip();
		}
	}
	else {
		charaSet(c);
		//��l���͌o���l0����n�߂�
		c->experience = 0;
		/*�������W�ʒu*/
		c->x = CHIP_SIZE * 3;
		c->y = CHIP_SIZE * 3;
		for (int i = 0; i < FLOORNUM - 1; i++) {
			for (int j = 0; j < ENEMYNUM; j++) {
				charaSet(enemy[i][j]);
			}
		}
		charaSet(lastboss);
		for (int i = 0; i < FLOORNUM; i++) {
			for (int j = 0; j < MAP_YNUM; j++) {
				for (int k = 0; k < MAP_XNUM; k++) {
					miniMapFlag[i][j][k] = 0;
				}
			}
		}
	}

	if (!continueflag) {
		randomEnemyPut(enemy[m->floor]);
	}
}

void nameSet(pokemon* me,char* s) {
	me->name = s;
}

void charaSet(pokemon* me) {
	char* dir[4] = { "d_","u_","l_","r_" };
	for (int i = 0; i < 4; i++) {
		sprintf_s(s, 256, "�摜/%s/%s%s1.png", me->name,me->name,dir[i]);
		me->moveTexture[i][0] = LoadGraph(s);
		sprintf_s(s, 256, "�摜/%s/%s%s2.png", me->name,me->name, dir[i]);
		me->moveTexture[i][1] = LoadGraph(s);
	}
	sprintf_s(s, 256, "���y/%svoice.mp3",me->name);
	me->level = 1;
	me->Max_ex = 80;
	me->experience = 0;
	me->voice = LoadSoundMem(s);
	setPoke(me);
	me->direction = DOWN;
	me->isLive = true;
}