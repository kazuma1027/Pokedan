#include "DxLib.h"
#include "pokemon.h"

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (400)                          // ��ʂ̏c��
#define CHIP_SIZE        (48)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // �}�b�v�̏c��

/*������Ă���L�[���i�[*/
char keyState[256];
char s[256];
/*�_���[�W��^�������^���Ă��Ȃ���*/
bool damage = false;

bool messageflag = false;

/*�W�����v�p�ϐ�*/
int temp = 0;
int y_temp = 0;
int y_prev = 0;

/*�W�����v�p�t���O*/
bool onGround = false;		//�W�����v����u��
bool jump = false;			//�W�����v���Ă��邩�ǂ���	

/*�R���\�[���\���p�ϐ�*/
char message1[1024];
char message2[1024];
char message3[1024];

/*�|�P�����\����*/
pokemon poke;
pokemon dark;
pokemon* c = &poke;
pokemon* d = &dark;

/*�����t�@�C���������p�z��*/
int slap;
int bgm;
int down;

void turnToPokemon(pokemon *me,pokemon *enemy ) {
	if (me->x > enemy->x)me->direction = LEFT;
	else if (me->x < enemy->x)me->direction = RIGHT;
	if (me->y > enemy->y)me->direction = UP;
	else if (me->y < enemy->y)me->direction = DOWN;
}

void initConsole() {

	/*���F�̓���*/
	SetTransColor(255, 255, 255);

	/*���b�Z�[�W�{�b�N�X*/
	int messageBox = LoadGraph("�摜/messageBox.png");

	/*���b�Z�[�W�t���O�������Ă���΁A���b�Z�[�W�{�b�N�X�\��*/
	if (messageflag) {
		DrawRotaGraph(SCREEN_WIDTH / 2, 300, 1, 0, messageBox, true);
	}
}


