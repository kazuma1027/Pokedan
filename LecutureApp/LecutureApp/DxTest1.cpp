#include "DxLib.h"
#include "all.h"
#include <iostream>
#include <random>
#include <stdio.h>
#include <tchar.h>
#include <map>
#include <stack>
#include <stdio.h>

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (600)                          // ��ʂ̏c��
#define CHIP_SIZE        (40)                           // ��̃`�b�v�̃T�C�Y
#define MAP_HEIGHT		 (400)
#define MAP_WIDTH		 (680)

#define GX (c->x/CHIP_SIZE - m->x)
#define GY (c->y/CHIP_SIZE - m->y)
#define SX (d->x/CHIP_SIZE - m->x)
#define SY (d->y/CHIP_SIZE - m->y)

#define WHITE	GetColor(255,255,255)
#define RED		GetColor(255,0,0)
#define GREEN	GetColor(0,255,0)
#define BLUE	GetColor(0,0,255)
#define BLACK	GetColor(0,0,0)

#define KEY(X,Y) ((X) * 100 + (Y))
#define KEYDATA(X, Y, N) std::pair<int, NODE>(KEY(X,Y), N)		//���W�ƃm�[�h���y�A�ɂ���

#define ENEMYNUM 3

/*�W�����v�p�ϐ�*/
int temp = 0;
int y_temp = 0;
int y_prev = 0;

/*�W�����v�p�t���O*/
bool onGround = false;		//�W�����v����u��
bool jump = false;			//�W�����v���Ă��邩�ǂ���	

/*�R���\�[���\���p�ϐ�*/
char message1[256];
char message2[256];
char message3[256];
char s[256];				//sprintf_s�p�̔z��
bool messageflag = false;	//���b�Z�[�W��\�����邩

char keyState[256];			//������Ă���L�[���i�[

/*�t���O*/
bool endflag = false;		//q�������ƏI���
bool menuflag = false;


/*�|�P�����\����*/
pokemon poke;
pokemon dark;
pokemon dark2;
pokemon dark3;
pokemon* c = &poke;
//pokemon* d = &dark;
pokemon* enemy[ENEMYNUM] = {&dark,&dark2,&dark3};

/*�}�b�v�\����*/
maps mp;
maps* m = &mp;


/*�����t�@�C���������p�z��*/
int slap;
int bgm;
int down;

/*�摜�t�@�C���������p�z��*/
int messageBox;
int skillBox;
int stairs_down;
int stairs_up;
int load;
int load2;



/*�֐��v���g�^�C�v�錾*/
int init();										//������
int getRandom(int,int);							//int max�`int min�͈̔͂ŗ������擾

void wait(int);									//int���ԑ҂�
void wait(int,char* s);							//int���ԑ҂A���S�ɕ����\��
void w_press();									//K�{�^����������i


//��Ɏ����p
void attack(pokemon*, pokemon*);			//�U������
void attack_for(pokemon* me);	//�v���C���[�p�U��
void skillfull(int experience);					//�Z�З͐ݒ�
void turnToPokemon(pokemon*, pokemon*);			//�|�P�����̕�������
void moveJump(pokemon*);						//Jump����


