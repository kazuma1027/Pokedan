#include "Map.h"
#include "Character.h"
#include "Enemy.h"
#include "Generic.h"
#include "allVariableName.h"

void allView(int);
void drawCharacter(pokemon*, int);
void drawHpBar();

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
	DrawBox(240, 1, c->maxHp + 240, 15, BLACK, true);
	DrawBox(240, 1, c->hp + 240, 15, hpColor, true);
	DrawBox(239, 0, c->maxHp + 241, 16, WHITE, false);
}