void setMessage(char s[]) {

	char temp[1024];
	/*������*/
	for (int i = 0; i < 1024; i++)temp[i] = '\0';

	/*������R�s�[*/
	for (int i = 0; s[i] != '\0'; i++) { temp[i] = s[i]; }

	/*message1->��i�Amessage2->���i�Amessage3->���i*/
	if (message1[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message1[i] = temp[i]; }
	else if (message2[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message2[i] = temp[i]; }
	else if (message3[0] == '\0')for (int i = 0; temp[i] != '\0'; i++) { message3[i] = temp[i]; }
	/*�S�Ė��܂��Ă���΁A���e����i���グ�ĕ\������*/
	else {
		for (int i = 0; i < 1024; i++) { message1[i] = '\0'; }
		for (int i = 0; i < 1024; i++) { message1[i] = message2[i]; }

		for (int i = 0; i < 1024; i++)message2[i] = '\0';
		for (int i = 0; i < 1024; i++) { message2[i] = message3[i]; }

		for (int i = 0; i < 1024; i++) { message3[i] = temp[i]; }
	}
}


void outMessage() {

	messageflag = true;

	initConsole();
	/*�R���\�[���\��*/
	DrawFormatString(160, 287, GetColor(255, 255, 255), "%s", message1);
	DrawFormatString(160, 317, GetColor(255, 255, 255), "%s", message2);
	DrawFormatString(160, 347, GetColor(255, 255, 255), "%s", message3);
}

/*�W�����v����*/
void moveJump() {

	int f;
	/*�W�����v�����u��*/
	if (onGround) {
		/*��ւ̓����蔻��*/
		if (c->y >= 140) {
			f = -30;
			y_temp = c->y;
			c->y += (c->y - y_prev) + f;
			y_prev = y_temp;
		}
		else {
			y_temp = 30;
			c->y = 30;
			y_prev = y_temp;
		}
	}
	/*�󒆂̏���*/
	else {
		f = 3;
		y_temp = c->y;
		c->y += (c->y - y_prev) + f;
		y_prev = y_temp;
		/*���̈ʒu�ɖ߂�΃W�����v�����I��*/
		if (c->y >= temp) {
			c->y = temp;
			jump = false;
		}
	}
	onGround = false;
}


/*�L�[��������Ă���t���[�����ɂ���ĕ\������摜��ύX����*/
/*
int getDnum(int key) {
	if (keyState[key] % 60 >= 1 && keyState[key] % 60 < 30) return 0;
	else return 1;
}
*/

/*���͂̃}�X�ɋ��邩���Ȃ���*/
bool isNearEnemy(pokemon* me,pokemon* enemy) {
	if ((me->x - CHIP_SIZE <= enemy->x) && (me->x + CHIP_SIZE >= enemy->x) && (me->y - CHIP_SIZE <= enemy->y) && (me->y + CHIP_SIZE >= enemy->y))return true;
	else return false;
}

/*�G�̓���*/
void enemyMove(pokemon* enemy) {
	

	/*�����Ă��邩����ł��邩*/
	if (enemy->isLive) {

		/*���S�m�F*/
		if (enemy->hp == 0 && enemy->isLive) { 
			PlaySoundMem(down, DX_PLAYTYPE_BACK); 
			sprintf_s(s, 1024, "%s�͓|�ꂽ!", enemy->name); 
			setMessage(s); 
			outMessage();
			enemy->isLive = false; 
		}

		/*�U�����Ȃ�*/
		/*�ړ�����*/
		if (!isNearEnemy(c, enemy)) {
			if (c->x!=enemy->x && c->x - CHIP_SIZE < enemy->x) {
					enemy->x -= CHIP_SIZE;
					enemy->direction = LEFT;
			}
			else if (c->x!=enemy->x && c->x + CHIP_SIZE > enemy->x) {
					enemy->x += CHIP_SIZE;
					enemy->direction = RIGHT;
			}
			if (c->y!=enemy->y && c->y - CHIP_SIZE < enemy->y) {
					enemy->y -= CHIP_SIZE;
					enemy->direction = UP;
			}
			else if (c->y!=enemy->y && c->y + CHIP_SIZE > enemy->y) {
					enemy->y += CHIP_SIZE;
					enemy->direction = DOWN;
			}
		}
		/*�U������*/
		else {
			turnToPokemon(enemy, c);
			if (c->hp > 0 && enemy->hp > 0) {
				c->hp -= 1;
				sprintf_s(s, "%s�̍U��!%s��%d�̃_���[�W!%s��HP:%d", enemy->name, c->name, enemy->attack[0], c->name, c->hp);
				messageflag = true;
				setMessage(s);
				outMessage();
				PlaySoundMem(slap, DX_PLAYTYPE_BACK);
			}
		}
	}
}

/*�L�[��������Ă���t���[�����𐔂���*/
int getCountFrame() {
	char tmpKey[256];								// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);						// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {						// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			keyState[i]++;							// ���Z
			if (keyState[i] == 60)keyState[i] = 1;	//�ړ����̉摜�����Ɏg�p
		}
		else {										// ������Ă��Ȃ����
			keyState[i] = 0;						// 0�ɂ���
		}
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

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

	d->moveTexture[DOWN][0] = LoadGraph("�摜/�_�[�N���Cd_1.png");
	d->moveTexture[DOWN][1] = LoadGraph("�摜/�_�[�N���Cd_2.png");
	d->moveTexture[UP][0] = LoadGraph("�摜/�_�[�N���Cu_1.png");
	d->moveTexture[UP][1] = LoadGraph("�摜/�_�[�N���Cu_2.png");
	d->moveTexture[LEFT][0] = LoadGraph("�摜/�_�[�N���Cl_1.png");
	d->moveTexture[LEFT][1] = LoadGraph("�摜/�_�[�N���Cl_2.png");
	d->moveTexture[RIGHT][0] = LoadGraph("�摜/�_�[�N���Cr_1.png");
	d->moveTexture[RIGHT][1] = LoadGraph("�摜/�_�[�N���Cr_2.png");
	

	/*���W�ʒu*/
	c->x = CHIP_SIZE*3;
	c->y = CHIP_SIZE*3;

	d->x = CHIP_SIZE*10;
	d->y = CHIP_SIZE*2;

	int d_num = 0;

	/*���������[�h*/
	slap = LoadSoundMem("���y/slap1.mp3");
	bgm = LoadSoundMem("���y/bgm.mp3");
	down = LoadSoundMem("���y/down1.mp3");

	/*�t���O*/
	bool endflag = false;		//q�������ƏI���

	int tempTime = 0;
	int currentTime = 0;


	currentTime = GetNowCount();

	/*bgm�Đ��J�n*/
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	/*�`�悷��*/
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

		/*500ms(0.5�b)�Ɉ�x�摜�X�V(�����Ă���悤�Ɍ�����)*/
		if (currentTime - tempTime> 500) 
		{	
			if (d_num == 1)d_num = 0;
			else d_num = 1;
			tempTime = GetNowCount(); 
		}

		currentTime = GetNowCount();

		/*�K�w�Alevel�AHP�\��(�Œ�)*/
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�s�J���W(%d,%d)", c->x, c->y);
		DrawFormatString(300, 20,GetColor(255, 255, 255), "�_�[���W(%d,%d)",d->x,d->y );
		DrawFormatString(0, 0, GetColor(255, 255, 255), "B1F");
		DrawFormatString(50, 0, GetColor(255, 255, 255), "Lv: %d",c->level);
		DrawFormatString(120, 0, GetColor(255, 255, 255), "HP: %d/ %d",c->hp,c->maxHp);
		

		/*DrawRotaGraph(x���W,y���W,�k�ړx,�p�x,�`�悷��摜�n���h��,�w�i���ߏ�����ON,OFF)*/
		/*���W�͉摜�̐^�񒆂Ɏ���*/
		DrawRotaGraph(c->x, c->y, 1.5, 0, c->moveTexture[c->direction][d_num], true);

		outMessage();

		/*�����Ă���G�\��*/
		if (d->hp > 0) { DrawRotaGraph(d->x, d->y, 1.5, 0, d->moveTexture[d->direction][d_num], true); }

		/*q�L�[�ŏI���*/
		if (keyState[KEY_INPUT_Q] != 0) { endflag = true; }
		

		/*Attack*/
		if (!jump && keyState[KEY_INPUT_Z] == 1) {
			/*�G�̂�������Ɍ�����ς���*/
			turnToPokemon(c, d);
			if (isNearEnemy(c, d) && d->isLive) {
				PlaySoundMem(slap,DX_PLAYTYPE_BACK);
				int tmp = c->x;
				d->hp -= 1;
				sprintf_s(s, 256, "%s�̍U��!%s��%d�̃_���[�W!%s��HP:%d", c->name, d->name, c->attack[0], d->name, d->hp);
				messageflag = true;
				setMessage(s);
				initConsole();
				outMessage();
			}
			enemyMove(d);
		}
		
		/*�΂߈ړ��������Ȃ�else if����Ȃ���if�����ɂ���*/
		/*�_���W�����̈ړ��ۂ�����Ȃ�x+=CHIP_SIZE*/
		/*�ʂ�ʂ铮�����Ȃ�x++*/
		/*�����������ΓG������*/
		/*Right*/
		else if (keyState[KEY_INPUT_D]==1) {
			c->direction = RIGHT;
			if (c->x < SCREEN_WIDTH-CHIP_SIZE && (!(d->x == c->x + 48 && d->y == c->y)||!d->isLive)) {
				c->x += CHIP_SIZE;
				enemyMove(d);
			}
		}

		/*Left*/
		else if (keyState[KEY_INPUT_A]==1) { 
			c->direction = LEFT;
			if (c->x > CHIP_SIZE && (!(d->x == c->x - 48 && d->y == c->y)||!d->isLive)) {
				c->x-=CHIP_SIZE;
				enemyMove(d);
			}
		}

		/*Up*/
		else if (!jump && keyState[KEY_INPUT_W]==1) {
			c->direction = UP;
			if (c->y > CHIP_SIZE && (!(d->y == c->y -48 && d->x == c->x)||!d->isLive)) {
				c->y-=CHIP_SIZE;
				enemyMove(d);
			}
		}

		/*Down*/
		else if (!jump && keyState[KEY_INPUT_X]==1) {
			c->direction = DOWN;
			if (c->y < SCREEN_HEIGHT - CHIP_SIZE*4 && (!(d->y == c->y + 48 && d->x == c->x)||!d->isLive)) {
				c->y+=CHIP_SIZE;
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
			//moveJump();
		//}

		//if (endflag) {
			//break;
		//}
	}

	DxLib_End();    // DX���C�u�����I������
	
	return 0;
}