//��ɓG�p
void enemyMove(pokemon*);					//�G�̓���
bool isNearPokemon(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool isNearPokemon2(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool findPokemon(pokemon*, pokemon*);			//�G�������ł���߂��ɂ�����
bool life(pokemon* enemy, pokemon* me);			//�G����ł��邩�ǂ���
//A*�A���S���Y���G�ǔ�
int h(NODE*, NODE*);		//�q���[���X�e�B�b�N�֐��l��Ԃ��A�}���n�b�^������
void setNode(NODE* child, int x, int y, NODE* parent, int cost, int f);		//�m�[�h�̏�����C�ɐݒ肷��
int getCost();				//�ړ��R�X�g��Ԃ��A���̏ꍇ��1��Ԃ�
NODE* Astar(pokemon*);			//A*�A���S���Y���K�p��A���ɐi�ރZ���̃m�[�h��Ԃ�


//���b�Z�[�W�n
void initConsole();								//���b�Z�[�W�{�b�N�X������������
void setMessage(char[]);						//�\�����������b�Z�[�W���Z�b�g����
void outMessage();								//���b�Z�[�W��\������
void initMessage();

/*�ړ�*/
void charaMove(pokemon*, int, int);				//�L�����ړ��A�G�p
void charaMove(pokemon*,pokemon*[ENEMYNUM], int, int);		//�L�����ړ��A�����p�@����ւ��l��
void mapMove(maps*,pokemon*,pokemon*[ENEMYNUM], int, int);	//�}�b�v�ړ��A�����|����l��
void setDirection(pokemon*, int);						//�L�����̌����Ă���������Z�b�g����

void drawMap();
void drawMiniMap();
void drawCharacter(pokemon*,int d_num);
void drawMenu();

pokemon* getAttackEnemy();

bool isPutMoveKey();

/*�L�[��������Ă���t���[�����ɂ���ĕ\������摜��ύX����*/
/*
int getDnum(int key) {
	if (keyState[key] % 60 >= 1 && keyState[key] % 60 < 30) return 0;
	else return 1;
}
*/

/******************************************************************************/
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

/******************************************************************************/

/*
void Screen() {
	while () {
		sprintf_s(s, "�悤�����|�P�����̐��E��");

		messageflag = true;
		setMessage(s);
		outMessage();
	}
}*/

void w_press() {
	while (getCountFrame() == 0) {
		if (keyState[KEY_INPUT_K] == 1) {
			break;
		}
	}
}


/***********************      Main�̏���      *********************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	/*����������*/
	if (init() == -1) { return -1; }

	int d_num = 0;
	int tempTime = 0;

	m->floor = 0;
	int tmp_mx = m->x;
	int tmp_my = m->y;
	
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

		/*�m�F�p���W(���Ƃŏ���)*/
		DrawFormatString(500, 0,  WHITE, "�s�J���W(%d,%d)", c->x + 20 - m->x * CHIP_SIZE, c->y + 20 - m->y * CHIP_SIZE);
		DrawFormatString(500, 20, WHITE, "�_�[���W(%d,%d)", enemy[0]->x + 20 - m->x * CHIP_SIZE, enemy[0]->y + 20 - m->y * CHIP_SIZE);
		DrawFormatString(500, 40, WHITE, "�}�b�v���W(%d,%d)", m->x, m->y);


		/*�K�i�ړ�����*/
		if (mapping[m->floor][GY][GX] == 100) {
			m->floor += 1;
			wait(2000, (char*)(m->floor + 1));
		}

		if (mapping[m->floor][GY][GX] == 101) {
			m->floor -= 1;
			wait(2000, (char*)(m->floor + 1));
		}


		drawCharacter(c, d_num);
		
		for (int i = 0; i < ENEMYNUM; i++) {
			drawCharacter(enemy[i], d_num);
		}

		/*���b�Z�[�W�o��*/
		outMessage();

		/*space�L�[�ŏI���*/
		if (keyState[KEY_INPUT_SPACE] == 1) { endflag = true; }
		
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

			tmp = getAttackEnemy();
			if (tmp != NULL)attack(c, tmp);
			else attack_for(c);

			for (int i = 0; i < ENEMYNUM; i++) {
				if (life(enemy[i], c) == FALSE) {
					enemyMove(enemy[i]);
				}
			}
		}
		/*Right*/
		if (!menuflag && keyState[KEY_INPUT_D]==1) {
			charaMove(c,enemy,1,0);
		}
		/*Left*/
		else if (!menuflag && keyState[KEY_INPUT_A]==1) { 
			charaMove(c,enemy, -1, 0);
		}
		/*Up*/
		else if (!menuflag && keyState[KEY_INPUT_W]==1) {
			charaMove(c,enemy, 0, -1);
		}
		/*Down*/
		else if (!menuflag && keyState[KEY_INPUT_X]==1) {
			charaMove(c,enemy, 0, 1);
		}
		/*RightUp*/
		else if (!menuflag && keyState[KEY_INPUT_E] == 1) {
			charaMove(c, enemy, 1, -1);
		}
		/*RightDown*/
		else if (!menuflag && keyState[KEY_INPUT_C] == 1) {
			charaMove(c, enemy, 1, 1);
		}
		/*LeftUp*/
		else if (!menuflag && keyState[KEY_INPUT_Q] == 1) {
			charaMove(c, enemy, -1, -1);
		}
		/*LeftDown*/
		else if (!menuflag && keyState[KEY_INPUT_Z] == 1) {
			charaMove(c, enemy, -1, 1);
		}

		
		if (!menuflag && isPutMoveKey() && tmp_mx == m->x && tmp_my == m->y) {
			if (keyState[KEY_INPUT_Y] == 0 && keyState[KEY_INPUT_I] == 0) {
				for (int i = 0; i < ENEMYNUM; i++) {
					enemyMove(enemy[i]);
				}
			}
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


		if (endflag) {
			break;
		}
	}

	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}


void wait(int ms,char* s) {
	int tmp = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetNowCount() - tmp < ms) {
		DrawFormatString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetColor(255,255,255), "B%dF", s);
	}
}

