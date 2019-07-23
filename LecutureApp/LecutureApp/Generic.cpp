#pragma once
#include "all.h"
#include <random>
#include "Map.cpp"
#include "Character.cpp"

char keyState[256];			//������Ă���L�[���i�[

/*�����t�@�C���������p�z��*/
int slap;
int bgm;
int down;

/*�摜�t�@�C���������p�z��*/
int skillBox;
int stairs_down;
int stairs_up;
int load;
int load2;

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

void w_press() {
	while (getCountFrame() == 0) {
		if (keyState[KEY_INPUT_K] == 1) {
			break;
		}
	}
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
	for (int i = 0; i < FLOORNUM - 1; i++) {
		enemy[i][0]->name = "�_�[�N���C";
		enemy[i][1]->name = "�t�V�M�_�l";
		enemy[i][2]->name = "�X�C�N��";
	}

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
	for (int i = 0; i < FLOORNUM - 1; i++) {
		enemy[i][0]->moveTexture[DOWN][0] = LoadGraph("�摜/�_�[�N���Cd_1.png");
		enemy[i][0]->moveTexture[DOWN][1] = LoadGraph("�摜/�_�[�N���Cd_2.png");
		enemy[i][0]->moveTexture[UP][0] = LoadGraph("�摜/�_�[�N���Cu_1.png");
		enemy[i][0]->moveTexture[UP][1] = LoadGraph("�摜/�_�[�N���Cu_2.png");
		enemy[i][0]->moveTexture[LEFT][0] = LoadGraph("�摜/�_�[�N���Cl_1.png");
		enemy[i][0]->moveTexture[LEFT][1] = LoadGraph("�摜/�_�[�N���Cl_2.png");
		enemy[i][0]->moveTexture[RIGHT][0] = LoadGraph("�摜/�_�[�N���Cr_1.png");
		enemy[i][0]->moveTexture[RIGHT][1] = LoadGraph("�摜/�_�[�N���Cr_2.png");

		enemy[i][0]->skill[0].name = "�ł񂱂�������";
		enemy[i][0]->skill[1].name = "���܂�����";
		enemy[i][0]->skill[2].name = "�����̂͂ǂ�";
		enemy[i][0]->skill[3].name = "�ꂢ�Ƃ��r�[��";

		enemy[i][0]->skill[0].value = 2;
		enemy[i][0]->skill[1].value = 7;
		enemy[i][0]->skill[2].value = 10;
		enemy[i][0]->skill[3].value = 3;


		enemy[i][0]->skill[0].maxCount = 20;
		enemy[i][0]->skill[1].maxCount = 10;
		enemy[i][0]->skill[2].maxCount = 20;
		enemy[i][0]->skill[3].maxCount = 10;

		enemy[i][0]->skill[0].count = c->skill[0].maxCount;
		enemy[i][0]->skill[1].count = c->skill[1].maxCount;
		enemy[i][0]->skill[2].count = c->skill[2].maxCount;
		enemy[i][0]->skill[3].count = c->skill[3].maxCount;

		enemy[i][0]->voice = LoadSoundMem("���y/�_�[�N���Cvoice.mp3");

		enemy[i][0]->experience = 10000;

		enemy[i][0]->maxHp = 70;
		enemy[i][0]->hp = 70;

		enemy[i][1]->moveTexture[DOWN][0] = LoadGraph("�摜/�t�V�M�_�ld_1.png");
		enemy[i][1]->moveTexture[DOWN][1] = LoadGraph("�摜/�t�V�M�_�ld_2.png");
		enemy[i][1]->moveTexture[UP][0] = LoadGraph("�摜/�t�V�M�_�lu_1.png");
		enemy[i][1]->moveTexture[UP][1] = LoadGraph("�摜/�t�V�M�_�lu_2.png");
		enemy[i][1]->moveTexture[LEFT][0] = LoadGraph("�摜/�t�V�M�_�ll_1.png");
		enemy[i][1]->moveTexture[LEFT][1] = LoadGraph("�摜/�t�V�M�_�ll_2.png");
		enemy[i][1]->moveTexture[RIGHT][0] = LoadGraph("�摜/�t�V�M�_�lr_1.png");
		enemy[i][1]->moveTexture[RIGHT][1] = LoadGraph("�摜/�t�V�M�_�lr_2.png");

		enemy[i][1]->skill[0].name = "�͂��σJ�b�^�[";
		enemy[i][1]->skill[1].name = "�ł񂱂�������";
		enemy[i][1]->skill[2].name = "�����̂͂ǂ�";
		enemy[i][1]->skill[3].name = "����������";

		enemy[i][1]->skill[0].value = 5;
		enemy[i][1]->skill[1].value = 10;
		enemy[i][1]->skill[2].value = 4;
		enemy[i][1]->skill[3].value = 11;


		enemy[i][1]->skill[0].maxCount = 10;
		enemy[i][1]->skill[1].maxCount = 5;
		enemy[i][1]->skill[2].maxCount = 10;
		enemy[i][1]->skill[3].maxCount = 10;

		enemy[i][1]->skill[0].count = c->skill[0].maxCount;
		enemy[i][1]->skill[1].count = c->skill[1].maxCount;
		enemy[i][1]->skill[2].count = c->skill[2].maxCount;
		enemy[i][1]->skill[3].count = c->skill[3].maxCount;

		enemy[i][1]->voice = LoadSoundMem("���y/�t�V�M�_�lvoice.mp3");

		enemy[i][1]->experience = 10000;

		enemy[i][1]->maxHp = 70;
		enemy[i][1]->hp = 70;

		enemy[i][2]->moveTexture[DOWN][0] = LoadGraph("�摜/�X�C�N��d_1.png");
		enemy[i][2]->moveTexture[DOWN][1] = LoadGraph("�摜/�X�C�N��d_2.png");
		enemy[i][2]->moveTexture[UP][0] = LoadGraph("�摜/�X�C�N��u_1.png");
		enemy[i][2]->moveTexture[UP][1] = LoadGraph("�摜/�X�C�N��u_2.png");
		enemy[i][2]->moveTexture[LEFT][0] = LoadGraph("�摜/�X�C�N��l_1.png");
		enemy[i][2]->moveTexture[LEFT][1] = LoadGraph("�摜/�X�C�N��l_2.png");
		enemy[i][2]->moveTexture[RIGHT][0] = LoadGraph("�摜/�X�C�N��r_1.png");
		enemy[i][2]->moveTexture[RIGHT][1] = LoadGraph("�摜/�X�C�N��r_2.png");

		enemy[i][2]->skill[0].name = "�݂��ł��ۂ�";
		enemy[i][2]->skill[1].name = "�n�C�h���|���v";
		enemy[i][2]->skill[2].name = "�����̂͂ǂ�";
		enemy[i][2]->skill[3].name = "����";

		enemy[i][2]->skill[0].value = 5;
		enemy[i][2]->skill[1].value = 10;
		enemy[i][2]->skill[2].value = 4;
		enemy[i][2]->skill[3].value = 11;


		enemy[i][2]->skill[0].maxCount = 10;
		enemy[i][2]->skill[1].maxCount = 5;
		enemy[i][2]->skill[2].maxCount = 10;
		enemy[i][2]->skill[3].maxCount = 10;

		enemy[i][2]->skill[0].count = c->skill[0].maxCount;
		enemy[i][2]->skill[1].count = c->skill[1].maxCount;
		enemy[i][2]->skill[2].count = c->skill[2].maxCount;
		enemy[i][2]->skill[3].count = c->skill[3].maxCount;

		enemy[i][2]->voice = LoadSoundMem("���y/�X�C�N��voice.mp3");

		enemy[i][2]->experience = 10000;

		enemy[i][2]->maxHp = 70;
		enemy[i][2]->hp = 70;
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

	randomEnemyPut(enemy[m->floor]);

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

	for (int j = 0; j < FLOORNUM - 1; j++) {
		for (int i = 0; i < ENEMYNUM; i++) {
			enemy[j][i]->skill[0].min = 2;
			enemy[j][i]->skill[0].max = 4;
			enemy[j][i]->skill[1].min = 3;
			enemy[j][i]->skill[1].max = 6;
			enemy[j][i]->skill[2].min = 8;
			enemy[j][i]->skill[2].max = 14;
			enemy[j][i]->skill[3].min = 4;
			enemy[j][i]->skill[3].max = 8;
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

