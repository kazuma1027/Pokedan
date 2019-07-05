#include "DxLib.h"
#include "pokemon.h"

#define DOWN	0
#define UP		1
#define LEFT	2
#define RIGHT	3
#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (400)                          // ��ʂ̏c��
#define CHIP_SIZE        (48)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // �}�b�v�̏c��

/*������Ă���L�[���i�[*/
char keyState[256];

/*�_���[�W��^�������^���Ă��Ȃ���*/
bool damage = false;

int enemyDirection = 0;

/*�W�����v�p�ϐ�*/
int temp = 0;
int y_temp = 0;
int y_prev = 0;

/*�W�����v�p�t���O*/
bool onGround = false;		//�W�����v����u��
bool jump = false;			//�W�����v���Ă��邩�ǂ���	

/*�|�P�����\����*/
pokemon poke;
pokemon dark;
pokemon* c = &poke;
pokemon* d = &dark;

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


bool isNearEnemy(pokemon* pika,pokemon* dark) {
	if ((pika->x - 48 <= dark->x) && (pika->x + 48 >= dark->x) && (pika->y - 48 <= dark->y) && (pika->y + 48 >= dark->y))return true;
	else return false;
}

/*���̓G�̓���*/
void enemyMove() {
	if (c->x-48 < d->x) {
		d->x -= CHIP_SIZE;
		enemyDirection = LEFT;
	}
	if (c->x+48 > d->x) {
		d->x += CHIP_SIZE;
		enemyDirection = RIGHT;
	}
	if (c->y-48 < d->y) {
		d->y -= CHIP_SIZE;
		enemyDirection = UP;
	}
	if (c->y+48 > d->y) {
		d->y += CHIP_SIZE;
		enemyDirection = DOWN;
	}
}

/*�L�[��������Ă���t���[�����𐔂���*/
int getCountFrame() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			keyState[i]++;     // ���Z
			if (keyState[i] == 60)keyState[i] = 1;	//�ړ����̉摜�����Ɏg�p
		}
		else {              // ������Ă��Ȃ����
			keyState[i] = 0;   // 0�ɂ���
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
	if (DxLib_Init() != 0) { return -1; }					// DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);  //�`���𗠉�ʂɐݒ�
	
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
	
	/*�W�����v�̑��x�ω��Ɏg�p*/
	int f = 0;

	/*���W�ʒu*/
	c->x = CHIP_SIZE*3;
	c->y = CHIP_SIZE*3;

	d->x = CHIP_SIZE*10;
	d->y = CHIP_SIZE*2;

	int direction = DOWN;
	int d_num = 0;

	/*�t���O*/
	bool endflag = false;		//q�������ƏI���
	int tempTime = 0;
	int stringTime = 0;
	int currentTime = 0;
	SetWaitVSyncFlag(FALSE);

	currentTime = GetNowCount();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A,�t���[���J�E���g)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0) {

		/*500ms(0.5�b)�Ɉ�x�摜�X�V*/
		if (currentTime - tempTime> 500) 
		{	
			if (d_num == 1)d_num = 0;
			else d_num = 1;
			tempTime = GetNowCount(); 
		}

		currentTime = GetNowCount();

		/*DrawRotaGraph(x���W,y���W,�k�ړx,�p�x,�`�悷��摜�n���h��,�w�i���ߏ�����ON,OFF)*/
		/*���W�͉摜�̐^�񒆂Ɏ���*/

		DrawFormatString(0, 0, GetColor(255, 255, 255), "B1F");
		DrawFormatString(50, 0, GetColor(255, 255, 255), "Lv: %d",c->level);
		DrawFormatString(120, 0, GetColor(255, 255, 255), "HP: %d/ %d",c->hp,c->maxHp);
		
		DrawRotaGraph(c->x, c->y, 1.5, 0, c->moveTexture[direction][d_num], true);
		if (d->hp > 0) { DrawRotaGraph(d->x, d->y, 1.5, 0, d->moveTexture[enemyDirection][d_num], true); }
		if (d->hp==0 && d->isLive) { stringTime = GetNowCount(); d->isLive = false; }
		if (!(d->isLive) && GetNowCount() - stringTime < 2000) { DrawFormatString(0, 0, GetColor(255, 255, 255), "%s�͓|�ꂽ!", d->name);}

		/*30�t���[�����Ƃɉ摜�X�V->�����Ă���悤�Ɍ�����*/
		/*q�L�[�ŏI���*/
		if (keyState[KEY_INPUT_Q] != 0) { endflag = true; }

		/*�_���[�W��������*/
		if (c->hp > 0 && isNearEnemy(c, d) && !damage) { c->hp -= 1; damage = true; }
		
		/*�΂߈ړ��������Ȃ�else if����Ȃ���if�����ɂ���*/
		/*�_���W�����̈ړ��ۂ�����Ȃ�*/
		/*Right*/
		if (keyState[KEY_INPUT_D]==1) {
			direction = RIGHT;
			if (c->x < SCREEN_WIDTH-24 && !(d->x == c->x + 48 && d->y == c->y)) {
				if (keyState[KEY_INPUT_B])c->x += 3;
				else c->x+=CHIP_SIZE;
				damage = false;
			}
			enemyMove();
		}

		/*Left*/
		else if (keyState[KEY_INPUT_A]==1) { 
			direction = LEFT;
			if (c->x > 24 && !(d->x == c->x - 48 && d->y == c->y)) {
				if (keyState[KEY_INPUT_B])c->x -= 3;
				else c->x-=CHIP_SIZE;
				damage = false;
			}
			enemyMove();
		}

		/*Up*/
		else if (!jump && keyState[KEY_INPUT_W]==1) {
			direction = UP;
			if (c->y > 24 && !(d->y == c->y -48 && d->x == c->x)) {
				if (keyState[KEY_INPUT_B])c->y -= 3;
				else c->y-=CHIP_SIZE;
				damage = false;
			}
			enemyMove();
		}

		/*Down*/
		else if (!jump && keyState[KEY_INPUT_X]==1) {
			direction = DOWN;
			if (c->y < SCREEN_HEIGHT - 24 && !(d->y == c->y + 48 && d->x == c->x)) {
				if (keyState[KEY_INPUT_B])c->y += 3;
				else c->y+=CHIP_SIZE;
				damage = false;
			}
			enemyMove();
		}

		/*Attack*/
		else if (!jump && keyState[KEY_INPUT_Z] == 1) {
			if(isNearEnemy(c,d) && d->isLive){
				DrawFormatString(200, 400, GetColor(255, 255, 255), "%s�̍U��! %s��%d�̃_���[�W!",c->name,d->name,1);
				d->hp -= 1;
			}
			damage = false;
			enemyMove();
		}
		/*���܂��̃W�����v����*/
		if (!jump && keyState[KEY_INPUT_SPACE] == 1) { 
			y_prev = c->y; temp = c->y;
			jump = true;  onGround = true;
		}

		
		
		/*�W�����v�����{��*/
		if (jump) {
			moveJump();
		}

		if (endflag) {
			break;
		}
	}
	DxLib_End();    // DX���C�u�����I������
	return 0;
}