void wait(int ms) {
	int tmp = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && GetNowCount() - tmp < ms) {
		
	}
}

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

	/*��X�����̖��O����͂�����*/
	c->name = "�s�J�`���E";
	enemy[0]->name = "�_�[�N���C";
	enemy[1]->name = "�_�[�N���C";
	enemy[2]->name = "�_�[�N���C";

	/*�摜�̃��[�h*/
	c->moveTexture[DOWN][0] = LoadGraph("�摜/�s�J�`���Ed_1.png");
	c->moveTexture[DOWN][1] = LoadGraph("�摜/�s�J�`���Ed_2.png");
	c->moveTexture[UP][0] = LoadGraph("�摜/�s�J�`���Eu_1.png");
	c->moveTexture[UP][1] = LoadGraph("�摜/�s�J�`���Eu_2.png");
	c->moveTexture[LEFT][0] = LoadGraph("�摜/�s�J�`���El_1.png");
	c->moveTexture[LEFT][1] = LoadGraph("�摜/�s�J�`���El_2.png");
	c->moveTexture[RIGHT][0] = LoadGraph("�摜/�s�J�`���Er_1.png");
	c->moveTexture[RIGHT][1] = LoadGraph("�摜/�s�J�`���Er_2.png");

	c->skill[0].name = "�ł񂱂�������";
	c->skill[1].name = "10�܂�{���g";
	c->skill[2].name = "���݂Ȃ�";
	c->skill[3].name = "�Ђ�����";

	c->skill[0].value = 2;
	c->skill[1].value = 7;
	c->skill[2].value = 10;
	c->skill[3].value = 3;

	c->skill[0].maxCount = 20;
	c->skill[1].maxCount = 10;
	c->skill[2].maxCount = 5;
	c->skill[3].maxCount = 20;

	c->skill[0].count = c->skill[0].maxCount;
	c->skill[1].count = c->skill[1].maxCount;
	c->skill[2].count = c->skill[2].maxCount;
	c->skill[3].count = c->skill[3].maxCount;

	c->maxHp = 30;
	c->hp = 30;

	skillfull(0);

	for (int i = 0; i < ENEMYNUM; i++) {
		enemy[i]->moveTexture[DOWN][0] = LoadGraph("�摜/�_�[�N���Cd_1.png");
		enemy[i]->moveTexture[DOWN][1] = LoadGraph("�摜/�_�[�N���Cd_2.png");
		enemy[i]->moveTexture[UP][0] = LoadGraph("�摜/�_�[�N���Cu_1.png");
		enemy[i]->moveTexture[UP][1] = LoadGraph("�摜/�_�[�N���Cu_2.png");
		enemy[i]->moveTexture[LEFT][0] = LoadGraph("�摜/�_�[�N���Cl_1.png");
		enemy[i]->moveTexture[LEFT][1] = LoadGraph("�摜/�_�[�N���Cl_2.png");
		enemy[i]->moveTexture[RIGHT][0] = LoadGraph("�摜/�_�[�N���Cr_1.png");
		enemy[i]->moveTexture[RIGHT][1] = LoadGraph("�摜/�_�[�N���Cr_2.png");

		enemy[i]->skill[0].name = "�ł񂱂�������";
		enemy[i]->skill[1].name = "���܂�����";
		enemy[i]->skill[2].name = "�����̂͂ǂ�";
		enemy[i]->skill[3].name = "�ꂢ�Ƃ��r�[��";

		enemy[i]->skill[0].value = 2;
		enemy[i]->skill[1].value = 7;
		enemy[i]->skill[2].value = 10;
		enemy[i]->skill[3].value = 3;


		enemy[i]->skill[0].maxCount = 20;
		enemy[i]->skill[1].maxCount = 10;
		enemy[i]->skill[2].maxCount = 20;
		enemy[i]->skill[3].maxCount = 10;

		enemy[i]->skill[0].count = c->skill[0].maxCount;
		enemy[i]->skill[1].count = c->skill[1].maxCount;
		enemy[i]->skill[2].count = c->skill[2].maxCount;
		enemy[i]->skill[3].count = c->skill[3].maxCount;

		enemy[i]->voice = LoadSoundMem("���y/�_�[�N���Cvoice.mp3");

		enemy[i]->experience = 10000;

		enemy[i]->maxHp = 70;
		enemy[i]->hp = 70;
	}
	/*�K�i�̉摜*/
	stairs_down = LoadGraph("�摜/stairs.png");
	stairs_up = LoadGraph("�摜/stairs2.png");

	/*���F�̓���*/
	SetTransColor(255, 255, 255);
	/*���b�Z�[�W�{�b�N�X*/
	messageBox = LoadGraph("�摜/messageBox.png");
	SetTransColor(255, 0, 0);
	/*�킴�I���{�b�N�X*/
	skillBox = LoadGraph("�摜/skillBox.png");
	/*���W�ʒu*/
	c->x = CHIP_SIZE * 3;
	c->y = CHIP_SIZE * 3;
	
	bool flag = 0;
	for (int i = 0; i < ENEMYNUM; i++) {
		while (true) {
			flag = true;
			enemy[i]->x = getRandom(3, 27) * CHIP_SIZE;
			enemy[i]->y = getRandom(3, 27) * CHIP_SIZE;
			if (mapping[0][enemy[i]->y/CHIP_SIZE][enemy[i]->x/CHIP_SIZE] > 0) {
				//���𖳂���
				for (int j = 0; j < i; j++) {
					if (enemy[i]->x == enemy[j]->x && enemy[i]->y == enemy[j]->y)flag = false;
				}
				if (flag)break;
			}
		}
	}



	/*���������[�h*/
	slap = LoadSoundMem("���y/slap1.mp3");
	bgm = LoadSoundMem("���y/bgm.mp3");
	down = LoadSoundMem("���y/down1.mp3");

	load = LoadGraph("�摜/load.png");
	load2 = LoadGraph("�摜/load2.png");

	return 0;
}

