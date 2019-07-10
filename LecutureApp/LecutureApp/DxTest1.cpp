#include "DxLib.h"
#include "pokemon.h"
#include <iostream>
#include <random>

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (600)                          // ��ʂ̏c��
#define CHIP_SIZE        (40)                           // ��̃`�b�v�̃T�C�Y
#define MAP_HEIGHT		 (400)
#define MAP_WIDTH		 (720)
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

/*�����t�@�C���������p�z��*/
int slap;
int bgm;
int down;

/*�摜�t�@�C���������p�z��*/
int messageBox;
int skillBox;

int attackNum;

/*�v���g�^�C�v�錾*/
int init();
void attack(pokemon*, pokemon*, int);			//�U��
void turnToPokemon(pokemon*, pokemon*);			//�|�P�����̕�������
void moveJump(pokemon*);						//Jump����
void initConsole();								//���b�Z�[�W�{�b�N�X������������
void setMessage(char[]);						//�\�����������b�Z�[�W���Z�b�g����
void outMessage();								//���b�Z�[�W��\������
bool isNearPokemon(pokemon*, pokemon*);			//�G���߂��ɂ�����(�U�������ɂ�����)true
bool findPokemon(pokemon*, pokemon*);
void enemyMove(pokemon*);						//�G�̓���
int getRandom(int,int);

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


/***********************      Main�̏���      *********************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	/*����������*/
	if (init() == -1) { return -1; }

	int d_num = 0;
	int tempTime = 0;

	/*���F���i�[*/
	const int white = GetColor(255, 255, 255);

	/*bgm�Đ��J�n*/
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	/*�`�悷��*/
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

		/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
		if (GetNowCount() - tempTime> 500) 
		{	
			if (d_num == 1)d_num = 0;
			else d_num = 1;
			tempTime = GetNowCount(); 
		}

		/*�K�w�Alevel�AHP�\��(�Œ�)*/
		DrawFormatString(0	, 0, white, "B1F");
		DrawFormatString(50	, 0, white, "Lv: %d",c->level);
		DrawFormatString(120, 0, white, "HP: %d/ %d",c->hp,c->maxHp);
		DrawFormatString(220, 0, white, "�Z�b�g�킴�� : %s",c->skill[attackNum].name);
		/*�m�F�p���W(���Ƃŏ���)*/
		DrawFormatString(500, 0, white, "�s�J���W(%d,%d)", c->x, c->y);
		DrawFormatString(500, 20,white, "�_�[���W(%d,%d)",d->x,d->y );

		/*DrawRotaGraph(x���W,y���W,�k�ړx,�p�x,�`�悷��摜�n���h��,�w�i���ߏ�����ON,OFF)*/
		/*���W�͉摜�̐^�񒆂Ɏ���*/
		DrawRotaGraph(c->x, c->y, 1.5, 0, c->moveTexture[c->direction][d_num], true);
		/*�����Ă���G�\��*/
		if (d->isLive) { DrawRotaGraph(d->x, d->y, 1.5, 0, d->moveTexture[d->direction][d_num], true); }

		/*���b�Z�[�W�o��*/
		outMessage();

		/*q�L�[�ŏI���*/
		if (keyState[KEY_INPUT_Q] == 1) { endflag = true; }
		
		/*�킴�\������*/
		if (menuflag && keyState[KEY_INPUT_I] == 1) {
			menuflag = false;
		}

		/*�킴�\��\��*/
		else if (!menuflag && keyState[KEY_INPUT_I] == 1) {
			menuflag = true;
		}

		/*Attack*/
		if (!jump && !menuflag && keyState[KEY_INPUT_Z] == 1) {
			/*�G�̂�������Ɍ�����ς���*/
			if (isNearPokemon(c, d) && d->isLive) {
				attack(c, d, attackNum);
			}
			enemyMove(d);
		}

		/*�΂߈ړ��������Ȃ�else if����Ȃ���if�����ɂ���*/
		/*�����������ΓG������*/
		/*Right*/
		else if (!menuflag && keyState[KEY_INPUT_RIGHT]==1) {
			c->direction = RIGHT;
			if (!keyState[KEY_INPUT_Y] && c->x < MAP_WIDTH && (!(d->x == c->x + CHIP_SIZE && d->y == c->y)||!d->isLive)) {
					c->x += CHIP_SIZE;
			}
		}

		/*Left*/
		else if (!menuflag && keyState[KEY_INPUT_LEFT]==1) { 
			c->direction = LEFT;
			if (!keyState[KEY_INPUT_Y] &&  c->x > CHIP_SIZE * 2 && (!(d->x == c->x - CHIP_SIZE && d->y == c->y)||!d->isLive)) {
				c->x-=CHIP_SIZE;
			}
		}

		/*Up*/
		if (!menuflag && !jump && keyState[KEY_INPUT_UP]==1) {
			c->direction = UP;
			if (!keyState[KEY_INPUT_Y] && c->y > CHIP_SIZE * 2 && (!(d->y == c->y - CHIP_SIZE && d->x == c->x)||!d->isLive)) {
				c->y-=CHIP_SIZE;
			}
		}

		/*Down*/
		else if (!menuflag && !jump && keyState[KEY_INPUT_DOWN]==1) {
			c->direction = DOWN;
			if (!keyState[KEY_INPUT_Y] && c->y < MAP_HEIGHT && (!(d->y == c->y + CHIP_SIZE && d->x == c->x)||!d->isLive)) {
				c->y+=CHIP_SIZE;
			}
		}

		if (!menuflag && !keyState[KEY_INPUT_Y]) {
			if (keyState[KEY_INPUT_RIGHT] == 1 || keyState[KEY_INPUT_LEFT] == 1 || keyState[KEY_INPUT_UP] == 1 || keyState[KEY_INPUT_DOWN] == 1){
				if(!(c->x == CHIP_SIZE * 2||c->x == MAP_WIDTH||c->y == CHIP_SIZE * 2 || c->y == MAP_HEIGHT) || !isNearPokemon(c,d))
					enemyMove(d);
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

		if (menuflag) {
			DrawRotaGraph(550, 160, 1, 0, skillBox, true);
			DrawFormatString(530, 98,  white, "%s (%d/%d)", c->skill[0].name, c->skill[0].count, c->skill[0].maxCount);
			DrawFormatString(530, 149, white, "%s (%d/%d)", c->skill[1].name, c->skill[1].count, c->skill[1].maxCount);
			DrawFormatString(530, 199, white, "%s (%d/%d)", c->skill[2].name, c->skill[2].count, c->skill[2].maxCount);
			DrawFormatString(530, 250, white, "%s (%d/%d)", c->skill[3].name, c->skill[3].count, c->skill[3].maxCount);
			if (keyState[KEY_INPUT_1]) { attackNum = 0; menuflag = false; }
			else if (keyState[KEY_INPUT_2]) { attackNum = 1; menuflag = false;}
			else if (keyState[KEY_INPUT_3]) { attackNum = 2; menuflag = false;}
			else if (keyState[KEY_INPUT_4]) { attackNum = 3; menuflag = false;}
		}

		if (endflag) {
			break;
		}
	}

	DxLib::DxLib_End();    // DX���C�u�����I������
	
	return 0;
}



