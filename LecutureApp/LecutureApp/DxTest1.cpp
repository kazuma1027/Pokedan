#include "DxLib.h"
#include "pokemon.h"
#include <iostream>
#include <random>

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (600)                          // ��ʂ̏c��
#define CHIP_SIZE        (40)                           // ��̃`�b�v�̃T�C�Y
#define MAP_HEIGHT		 (400)
#define MAP_WIDTH		 (680)
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
pokemon* c = &poke;
pokemon* d = &dark;

map mp;
map* m = &mp;

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

/*�v���g�^�C�v�錾*/
int init();
void w_press();										//K�{�^����������i
void attack(pokemon*, pokemon*, int);			//�U��
void attack_for(pokemon* me, int attackNum);	//�v���C���[�p�U��
void skillfull(int experience);					//�Z�З�
void turnToPokemon(pokemon*, pokemon*);			//�|�P�����̕�������
void moveJump(pokemon*);						//Jump����
void initConsole();								//���b�Z�[�W�{�b�N�X������������
void setMessage(char[]);						//�\�����������b�Z�[�W���Z�b�g����
void outMessage();								//���b�Z�[�W��\������
bool isNearPokemon(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool findPokemon(pokemon*, pokemon*);
bool life(pokemon* enemy, pokemon* me);						//�G����ł��邩�ǂ���
void enemyMove(pokemon*, int);						//�G�̓���
int getRandom(int,int);
void wait(int,char* s);
void wait(int);
void charaMove(pokemon*, int, int, int);
void charaMove(pokemon*,pokemon*, int, int, int);
void mapMove(map*,pokemon*,pokemon*, int, int, int);
void setDirection(pokemon*, int);
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
	for (int i = 0; i<256; i++) {
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
	int nearCell[9];
	int enemyCell = 0;

	int floor = 0;

	/*���F���i�[*/
	const int white = GetColor(255, 255, 255);

	/*bgm�Đ��J�n*/
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	/*�`�悷��*/
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

		/*�}�b�v�S�͈͑���*/
		for (int x = m->x; x < SCREEN_WIDTH/CHIP_SIZE - m->x; x++) {
			for (int y = m->y; y < SCREEN_HEIGHT/CHIP_SIZE - m->y; y++) {
				if (mapping[floor][y][x] == 0)		 { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, white, "0"); }//DrawRotaGraph(x*CHIP_SIZE + 20, y*CHIP_SIZE + 20, 1.5,0,c->moveTexture[0][0],true); }
				else if (mapping[floor][y][x] == 1)  { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1,0,load,true); }
				else if (mapping[floor][y][x] == 2)  { DrawRotaGraph((m->x + x) * CHIP_SIZE + 20   , (m->y + y) * CHIP_SIZE + 20, 1.5,0, d->moveTexture[0][0],true); }
				else if (mapping[floor][y][x] == 3)  { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, GetColor(0, 0, 255), "B"); }
				else if (mapping[floor][y][x] == 5)  { DrawFormatString((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, GetColor(0,0,255), "*"); }
				else if (mapping[floor][y][x] == 100){ DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, stairs_down, true);}
				else if (mapping[floor][y][x] == 101){ DrawRotaGraph((m->x + x) * CHIP_SIZE + 20, (m->y + y) * CHIP_SIZE + 20, 1, 0, stairs_up, true);}
			}
		}

		/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
		if (GetNowCount() - tempTime> 500) 
		{	
			if (d_num == 1)d_num = 0;
			else d_num = 1;
			tempTime = GetNowCount(); 
		}

		/*�K�w�Alevel�AHP�\��(�Œ�)*/
		DrawFormatString(0	, 0, white, "B%dF",floor + 1);
		DrawFormatString(50	, 0, white, "Lv: %d",c->level);
		DrawFormatString(120, 0, white, "HP: %d/ %d",c->hp,c->maxHp);
		DrawFormatString(220, 0, white, "�Z�b�g�킴�� : %s",c->skill[c->attackNum].name);

		/*�m�F�p���W(���Ƃŏ���)*/
		DrawFormatString(500, 0, white, "�s�J���W(%d,%d)", c->x + 20 - m->x * CHIP_SIZE, c->y + 20 - m->y * CHIP_SIZE);
		DrawFormatString(500, 20, white, "�_�[���W(%d,%d)", d->x + 20 - m->x * CHIP_SIZE, d->y + 20 - m->y*CHIP_SIZE);
		DrawFormatString(500, 40, white, "�}�b�v���W(%d,%d)", m->x, m->y);

		/*DrawRotaGraph(x���W,y���W,�k�ړx,�p�x,�`�悷��摜�n���h��,�w�i���ߏ�����ON,OFF)*/
		/*���W�͉摜�̐^�񒆂Ɏ���*/
		DrawRotaGraph(c->x + 20, c->y + 20, 1.5, 0, c->moveTexture[c->direction][d_num], true);
		
		/*�����Ă���G�\��*/
		if (d->isLive) { DrawRotaGraph(d->x + 20, d->y + 20, 1.5, 0, d->moveTexture[d->direction][d_num], true); }

		/*���b�Z�[�W�o��*/
		outMessage();

		/*q�L�[�ŏI���*/
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
			DrawRotaGraph(550, 160, 1, 0, skillBox, true);
			DrawFormatString(530, 98,  white, "%s (%d/%d)", c->skill[0].name, c->skill[0].count, c->skill[0].maxCount);
			DrawFormatString(530, 149, white, "%s (%d/%d)", c->skill[1].name, c->skill[1].count, c->skill[1].maxCount);
			DrawFormatString(530, 199, white, "%s (%d/%d)", c->skill[2].name, c->skill[2].count, c->skill[2].maxCount);
			DrawFormatString(530, 250, white, "%s (%d/%d)", c->skill[3].name, c->skill[3].count, c->skill[3].maxCount);
			if (keyState[KEY_INPUT_1])		{ c->attackNum = 0; menuflag = false; }
			else if (keyState[KEY_INPUT_2]) { c->attackNum = 1; menuflag = false; }
			else if (keyState[KEY_INPUT_3]) { c->attackNum = 2; menuflag = false; }
			else if (keyState[KEY_INPUT_4]) { c->attackNum = 3; menuflag = false; }
		}
		
		/*���setNearMap�֐������Ă���������*/
		nearCell[RIGHT]		= mapping[floor][c->y / CHIP_SIZE - m->y][(c->x + CHIP_SIZE) / CHIP_SIZE - m->x];
		nearCell[LEFT]		= mapping[floor][c->y / CHIP_SIZE - m->y][(c->x - CHIP_SIZE) / CHIP_SIZE - m->x];
		nearCell[UP]		= mapping[floor][(c->y - CHIP_SIZE) / CHIP_SIZE - m->y][c->x / CHIP_SIZE - m->x];
		nearCell[DOWN]		= mapping[floor][(c->y + CHIP_SIZE) / CHIP_SIZE - m->y][c->x / CHIP_SIZE - m->x];

		nearCell[RIGHT_UP]	= mapping[floor][(c->y - CHIP_SIZE) / CHIP_SIZE - m->y][(c->x + CHIP_SIZE) / CHIP_SIZE - m->x];
		nearCell[RIGHT_DOWN]= mapping[floor][(c->y + CHIP_SIZE) / CHIP_SIZE - m->y][(c->x + CHIP_SIZE) / CHIP_SIZE - m->x];
		nearCell[LEFT_UP]	= mapping[floor][(c->y - CHIP_SIZE) / CHIP_SIZE - m->y][(c->x - CHIP_SIZE) / CHIP_SIZE - m->x];
		nearCell[LEFT_DOWN]	= mapping[floor][(c->y + CHIP_SIZE) / CHIP_SIZE - m->y][(c->x - CHIP_SIZE) / CHIP_SIZE - m->x];

		nearCell[CENTER]	= mapping[floor][c->y / CHIP_SIZE - m->y][c->x / CHIP_SIZE - m->x];

		enemyCell = mapping[floor][d->y / CHIP_SIZE - m->y][d->x / CHIP_SIZE - m->x];

		/*Attack*/
		if (!menuflag && keyState[KEY_INPUT_J] == 1) {
			//�����̋߂��ɂ����
			if (isNearPokemon(c, d) && d->isLive) {
				attack(c, d, c->attackNum);
			}
			//�߂��ɂ��Ȃ��ꍇ�U���͊O���
			else if (d->isLive) {
				attack_for(c, c->attackNum);
			}
			if (life(d, c) == FALSE) {
				enemyMove(d, floor);
			}
		}


		/*Right*/
		if (!menuflag && keyState[KEY_INPUT_D]==1) {
			if (c->x == MAP_WIDTH) { 
				mapMove(m, c, d, -1, 0,floor);
			}
			else {
				charaMove(c,d,1,0,floor);
				if (!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
		}

		/*Left*/
		else if (!menuflag && keyState[KEY_INPUT_A]==1) { 
			if (c->x == CHIP_SIZE * 2 && m->x != 0) {
				mapMove(m, c, d, 1, 0, floor);
			}
			else  {
				charaMove(c,d, -1, 0,floor);
				if (!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
			
		}

		/*Up*/
		else if (!menuflag && keyState[KEY_INPUT_W]==1) {
			if (c->y == CHIP_SIZE * 2 && m->y != 0) { 
				mapMove(m, c, d, 0, 1,floor);
			}
			else {
				charaMove(c,d, 0, -1,floor);
				if (!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
			
		}

		/*Down*/
		else if (!menuflag && keyState[KEY_INPUT_X]==1) {
			if (c->y == MAP_HEIGHT){
				mapMove(m, c, d, 0, -1,floor);
			}
			else {
				charaMove(c,d, 0, 1,floor);
				if(!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
		}

		/*RightUp*/
		else if (!menuflag && keyState[KEY_INPUT_E] == 1) {
			if (c->y == CHIP_SIZE * 2 && c->x == MAP_WIDTH) { //�E��[�̏ꍇ
				if (m->y == 0) {							  //�}�b�v������ȏ��ɍs���Ȃ��ꍇ
					mapMove(m, c, d, 1, 0, floor);
					charaMove(c, d, 0, -1, floor);
				}
				else {
					mapMove(m, c, d, -1, 1, floor);
				}
			}
			else if (c->y == CHIP_SIZE * 2) {			//�E�[�ł͂Ȃ�����[�̏ꍇ
				if (m->y != 0) {
					mapMove(m, c, d, 0, 1, floor);
					charaMove(c, d, 1, 0, floor);
				}
				else {
					charaMove(c, d, 1, 0, floor);
				}
			}
			else if (c->x == MAP_WIDTH){				//��[�ł͂Ȃ����E�[�̏ꍇ
				mapMove(m,c,d,-1,0,floor);
				charaMove(c, d, 0, -1, floor);
			}
			else  {										//�}�b�v�̒[�łȂ��ꍇ�Ay�������Ă��Ȃ��ƕ��ʂɈړ�
				charaMove(c, d, 1, -1,floor);
				if(!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
		}
		/*RightDown*/
		else if (!menuflag && keyState[KEY_INPUT_C] == 1) {
			
			if (c->y == MAP_HEIGHT && c->x == MAP_WIDTH) {	//�}�b�v�̉E���[�ł����
				mapMove(m, c, d, -1, -1, floor);
			}
			else if (c->y == MAP_HEIGHT) {					//�E�[�ł͂Ȃ������[�ł���ꍇ
				mapMove(m, c, d, 0, -1, floor);
				charaMove(c, d, 1, 0, floor);
			}
			else if (c->x == MAP_WIDTH) {					//���[�ł͂Ȃ����E�[�ł���ꍇ
				mapMove(m, c, d, -1, 0, floor);
				charaMove(c, d, 0, 1, floor);
			}
			else {
				charaMove(c, d, 1, 1, floor);
				if(!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
			
		}

		/*LeftUp*/
		else if (!menuflag && keyState[KEY_INPUT_Q] == 1) {		//���j���[���J���Ă��炸�AQ�L�[��������
			if (c->y == CHIP_SIZE * 2 && c->x == CHIP_SIZE * 2) {		//����[�ɂ���ꍇ
				if (m->y == 0) {							//�}�b�v������ȏ��ɍs���Ȃ��ꍇ
					mapMove(m, c, d, 1, 0, floor);
				}
				else if (m->x == 0) {						//�}�b�v������ȏ㍶�ɍs���Ȃ��ꍇ 
					mapMove(m, c, d, 0, 1, floor);
				}
				else if (m->y == 0 && m->x == 0) {			//�}�b�v������ȏ��ɂ����ɂ��s���Ȃ��ꍇ
					//�������Ȃ�
				} 
				else {
					mapMove(m, c, d, 1, 1, floor);
				}
			}
			else if (c->y == CHIP_SIZE * 2) {							//���[�ł͂Ȃ�����[�ɂ���ꍇ		
				if (m->y != 0) {							//�}�b�v���܂���ɍs����ꍇ
					mapMove(m, c, d, 0, 1, floor);
					charaMove(c, d, -1, 0,floor);
				}
				else {
					charaMove(c, d, -1, 0, floor);
				}
			}
			else if (c->x == CHIP_SIZE * 2) {							//��[�ł͂Ȃ������[�ɂ���ꍇ
				if (m->x != 0) {							//�}�b�v���܂����ɍs����ꍇ
					mapMove(m, c, d, 1, 0, floor);
					charaMove(c,d,0,-1,floor);
				}
				else {
					charaMove(c, d, 0, -1, floor);
				}
			}
			else {
				charaMove(c, d, -1, -1, floor);
				if(!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
		}

		/*LeftDown*/
		else if (!menuflag && keyState[KEY_INPUT_Z] == 1) {
			if (c->y ==  MAP_HEIGHT && c->x == CHIP_SIZE * 2) {				//�}�b�v�̍����[�ɂ���ꍇ
				if (m->x == 0) {											//�}�b�v������ȏ㍶�ɍs���Ȃ��ꍇ
					mapMove(m, c, d, 0, -1, floor);
					charaMove(c, d, -1, 0, floor);
				}
				else {
					mapMove(m, c, d, 1, -1, floor);
				}
			}
			else if (c->y == MAP_HEIGHT) {									//�}�b�v�̍��[�łȂ������[�ɂ���ꍇ
				mapMove(m, c, d, 0, -1, floor);
				charaMove(c, d, -1, 0, floor);
			}
			else if (c->x == CHIP_SIZE * 2) {								//�}�b�v�̉��[�łȂ������[�ɂ���ꍇ
				if (m->x != 0) {											//�}�b�v���܂����ɍs����ꍇ
					mapMove(m, c, d, 1, 0, floor);
					charaMove(c, d, 0, 1,floor);
				}
				else {
					charaMove(c, d, 0, 1, floor);
				}
			}
			else {
				charaMove(c, d, -1, 1, floor);
				if(!keyState[KEY_INPUT_Y])enemyMove(d, floor);
			}
		}


		/*
		if (!menuflag && !keyState[KEY_INPUT_Y]) {
			if (keyState[KEY_INPUT_Q] == 1 || keyState[KEY_INPUT_W] == 1 || keyState[KEY_INPUT_] == 1 || keyState[KEY_INPUT_DOWN] == 1){
				if(!(c->x == CHIP_SIZE * 2||c->x == MAP_WIDTH||c->y == CHIP_SIZE * 2 || c->y == MAP_HEIGHT) || !isNearPokemon(c,d))
					enemyMove(d,floor);
			}
		}
		*/

		/*�K�i�ړ�����*/
		if (nearCell[CENTER] == 100) {
			floor += 1;
			wait(2000,(char*)(floor+1));
		}

		if (nearCell[CENTER] == 101) {
			floor -= 1;
			wait(2000,(char*)(floor+1));
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
	d->name = "�_�[�N���C";

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

	d->moveTexture[DOWN][0] = LoadGraph("�摜/�_�[�N���Cd_1.png");
	d->moveTexture[DOWN][1] = LoadGraph("�摜/�_�[�N���Cd_2.png");
	d->moveTexture[UP][0] = LoadGraph("�摜/�_�[�N���Cu_1.png");
	d->moveTexture[UP][1] = LoadGraph("�摜/�_�[�N���Cu_2.png");
	d->moveTexture[LEFT][0] = LoadGraph("�摜/�_�[�N���Cl_1.png");
	d->moveTexture[LEFT][1] = LoadGraph("�摜/�_�[�N���Cl_2.png");
	d->moveTexture[RIGHT][0] = LoadGraph("�摜/�_�[�N���Cr_1.png");
	d->moveTexture[RIGHT][1] = LoadGraph("�摜/�_�[�N���Cr_2.png");

	d->skill[0].name = "�ł񂱂�������";
	d->skill[1].name = "���܂�����";
	d->skill[2].name = "�����̂͂ǂ�";
	d->skill[3].name = "�ꂢ�Ƃ��r�[��";

	d->skill[0].value = 2;
	d->skill[1].value = 7;
	d->skill[2].value = 10;
	d->skill[3].value = 3;


	d->skill[0].maxCount = 20;
	d->skill[1].maxCount = 10;
	d->skill[2].maxCount = 20;
	d->skill[3].maxCount = 10;

	d->skill[0].count = c->skill[0].maxCount;
	d->skill[1].count = c->skill[1].maxCount;
	d->skill[2].count = c->skill[2].maxCount;
	d->skill[3].count = c->skill[3].maxCount;

	d->voice = LoadSoundMem("���y/�_�[�N���Cvoice.mp3");

	d->experience = 10000;

	d->maxHp = 70;
	d->hp = 70;

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

	d->x = CHIP_SIZE * 10;
	d->y = CHIP_SIZE * 2;


	/*���������[�h*/
	slap = LoadSoundMem("���y/slap1.mp3");
	bgm = LoadSoundMem("���y/bgm.mp3");
	down = LoadSoundMem("���y/down1.mp3");

	load = LoadGraph("�摜/load.png");

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

	d->skill[0].min = 2;
	d->skill[0].max = 4;
	d->skill[1].min = 3;
	d->skill[1].max = 6;
	d->skill[2].min = 8;
	d->skill[2].max = 14;
	d->skill[3].min = 4;
	d->skill[3].max = 8;
}


/*attack(����,�G,�U���̎��)*/
void attack(pokemon* me, pokemon* enemy, int attackNum) {

	//turnToPokemon(me, enemy);//�G�̕�������
	int value = getRandom(me->skill[attackNum].min, me->skill[attackNum].max);	//�킴���o�����тɗ�������
	//�ȂȂ߂ɋ��鎞�͍U�����Ȃ�
	if (!(((me->x - CHIP_SIZE == enemy->x) && (me->y + CHIP_SIZE == enemy->y || me->y - CHIP_SIZE == enemy->y)) || (me->x + CHIP_SIZE == enemy->x) && (me->y + CHIP_SIZE == enemy->y || me->y - CHIP_SIZE == enemy->y))) {
		//�G�̕��������Ă���ꍇ
		if ((me->x > enemy->x && me->direction == LEFT) || (me->x < enemy->x && me->direction == RIGHT) || (me->y > enemy->y && me->direction == UP) || (me->y < enemy->y && me->direction == DOWN)) {
			if (me->skill[attackNum].count > 0) {

				/*�m���ōU�����O���*/
				if (getRandom(1, 100) < 98) {
					enemy->hp -= value;
					if (enemy->hp < 0)enemy->hp = 0;//hp���}�C�i�X�ɂȂ�̂�h��
					sprintf_s(s, "%s��%s! %s��%d�̃_���[�W!%s��HP:%d", me->name, me->skill[attackNum].name, enemy->name, value, enemy->name, enemy->hp);
					PlaySoundMem(slap, DX_PLAYTYPE_BACK);
				}
				else {
					sprintf_s(s, "%s��%s!�������U���͊O�ꂽ", me->name, me->skill[attackNum].name);
					PlaySoundMem(slap, DX_PLAYTYPE_BACK);
				}
			}
			else {
				sprintf_s(s, "%s�͂����g���Ȃ�!", me->skill[attackNum].name);
			}
			me->skill[attackNum].count -= 1;
			if (me->skill[attackNum].count < 0)me->skill[attackNum].count = 0;	//�}�C�i�X��h��
			messageflag = true;
			setMessage(s);
			outMessage();
		}
		//�G�̕��������Ă��Ȃ��ꍇ
		else {
			attack_for(me, attackNum);
		}
	}


}
//�v���C���[�U���p,�G������ɂ��炸�U�����K���O���ꍇ
void attack_for(pokemon* me, int attackNum) {

	if (me->skill[attackNum].count > 0) {

		/*�U�����O���*/
		sprintf_s(s, "%s��%s!�������U���͊O�ꂽ", me->name, me->skill[attackNum].name);
		PlaySoundMem(slap, DX_PLAYTYPE_BACK);
	}
	else {
		sprintf_s(s, "%s�͂����g���Ȃ�!", me->skill[attackNum].name);
	}
	me->skill[attackNum].count -= 1;
	if (me->skill[attackNum].count < 0)me->skill[attackNum].count = 0;	//�}�C�i�X��h��
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
bool isNearPokemon(pokemon* me, pokemon* enemy) {
	if ((me->x - CHIP_SIZE <= enemy->x) && (me->x + CHIP_SIZE >= enemy->x) && (me->y - CHIP_SIZE <= enemy->y) && (me->y + CHIP_SIZE >= enemy->y)) {
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
		return TRUE;
	}
	return FALSE;
}


/*�G�̓���*/
void enemyMove(pokemon* enemy,int floor) {

	/*�G�������}�b�v���ɂ���ƁA�����Ɍ������Ă���*/
	if (findPokemon(enemy, c)) {
		/*�U�����Ȃ�*/
		/*�ړ�����(A*�A���S���Y������Ɏg�p)*/
		if (!isNearPokemon(enemy, c) && enemy->isLive) {

			if (c->x != enemy->x && c->y != enemy->y && c->x < enemy->x && c->y < enemy->y) {
				charaMove(d, -1, -1,floor);
			}
			else if (c->x != enemy->x && c->y != enemy->y && c->x < enemy->x && c->y > enemy->y) {
				charaMove(d, -1, 1,floor);
			}
			else if (c->x != enemy->x && c->y != enemy->y && c->x > enemy->x && c->y < enemy->y) {
				charaMove(d, 1, -1,floor);
			}
			else if (c->x != enemy->x && c->y != enemy->y && c->x > enemy->x && c->y > enemy->y) {
				charaMove(d, 1, 1,floor);
			}
			else if (c->x != enemy->x && c->x < enemy->x) {
				charaMove(d, -1, 0,floor);
			}
			else if (c->x != enemy->x && c->x > enemy->x) {
				charaMove(d, 1, 0,floor);
			}
			else if (c->y != enemy->y && c->y < enemy->y) {
				charaMove(d, 0, -1,floor);
			}
			else if (c->y != enemy->y && c->y > enemy->y) {
				charaMove(d, 0, 1,floor);
			}
		}
		/*�U������*/
		else if (isNearPokemon(enemy, c) && c->hp > 0 && enemy->isLive) {
			turnToPokemon(enemy, c);
			attack(enemy, c, getRandom(0,3));		//�����_���ł킴��I��
		}
	}
	/*�܂��������������Ă��Ȃ��ꍇ�A���낤�낷��*/
	else {
		switch (getRandom(0,8)) {
		case LEFT:
			charaMove(enemy, -1, 0,floor);
			break;
		case RIGHT:
			charaMove(enemy, 1, 0,floor);
			break;
		case UP:
			charaMove(enemy, 0, -1,floor);
			break;
		case DOWN:
			charaMove(enemy, 0, 1,floor);
			break;
		case LEFT_UP:
			charaMove(enemy, -1, -1,floor);
			break;
		case LEFT_DOWN:
			charaMove(enemy, -1, 1,floor);
			break;
		case RIGHT_UP:
			charaMove(enemy, 1, -1,floor);
			break;
		case RIGHT_DOWN:
			charaMove(enemy, 1, 1,floor);
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
void charaMove(pokemon* me,pokemon* enemy, int x, int y,int floor) {

	if (x == 1)setDirection(me,RIGHT);
	else if(x == -1)setDirection(me,LEFT);

	if (y == 1)setDirection(me,DOWN);
	else if(y == -1)setDirection(me,UP);

	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[floor][me->y / CHIP_SIZE - m->y + y][me->x  / CHIP_SIZE - m->x + x];

	/*�ȂȂ߈ړ��̂Ƃ�*/
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {

		int nextCell_x = mapping[floor][me->y / CHIP_SIZE - m->y][me->x / CHIP_SIZE - m->x + x];	//�����̍��E�ǂ��炩�̃Z���̏��
		int nextCell_y = mapping[floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x];	//�����̏㉺�ǂ��炩�̃Z���̏��

		//�i�ސ悪��Q���Ȃ�
		if (nextCell <= 0 && !keyState[KEY_INPUT_Y]) {
			if (nextCell_x > 0 && nextCell_y <=0)me->x += x * CHIP_SIZE;
			if (nextCell_y > 0 && nextCell_x <=0)me->y += y * CHIP_SIZE;
		}
	}

	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		/*�ړ���ɓG�����������ւ��*/
		if (me->x + x * CHIP_SIZE == enemy->x && me->y + y * CHIP_SIZE == enemy->y) { enemy->x = me->x; enemy->y = me->y; }
		me->x += x * CHIP_SIZE;
		me->y += y * CHIP_SIZE;
	}
}

/*�G�p�̏���,����ւ�菈���𖳂�����*/
void charaMove(pokemon* me, int x, int y, int floor) {

	if (x == 1)setDirection(me, RIGHT);
	else if (x == -1)setDirection(me, LEFT);

	if (y == 1)setDirection(me, DOWN);
	else if (y == -1)setDirection(me, UP);

	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[floor][me->y / CHIP_SIZE - m->y + y][me->x / CHIP_SIZE - m->x + x];


	if (nextCell > 0) {
		me->x += x * CHIP_SIZE;
		me->y += y * CHIP_SIZE;
	}
}

void mapMove(map* m,pokemon* me,pokemon* enemy, int x, int y, int floor) {

	if (x == -1)setDirection(me,RIGHT);
	else if(x == 1)setDirection(me,LEFT);

	if (y == -1)setDirection(me,DOWN);
	else if(y == 1)setDirection(me,UP);

	int nextCell = mapping[floor][me->y / CHIP_SIZE - m->y - y][me->x  / CHIP_SIZE - m->x - x];
	
	//�}�b�v���ȂȂ߂Ɉړ�����Ƃ�
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {
		int nextCell_x = mapping[floor][me->y / CHIP_SIZE - m->y][me->x / CHIP_SIZE - m->x - x];
		int nextCell_y = mapping[floor][me->y / CHIP_SIZE - m->y - y][me->x / CHIP_SIZE - m->x];

		if (nextCell <= 0 && !keyState[KEY_INPUT_Y]) {
			if (nextCell_x > 0) { 
				m->x += x;
				int enemyCell = mapping[floor][enemy->y / CHIP_SIZE - m->y][enemy->x / CHIP_SIZE - m->x];
				if (enemyCell <= 0)charaMove(enemy, x, 0, floor);
			}
			if (nextCell_y > 0) { 
				m->y += y; 
				int enemyCell = mapping[floor][enemy->y / CHIP_SIZE - m->y][enemy->x / CHIP_SIZE - m->x];
				if (enemyCell <= 0)charaMove(enemy, 0, y, floor);
			}
		}
	}

	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		m->x += x;
		m->y += y;
		int enemyCell = mapping[floor][enemy->y / CHIP_SIZE - m->y][enemy->x / CHIP_SIZE - m->x];
		if (enemyCell <= 0)charaMove(enemy,x,y,floor);
	}

}

void setDirection(pokemon* me, int direction) {
	me->direction = direction;
}