//�Z�З͐ݒ�
void skillfull(int level) {
	c->skill[0].min = 2 + level * 2;
	c->skill[0].max = 4 + level * 2;
	c->skill[1].min = 5 + level * 2;
	c->skill[1].max = 8 + level * 2;
	c->skill[2].min = 8 + level * 2;
	c->skill[2].max = 14 + level * 2;
	c->skill[3].min = 1 + level * 2;
	c->skill[3].max = 3 + level * 2;

	for (int i = 0; i < ENEMYNUM; i++) {

		enemy[i]->skill[0].min = 2;
		enemy[i]->skill[0].max = 4;
		enemy[i]->skill[1].min = 3;
		enemy[i]->skill[1].max = 6;
		enemy[i]->skill[2].min = 8;
		enemy[i]->skill[2].max = 14;
		enemy[i]->skill[3].min = 4;
		enemy[i]->skill[3].max = 8;
	}
}


/*attack(����,�G,�U���̎��)*/
void attack(pokemon* me, pokemon* enemy) {

	//turnToPokemon(me, enemy);//�G�̕�������
	int value = getRandom(me->skill[me->attackNum].min, me->skill[me->attackNum].max);	//�킴���o�����тɗ�������
	if (me->skill[me->attackNum].count > 0) {
		//�G�̕��������Ă���ꍇ
		if (enemy->isLive && isNearPokemon(me,enemy)&&((me->y == enemy->y &&  ((me->x > enemy->x && me->direction == LEFT)||(me->x < enemy->x && me->direction == RIGHT)))||(me->x == enemy->x && ((me->y > enemy->y && me->direction==UP|| me->y<enemy->y && me->direction==DOWN))))) {
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



/*�U�����ɓG�̕�������*/
/*�̂��Ɍ�������O�ɉ摜��~���ă_�u���𖳂���*/
/*�������͌����Ă�������ɍU��������̂ł���͏�������?*/
void turnToPokemon(pokemon* me, pokemon* enemy) {
	if (me->x > enemy->x)me->direction = LEFT;
	else if (me->x < enemy->x)me->direction = RIGHT;
	if (me->y > enemy->y)me->direction = UP;
	else if (me->y < enemy->y)me->direction = DOWN;
}

/*���̃R���\�[��������*/
void initConsole() {

	/*���b�Z�[�W�t���O�������Ă���΁A���b�Z�[�W�{�b�N�X�\��*/
	/*�㏑�����Ă���*/
	if (messageflag) {
		DrawRotaGraph(SCREEN_WIDTH / 2, 500, 1, 0, messageBox, true);
	}
}

/*�\�����郁�b�Z�[�W���Z�b�g*/
void setMessage(char s[]) {

	messageflag = true;

	char temp[256];
	/*������*/
	for (int i = 0; i < 256; i++)temp[i] = '\0';

	/*������R�s�[*/
	for (int i = 0; s[i] != '\0'; i++) { temp[i] = s[i]; }

	/*message1->��i�Amessage2->���i�Amessage3->���i*/
	if (message1[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message1[i] = temp[i]; }
	else if (message2[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message2[i] = temp[i]; }
	else if (message3[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message3[i] = temp[i]; }
	/*�S�Ė��܂��Ă���΁A���e����i���グ�ĕ\������*/
	else {
		for (int i = 0; i < 256; i++) { message1[i] = '\0'; }
		for (int i = 0; i < 256; i++) { message1[i] = message2[i]; }

		for (int i = 0; i < 256; i++)message2[i] = '\0';
		for (int i = 0; i < 256; i++) { message2[i] = message3[i]; }

		for (int i = 0; i < 256; i++) { message3[i] = temp[i]; }
	}
}

/*���b�Z�[�W�\��*/
void outMessage() {

	initConsole();
	/*�R���\�[���\��*/
	DrawFormatString(100, 487, GetColor(255, 255, 255), "%s", message1);
	DrawFormatString(100, 517, GetColor(255, 255, 255), "%s", message2);
	DrawFormatString(100, 547, GetColor(255, 255, 255), "%s", message3);
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


/*���͂̃}�X�ɓG�����邩���Ȃ���*/
/*�U�����Ɏg�p����*/
/*�ȂȂ߂𔲂�*/
/*4��ver*/
bool isNearPokemon(pokemon* me, pokemon* enemy) {
	if ((me->y == enemy->y && (me->x - CHIP_SIZE == enemy->x || me->x + CHIP_SIZE == enemy->x)) || (me->x == enemy->x && (me->y - CHIP_SIZE == enemy->y || me->y + CHIP_SIZE == enemy->y))) {
		return true;
	}
	return false;
}

/*8��ver*/
bool isNearPokemon2(pokemon* me, pokemon* enemy) {
	if (me->x - CHIP_SIZE <= enemy->x && me->x + CHIP_SIZE >= enemy->x && me->y - CHIP_SIZE <= enemy->y && me->y + CHIP_SIZE >= enemy->y) {
		return true;
	}
	return false;
}

/*�����}�b�v���ɂ��邩�ǂ���*/
bool findPokemon(pokemon* me, pokemon* enemy) {
	if ((me->x - SCREEN_WIDTH/2 < enemy->x) && (me->x + SCREEN_WIDTH/2 > enemy->x) && (me->y + SCREEN_HEIGHT/2 > enemy->y) && (me->y - SCREEN_HEIGHT/2 < enemy->y))return true;
	else return false;
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
		while (me->Max_ex < enemy->experience) {
			enemy->experience = enemy->experience - me->Max_ex;
			me->level++;
			me->Max_ex += 30;
			sprintf_s(s, "%s��%d���x���ɏオ�����I", me->name, me->level);
			setMessage(s);
			outMessage();
			wait(400);
			//w_press();
		}
		enemy->isLive = false;
		initMessage();
		return TRUE;
	}
	return FALSE;
}


/*�G�̓���*/
void enemyMove(pokemon* enemy) {

	//����ł����牽�����Ȃ�
	if (!enemy->isLive)return;

	//�����̍��W�擾
	int sx = enemy->x / CHIP_SIZE - m->x;
	int sy = enemy->y / CHIP_SIZE - m->y;

	/*�G�������}�b�v���ɂ���ƁA�����Ɍ������Ă���*/
	if (findPokemon(enemy, c)) {

		/*4���ɂ���Ƃ��A�U������*/
		if (isNearPokemon(enemy, c)) {
			turnToPokemon(enemy, c);
			enemy->attackNum = getRandom(0, 3);
			attack(enemy, c);		//�����_���ł킴��I��
		}
		/*8��(�����ł͂ȂȂ�)�ɂ���Ƃ��A�U���ł���͈͂Ɉړ�����*/
		else if (isNearPokemon2(enemy, c)) {
			charaMove(enemy, (c->x - enemy->x)/CHIP_SIZE, (c->y - enemy->y)/CHIP_SIZE);	//�U���ł���Ƃ���Ɉړ�����
		}
		/*8���ɂ��Ȃ��Ƃ���A*�A���S���Y��*/
		else if (!isNearPokemon2(enemy, c)) {
			NODE* nextEnemy = Astar(enemy);
			charaMove(enemy,nextEnemy->x - sx,nextEnemy->y - sy);
		}
	}
	/*�܂��Ώۂ��������Ă��Ȃ��ꍇ�A���낤�낷��*/
	else {
		switch (getRandom(0,8)) {
		case LEFT:
			charaMove(enemy, -1, 0);
			break;
		case RIGHT:
			charaMove(enemy, 1, 0);
			break;
		case UP:
			charaMove(enemy, 0, -1);
			break;
		case DOWN:
			charaMove(enemy, 0, 1);
			break;
		case LEFT_UP:
			charaMove(enemy, -1, -1);
			break;
		case LEFT_DOWN:
			charaMove(enemy, -1, 1);
			break;
		case RIGHT_UP:
			charaMove(enemy, 1, -1);
			break;
		case RIGHT_DOWN:
			charaMove(enemy, 1, 1);
			break;
		default:
			break;
		}
	}
}

/*0�`3�̗����𓾂�*/
int getRandom(int min,int max) {
	
	std::random_device rd;

	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dice(min, max);

	return dice(mt);
}

/*�����p�̏���*/
void charaMove(pokemon* me,pokemon* enemy[ENEMYNUM], int x, int y) {

	//�����Ă���������Z�b�g
	if (x == 1)setDirection(me,RIGHT);
	else if(x == -1)setDirection(me,LEFT);

	if (y == 1)setDirection(me,DOWN);
	else if(y == -1)setDirection(me,UP);

	//�}�b�v�ړ��p
	int mx = 0;
	int my = 0;

	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[m->floor][me->y / CHIP_SIZE - m->y + y][me->x  / CHIP_SIZE - m->x + x];

	/*�ȂȂ߈ړ��̂Ƃ�*/
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {

		int nextCell_x = mapping[m->floor][me->y / CHIP_SIZE - m->y][me->x / CHIP_SIZE - m->x + x];	//�����̍��E�ǂ��炩�̃Z���̏��
		int nextCell_y = mapping[m->floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x];	//�����̏㉺�ǂ��炩�̃Z���̏��

		//�i�ސ悪��Q���ŁA���E�ǂ��炩�A�㉺�ǂ��炩�����ł���Ί���
		if (nextCell <= 0 && !keyState[KEY_INPUT_Y]) {
			if (nextCell_x > 0 && nextCell_y <=0)y = 0;
			if (nextCell_y > 0 && nextCell_x <=0)x = 0;
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
	nextCell = mapping[m->floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x + x];

	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		/*�ړ���ɓG�����������ւ��*/
		for (int i = 0; i < ENEMYNUM; i++) {
			if (me->x + x * CHIP_SIZE == enemy[i]->x && me->y + y * CHIP_SIZE == enemy[i]->y) { enemy[i]->x = me->x; enemy[i]->y = me->y; }
		}
			me->x += x * CHIP_SIZE;
			me->y += y * CHIP_SIZE;
	}

	//�}�b�v�ړ��������
	if (!(mx == 0 && my == 0)) {
		mapMove(m, me, enemy, mx, my);
	}
}

/*�G�p�̏���,����ւ�菈���𖳂�����*/
void charaMove(pokemon* me, int x, int y) {

	if (x == 1)setDirection(me, RIGHT);
	else if (x == -1)setDirection(me, LEFT);

	if (y == 1)setDirection(me, DOWN);
	else if (y == -1)setDirection(me, UP);

	int tmpX = (me->x - c->x)/CHIP_SIZE;
	int tmpY = (me->y - c->y)/CHIP_SIZE;
	int nextCell_x = mapping[m->floor][me->y / CHIP_SIZE - m->y][me->x / CHIP_SIZE - m->x + x];
	int nextCell_y = mapping[m->floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x];

	//�ȂȂ߈ړ����ɁA�ȂȂ߂Ɏ�l���������
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {
		if ((tmpX == 1 || tmpX == -1) && (tmpY == 1 || tmpY == -1)) {
			//�U���ł���͈͂Ɉړ�����
			if (nextCell_x > 0)y = 0;
			else if (nextCell_y > 0)x = 0;
		}
	}
	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[m->floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x + x];

	if (nextCell > 0) {
		me->x += x * CHIP_SIZE;
		me->y += y * CHIP_SIZE;
	}
}

void mapMove(maps* m,pokemon* me,pokemon* enemy[ENEMYNUM], int x, int y) {

	int nextCell = mapping[m->floor][me->y / CHIP_SIZE - m->y - y][me->x  / CHIP_SIZE - m->x - x];

	//�ړ������ƈ����|���菈��
	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		m->x += x;
		m->y += y;
		for (int i = 0; i < ENEMYNUM; i++) {
			int enemyCell = mapping[m->floor][enemy[i]->y / CHIP_SIZE - m->y][enemy[i]->x / CHIP_SIZE - m->x];
			if (enemyCell <= 0)charaMove(enemy[i], x, y);
		}
	}

}

void setDirection(pokemon* me, int direction) {
	me->direction = direction;
}


void initMessage() {
	messageflag = false;
	for (int i = 0; i < 256; i++) {
		message1[i] = '\0';
		message2[i] = '\0';
		message3[i] = '\0';
	}
}


void setNode(NODE* child, int x, int y, NODE* parent, int cost,int f) {
	child->x = x;
	child->y = y;
	child->parent = parent;
	child->cost = cost;
	child-> f = f;
}

int getCost() {
	return 1;
}


int g(NODE* s, NODE* n) {
	return n->cost;
}

//�q���[���X�e�B�b�N�֐�
//�}���n�b�^������
int h(NODE* e, NODE* n) {
	//�I�_���猩�����݂̃m�[�h�܂ł̐���R�X�g���v�Z
	int cx = e->x - n->x;
	int cy = e->y - n->y;
	if (cx < 0)cx *= -1;
	if (cy < 0)cy *= -1;

	if (cx < cy) {
		return (cx + cy);
	}
	else {
		return (cy + cx);
	}
}

NODE* Astar(pokemon* enemy) {

	//���ʕێ��p�X�^�b�N
	std::stack<NODE*> st;
	std::map<int, NODE> openList;
	std::map<int, NODE>closedList;
	int loop = 0;
	NODE s = { 0,0,0 };
	NODE e = { 0,0,0 };

	
	int key[8][2] = {
		{1,0},
		{-1,0},
		{0,-1},
		{0,1},
		{1,1},
		{-1,1},
		{1,-1},
		{-1,-1},
	};

	//open.index = 0;
	//close.index = 0;

	//�X�^�[�g
	//�G�̍��W
	s.x = (enemy->x / CHIP_SIZE - m->x);
	s.y = (enemy->y / CHIP_SIZE - m->y);

	//�e�m�[�h�A�R�X�g�A�]���l�Ȃ�
	setNode(&s, s.x, s.y, NULL, 0, 0);
	//open.node[open.index++] = &s;
	//�I�[�v�����X�g�ɑ��
	openList.insert(KEYDATA(s.x,s.y,s));

	//�S�[��
	//�����̍��W
	e.x = (c->x / CHIP_SIZE - m->x);
	e.y = (c->y / CHIP_SIZE - m->y);

	while (true) {

		

		// open���X�g���Ȃ��Ȃ����̂ŏI������
		if (openList.empty()) { break; }
		
		int f_min = 999;

		//�W�J�p
		NODE *p = new NODE;

		auto it = openList.begin();		//�擪�C�e���[�^�擾
		std::map<int, NODE>::iterator it_min;
		while (it != openList.end()) {
			if (f_min > it->second.f) {
				f_min = it->second.f;
				it_min = it;
			}
			it++;
		}
		
		setNode(
			p,
			it_min->second.x, it_min->second.y,
			it_min->second.parent,
			it_min->second.cost, it_min->second.f
		);
		

		//�e�m�[�h���I�[�v�����X�g����폜
		openList.erase(KEY(p->x, p->y));
		//�e�m�[�h���N���[�Y�h���X�g�ɑ}��
		closedList.insert(KEYDATA(p->x, p->y, *p));

		// �����S�[���Ȃ炽�����ɏI������
		if (p->y == e.y && p->x == e.x) {

			st.push(p);
			p = p->parent;
			while (p->parent != NULL) {
				st.push(p);
				p = p->parent;
			}
			
			break;
		}

		//�q�m�[�h�W�J
		for (int i = 0; i < 8; i++) {
			
			//�q�m�[�h�]���p
			NODE* child = new NODE;
			
			
			//����8�}�X���v�Z
			int cx = p->x + key[i][0];
			int cy = p->y + key[i][1];
			
			//0�ȉ��͒ʂ�Ȃ��̂Ŕ�΂�
			if (mapping[m->floor][cy][cx] <= 0)continue;

			//�m�[�h�̎��̂͂قڍ��W
			child->x = cx;
			child->y = cy;
			
			//���̃R�X�g�A�]���l�v�Z
			int cost = p->cost + getCost();
			int f = cost + h(&e, child);
			
			//�ŏ��R�X�g�̐e�̂͂��Ȃ̂ŁA��ɐe�����Ă��܂�
			setNode(child, cx, cy, p, cost, f);

			//�I�[�v�����X�g
			if (openList.count(KEY(cx, cy))) {
				auto open_child = openList.find(KEY(cx, cy));
				//�]���l�����������̏����g�p
				if (child->f < open_child->second.f) {
					openList[KEY(cx,cy)].cost = child->cost;
					openList[KEY(cx,cy)].f	  = child->f;
					openList[KEY(cx,cy)].parent = child->parent;
				}
			}
			//�N���[�Y�h���X�g
			else if (closedList.count(KEY(cx, cy))) {
				auto closed_child = closedList.find(KEY(cx, cy));
				//�]���l�����������̏����g�p
				if (child->f < closed_child->second.f) {
					closed_child->second.cost = child->cost;
					closed_child->second.f = child->f;
					closed_child->second.parent = child->parent;
				
					//�I�[�v�����X�g�ɖ߂�
					openList.insert(KEYDATA(cx,cy,closed_child->second));
					closedList.erase(KEY(cx, cy));
				}

			}
			else {//�I�[�v�����X�g�ɂ��N���[�Y�h���X�g�ɂ��܂܂�Ă��Ȃ�
				openList.insert(KEYDATA(cx, cy, *child));
			}


			
		}

		if (loop++ > 1000) { break; }
		
	}
	
	NODE* node = st.top();

	
	return node;
}

void drawMap() {
	/*�}�b�v�S�͈͑���*/
	for (int x = m->x; x < SCREEN_WIDTH / CHIP_SIZE - m->x; x++) {
		for (int y = m->y; y < SCREEN_HEIGHT / CHIP_SIZE - m->y; y++) {
			if (mapping[m->floor][y][x] == 0) { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, WHITE, " "); }
			else if (mapping[m->floor][y][x] == 1) { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, load, true); }
			else if (mapping[m->floor][y][x] == 2) { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, load2, true); }
			else if (mapping[m->floor][y][x] == 3) { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, GetColor(0, 0, 255), "B"); }
			else if (mapping[m->floor][y][x] == 5) { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, GetColor(0, 0, 255), "*"); }
			else if (mapping[m->floor][y][x] == 100) { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, stairs_down, true); }
			else if (mapping[m->floor][y][x] == 101) { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, stairs_up, true); }
		}
	}
}

