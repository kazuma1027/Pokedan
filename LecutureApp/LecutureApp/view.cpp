#include "Map.h"
#include "Character.h"
#include "Enemy.h"
#include "Generic.h"
#include "allVariableName.h"
#include "Message.h"

void allView(int);
void drawCharacter(pokemon*, int);
void drawHpBar();
void drawExplain();

void allView(int d_num) {

	//�}�b�v�`��
	drawMap();
	//�~�j�}�b�v�`��
	drawMiniMap();

	/*�K�w�Alevel�AHP�\��(�Œ�)*/
	DrawFormatString(0, 0, WHITE, "B%dF", m->floor + 1);
	DrawFormatString(50, 0, WHITE, "Lv: %d", c->level);
	DrawFormatString(120, 0, WHITE, "HP: %d/ %d", c->hp, c->maxHp);
	DrawFormatString(360, 0, WHITE, "�Z�b�g�킴�� : %s", c->skill[c->attackNum].name);

	//hp�o�[�\��
	drawHpBar();

	//�L�����\��
	drawCharacter(c, d_num);
	
	if (m->floor != 2) {
		for (int i = 0; i < ENEMYNUM; i++) {
			drawCharacter(enemy[m->floor][i], d_num);
		}
	}
	else {
		drawCharacter(lastboss, d_num);
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

void drawHpBar() {
	int hpColor = 0;
	if (c->hp <= c->maxHp / 3) { hpColor = RED; }
	else if (c->hp <= c->maxHp / 2) { hpColor = YELLOW; }
	else { hpColor = GREEN; }
	DrawBox(250, 1, c->maxHp + 250, 15, BLACK, true);
	DrawBox(250, 1, c->hp + 250, 15, hpColor, true);
	DrawBox(249, 0, c->maxHp + 251, 16, WHITE, false);
}


void drawExplain() {
	bool explain = false;
	setMessage("��������͕K�v�ł���?");
	setMessage("YES��Y");
	setMessage("NO��N");
	outMessage();
	while (getCountFrame() == 0 && ScreenFlip() == 0 && ProcessMessage() == 0) {
		if (keyState[KEY_INPUT_Y]) { explain = true; break; }
		if (keyState[KEY_INPUT_N]) { explain = false; break; }
	}
	if (explain) {
		showMessage("�������");
		showMessage("Q,W,E,A,D,Z,X,C�ł��ꂼ��̕����ɓ����܂�");
		showMessage("Y�������Ȃ������̈ړ��L�[�������ƕ��������ς��܂�");
		showMessage("I�ł킴���j���[���J���A�����ł킴��I�ׂ܂�");
		showMessage("J�ŃZ�b�g�����킴�œG�ɍU���ł��܂�");
		showMessage("�G�̕��������Ă��Ȃ��ƍU����������Ȃ��̂Œ��ӂ��Ă�������");
		showMessage("space�L�[�������Ƌ����I�ɃQ�[�����I���ł��܂�");
		showMessage("K�ŃZ�[�u���ł��܂�");
		showMessage("�G�͂�����̋߂��ɂȂ�ƒǂ��Ă��܂�");
		showMessage("����ȊO�̓����_���ɓ����Ă��܂�");
		showMessage("�ŉ��w�ɋ���{�X�����X�^�[��|���ƃQ�[���N���A�ƂȂ�܂�");
		showMessage("����ł̓|�P�_�������y���݂�������");
	}
	initMessage();
}