int init() {
	/*�E�C���h�E�̑傫���w��*/
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
	/*�w�i�F�`��(��Ƀ}�b�v)*/
	SetBackgroundColor(100, 100, 100);
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


	d->maxHp = 70;
	d->hp = 70;

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

}

/*attack(����,�G,�U���̎��)*/
void attack(pokemon* me, pokemon* enemy, int attackNum) {

	turnToPokemon(me, enemy);//�G�̕�������
	
	//�ȂȂ߂ɋ��鎞�͍U�����Ȃ�
	if (!(((me->x - CHIP_SIZE == enemy->x) && (me->y + CHIP_SIZE == enemy->y || me->y - CHIP_SIZE == enemy->y)) || (me->x + CHIP_SIZE == enemy->x) && (me->y + CHIP_SIZE == enemy->y || me->y - CHIP_SIZE == enemy->y))) {
		if (me->skill[attackNum].count > 0) {

			/*�m���ōU�����O���*/
			if (getRandom(1, 100) < 98) {
				enemy->hp -= me->skill[attackNum].value;
				if (enemy->hp < 0)enemy->hp = 0;//hp���}�C�i�X�ɂȂ�̂�h��
				sprintf_s(s, "%s��%s! %s��%d�̃_���[�W!%s��HP:%d", me->name, me->skill[attackNum].name, enemy->name, me->skill[attackNum].value, enemy->name, enemy->hp);
				PlaySoundMem(slap, DX_PLAYTYPE_BACK);
			}
			else {
				sprintf_s(s, "%s�̍U���͊O�ꂽ!", me->name);
			}
		}
		else {
			sprintf_s(s, "%s�͂����g���Ȃ�!",me->skill[attackNum].name);
		}
		me->skill[attackNum].count -= 1;
		if (me->skill[attackNum].count < 0)me->skill[attackNum].count = 0;	//�}�C�i�X��h��
		messageflag = true;
		setMessage(s);
		outMessage();
	}
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

/*�G�̓���*/
void enemyMove(pokemon* enemy) {


	/*�����Ă��邩����ł��邩*/
	/*���S�m�F*/
	if (enemy->hp == 0 && enemy->isLive) {
		PlaySoundMem(down, DX_PLAYTYPE_BACK);
		c->experience += enemy->experience;
		sprintf_s(s, 256, "%s�͓|�ꂽ! �o���l%d���l��!", enemy->name,enemy->experience);
		setMessage(s);
		outMessage();
		enemy->isLive = false;
	}

	/*�G�������}�b�v���ɂ���ƁA�����Ɍ������Ă���*/
	if (findPokemon(enemy, c)) {
		/*�U�����Ȃ�*/
		/*�ړ�����*/
		if (!isNearPokemon(enemy, c) && enemy->isLive) {
			if (c->x != enemy->x && c->x - CHIP_SIZE < enemy->x) {
				enemy->x -= CHIP_SIZE;
				enemy->direction = LEFT;
			}
			else if (c->x != enemy->x && c->x + CHIP_SIZE > enemy->x) {
				enemy->x += CHIP_SIZE;
				enemy->direction = RIGHT;
			}
			if (c->y != enemy->y && c->y - CHIP_SIZE < enemy->y) {
				enemy->y -= CHIP_SIZE;
				enemy->direction = UP;
			}
			else if (c->y != enemy->y && c->y + CHIP_SIZE > enemy->y) {
				enemy->y += CHIP_SIZE;
				enemy->direction = DOWN;
			}
		}
		/*�U������*/
		else if (c->hp > 0 && enemy->isLive) {
			attack(enemy, c, getRandom(0,3));		//�����_���ł킴��I��
		}
	}
	/*�܂��������������Ă��Ȃ��ꍇ�A���낤�낷��*/
	else {
		switch (getRandom(0,3)) {
		case 0:
			enemy->x -= CHIP_SIZE;
			enemy->direction = LEFT;
			break;
		case 1:
			enemy->x += CHIP_SIZE;
			enemy->direction = RIGHT;
			break;
		case 2:
			enemy->y -= CHIP_SIZE;
			enemy->direction = UP;
			break;
		case 3:
			enemy->y += CHIP_SIZE;
			enemy->direction = DOWN;
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