void drawCharacter(pokemon* me, int d_num) {
	//�����Ă���Ε\��
	if (me->isLive) {
	/*���W�͉摜�̐^�񒆂Ɏ���*/
	/*DrawRotaGraph(x���W,y���W,�k�ړx,�p�x,�`�悷��摜�n���h��,�w�i���ߏ�����ON,OFF)*/
		DrawRotaGraph(me->x + 20, me->y + 20, 1.5, 0, me->moveTexture[me->direction][d_num], true);
	}
}

void drawMiniMap() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (mapping[m->floor][j][i] == 1 || mapping[m->floor][j][i] == 2)DrawFormatString(i * 3, j * 3, WHITE, ".");
			if (i == GX && j == GY)DrawFormatString(i * 3, j * 3, RED, ".");
			for (int k = 0; k < ENEMYNUM; k++) {
				if (i == enemy[k]->x/CHIP_SIZE - m->x && j == enemy[k]->y/CHIP_SIZE - m->y && enemy[k]->isLive)DrawFormatString(i * 3, j * 3, BLUE, ".");
			}
			if (mapping[m->floor][j][i] == 100)DrawFormatString(i * 3, j * 3, GREEN, ".");
			if (mapping[m->floor][j][i] == 101)DrawFormatString(i * 3, j * 3, GREEN, ".");
		}
	}
}

void drawMenu() {
	DrawRotaGraph(550, 160, 1, 0, skillBox, true);
	DrawFormatString(530, 98, WHITE, "%s (%d/%d)", c->skill[0].name, c->skill[0].count, c->skill[0].maxCount);
	DrawFormatString(530, 149, WHITE, "%s (%d/%d)", c->skill[1].name, c->skill[1].count, c->skill[1].maxCount);
	DrawFormatString(530, 199, WHITE, "%s (%d/%d)", c->skill[2].name, c->skill[2].count, c->skill[2].maxCount);
	DrawFormatString(530, 250, WHITE, "%s (%d/%d)", c->skill[3].name, c->skill[3].count, c->skill[3].maxCount);
	if (keyState[KEY_INPUT_1]) { c->attackNum = 0; menuflag = false; }
	else if (keyState[KEY_INPUT_2]) { c->attackNum = 1; menuflag = false; }
	else if (keyState[KEY_INPUT_3]) { c->attackNum = 2; menuflag = false; }
	else if (keyState[KEY_INPUT_4]) { c->attackNum = 3; menuflag = false; }
}

bool isPutMoveKey() {
	
	if (keyState[KEY_INPUT_Q] == 1 || keyState[KEY_INPUT_W] == 1 || keyState[KEY_INPUT_E] == 1 || keyState[KEY_INPUT_D] == 1 || keyState[KEY_INPUT_C] == 1 || keyState[KEY_INPUT_X] == 1 || keyState[KEY_INPUT_Z] == 1 || keyState[KEY_INPUT_A] == 1) {
		return true;
	}
	else {
		return false;
	}

}

pokemon* getAttackEnemy() {
	
	for (int i = 0; i < ENEMYNUM; i++) {

		if (c->direction == UP) {
			if (c->x == enemy[i]->x && c->y - CHIP_SIZE == enemy[i]->y) {
				if (enemy[i]->isLive) {
					return enemy[i];
				}
			}
		}
		else if (c->direction == RIGHT) {
			if (c->y == enemy[i]->y && c->x + CHIP_SIZE == enemy[i]->x) {
				if (enemy[i]->isLive) {
					return enemy[i];
				}
			}
		}
		else if (c->direction == DOWN) {
			if (c->x == enemy[i]->x && c->y + CHIP_SIZE == enemy[i]->y) {
				if (enemy[i]->isLive) {
					return enemy[i];
				}
			}
		}
		else if (c->direction == LEFT) {
			if (c->y == enemy[i]->y && c->x - CHIP_SIZE == enemy[i]->x) {
				if (enemy[i]->isLive) {
					return enemy[i];
				}
			}
		}
	}
	return NULL;
}