#pragma once
#include "allVariableName.h"
#include "Message.h"
#include "Generic.h"
#include "Character.h"
#include <map>
#include <stack>


pokemon e1_1;
pokemon e2_1;
pokemon e3_1;
pokemon e1_2;
pokemon e2_2;
pokemon e3_2;
pokemon boss;
pokemon e_null1;
pokemon e_null2;

pokemon* enemy[FLOORNUM][ENEMYNUM] = {
	{ &e1_1 , &e2_1 , &e3_1 },
	{ &e1_2 , &e2_2 , &e3_2 },
	{ &boss , &e_null1 , &e_null2},
};

/*�v���g�^�C�v�錾*/
void turnToPokemon(pokemon* me, pokemon* enemy);
NODE* Astar(pokemon* enemy);
bool isNearPokemon(pokemon* me, pokemon* enemy);
bool isNearPokemon2(pokemon* me, pokemon* enemy);
bool findPokemon(pokemon* me, pokemon* enemy);
void charaMoveEnemy(pokemon* me, int x, int y);
bool isNearEnemy(pokemon* e, int x, int y);
void enemyMove(pokemon* enemy);
void randomEnemyPut(pokemon* e[ENEMYNUM]);
void sortEnemy();


/*�U�����ɓG�̕�������*/
/*�̂��Ɍ�������O�ɉ摜��~���ă_�u���𖳂���*/
void turnToPokemon(pokemon* me, pokemon* enemy) {
	if (me->x > enemy->x)me->direction = LEFT;
	else if (me->x < enemy->x)me->direction = RIGHT;
	if (me->y > enemy->y)me->direction = UP;
	else if (me->y < enemy->y)me->direction = DOWN;
}


void setNode(NODE* child, int x, int y, NODE* parent, int cost, int f) {
	child->x = x;
	child->y = y;
	child->parent = parent;
	child->cost = cost;
	child->f = f;
}

int getCost() {
	return 1;
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

	NODE s = { 0,0,0 };
	NODE e = { 0,0,0 };


	int key[8][2] = {
		{ 1,0 },
		{ -1,0 },
		{ 0,-1 },
		{ 0,1 },
		{ 1,1 },
		{ -1,1 },
		{ 1,-1 },
		{ -1,-1 },
	};


	//�X�^�[�g
	//�G�̍��W
	s.x = SX(enemy);
	s.y = SY(enemy);

	//�e�m�[�h�A�R�X�g�A�]���l�Ȃ�
	setNode(&s, s.x, s.y, NULL, 0, 0);
	//open.node[open.index++] = &s;
	//�I�[�v�����X�g�ɑ��
	openList.insert(KEYDATA(s.x, s.y, s));

	//�S�[��
	//�����̍��W
	e.x = GX;
	e.y = GY;

	while (true) {

		// open���X�g���Ȃ��Ȃ����̂ŏI������
		if (openList.empty()) { return NULL; }

		int f_min = 9999;

		//�W�J�p�m�[�h
		NODE *p = new NODE;

		auto it = openList.begin();		//�擪�C�e���[�^�擾
		std::map<int, NODE>::iterator it_min;
		//�ŏ��m�[�h�擾
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
		//�S�[����8���ɐݒ�
		if ((p->x == e.x && (p->y == e.y + 1 || p->y == e.y - 1)) || (p->y == e.y && (p->x == e.x + 1 || p->x == e.x - 1))) {

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

			//�m�[�h�̎���(���W)
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
					openList[KEY(cx, cy)].cost = child->cost;
					openList[KEY(cx, cy)].f = child->f;
					openList[KEY(cx, cy)].parent = child->parent;
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
					openList.insert(KEYDATA(cx, cy, closed_child->second));
					closedList.erase(KEY(cx, cy));
				}

			}
			else {//�I�[�v�����X�g�ɂ��N���[�Y�h���X�g�ɂ��܂܂�Ă��Ȃ�
				openList.insert(KEYDATA(cx, cy, *child));
			}



		}
	}

	NODE* node = st.top();


	return node;
}

/*���͂̃}�X�ɓG�����邩���Ȃ���* /
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

/*�����Ă��邩�ǂ����A�����Ă����A*�Œǂ�*/
bool findPokemon(pokemon* me, pokemon* enemy) {
	if ((me->x - SCREEN_WIDTH / 2 < enemy->x) && (me->x + SCREEN_WIDTH / 2 > enemy->x) && (me->y + SCREEN_HEIGHT / 2 > enemy->y) && (me->y - SCREEN_HEIGHT / 2 < enemy->y))return true;
	else return false;
}

/*�G�p�̏���,����ւ�菈���𖳂�����*/
void charaMoveEnemy(pokemon* me, int x, int y) {

	if (x == 1)setDirection(me, RIGHT);
	else if (x == -1)setDirection(me, LEFT);

	if (y == 1)setDirection(me, DOWN);
	else if (y == -1)setDirection(me, UP);

	int tmpX = (me->x - c->x) / CHIP_SIZE;
	int tmpY = (me->y - c->y) / CHIP_SIZE;
	int nextCell_x = mapping[m->floor][SY(me)][SX(me) + x];
	int nextCell_y = mapping[m->floor][SY(me) + y][SX(me)];

	//�ȂȂ߈ړ����ɁA�ȂȂ߂Ɏ�l���������
	if ((x == 1 || x == -1) && (y == 1 || y == -1)) {
		if ((tmpX == 1 || tmpX == -1) && (tmpY == 1 || tmpY == -1)) {
			//�U���ł���͈͂Ɉړ�����
			if (nextCell_x > 0)y = 0;
			else if (nextCell_y > 0)x = 0;
		}
	}

	/*�ړ���̃Z���m�F*/
	int nextCell = mapping[m->floor][SY(me) + y][SX(me) + x];

	if (nextCell > 0 && !isNearEnemy(me, x, y)) {
		me->x += x * CHIP_SIZE;
		me->y += y * CHIP_SIZE;
	}
}

/*�G(����)���ړ���ɂ��邩*/
/*�ʒu���𖳂������߂Ɏg�p*/
bool isNearEnemy(pokemon* e, int x, int y) {

	for (int i = 0; i < ENEMYNUM; i++) {
		if (enemy[m->floor][i] != e) {
			//�ړ���Ɋ��ɓG������ꍇ
			if (enemy[m->floor][i]->isLive) {
				if (SX(e) + x == SX(enemy[m->floor][i]) && (SY(e) + y == SY(enemy[m->floor][i])))return true;
			}
		}
	}
	return false;

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
			charaMoveEnemy(enemy, (c->x - enemy->x) / CHIP_SIZE, (c->y - enemy->y) / CHIP_SIZE);	//�U���ł���Ƃ���Ɉړ�����
		}
		/*8���ɂ��Ȃ��Ƃ���A*�A���S���Y��*/
		else if (!isNearPokemon2(enemy, c)) {
			NODE* nextEnemyNode = Astar(enemy);
			charaMoveEnemy(enemy, nextEnemyNode->x - SX(enemy), nextEnemyNode->y - SY(enemy));
		}
	}
	/*�܂��Ώۂ��������Ă��Ȃ��ꍇ�A���낤�낷��*/
	else {
		switch (getRandom(0, 8)) {
		case LEFT:
			charaMoveEnemy(enemy, -1, 0);
			break;
		case RIGHT:
			charaMoveEnemy(enemy, 1, 0);
			break;
		case UP:
			charaMoveEnemy(enemy, 0, -1);
			break;
		case DOWN:
			charaMoveEnemy(enemy, 0, 1);
			break;
		case LEFT_UP:
			charaMoveEnemy(enemy, -1, -1);
			break;
		case LEFT_DOWN:
			charaMoveEnemy(enemy, -1, 1);
			break;
		case RIGHT_UP:
			charaMoveEnemy(enemy, 1, -1);
			break;
		case RIGHT_DOWN:
			charaMoveEnemy(enemy, 1, 1);
			break;
		default:
			break;
		}
	}
}

void randomEnemyPut(pokemon* e[ENEMYNUM]) {
	bool flag = 0;
	for (int i = 0; i < ENEMYNUM; i++) {
		while (true) {
			flag = true;
			e[i]->x = (getRandom(5, 30)+m->x) * CHIP_SIZE;
			e[i]->y = (getRandom(5, 30)+m->y) * CHIP_SIZE;
			if (mapping[m->floor][SY(e[i])][SX(e[i])] > 0) {
				//���𖳂���
				for (int j = 0; j < i; j++) {
					if ((SX(e[i]) == SX(e[j]) && SY(e[i]) == SY(e[j])) || (SX(e[i]) == GX && SY(e[i]) == GY))flag = false;
				}
				if (flag)break;
			}
		}
	}
}

void sortEnemy() {
	pokemon* enemy_tmp[ENEMYNUM];
	bool enFlag = false;
	int sx = 0;
	int sy = 0;
	for (int i = 0; i < ENEMYNUM; i++) {
		int distance = 9999;
		for (int j = 0; j < ENEMYNUM; j++) {
			enFlag = false;
			sx = GX - SX(enemy[m->floor][j]);
			if (sx < 0)sx *= -1;
			sy = GY - SY(enemy[m->floor][j]);
			if (sy < 0)sy *= -1;
			//��ԋ߂��G����enemy_tmp�Ɋi�[���Ă���
			if (distance > sx + sy) {
				//�ŏ��͔�肪�Ȃ��̂őf���Ɉ�ԋ߂��G���i�[
				if (i == 0) {
					distance = sx + sy;
					enemy_tmp[i] = enemy[m->floor][j];
				}

				//���ڈȍ~�͔��𖳎�����
				else {
					//����enemy_tmp�Ɋ܂܂�Ă���v�f�͖�������
					for (int k = 0; k < ENEMYNUM; k++) {
						if (enemy[m->floor][j] == enemy_tmp[k])enFlag = true;
					}
					if (enFlag)continue;
					distance = sx + sy;
					enemy_tmp[i] = enemy[m->floor][j];
				}
			}
		}
	}
	for (int i = 0; i < ENEMYNUM; i++) {
		enemy[m->floor][i] = enemy_tmp[i];
	}
}

void enemyMapMove(int tmp_mx,int tmp_my) {
	pokemon* tmp = NULL;

	//����ւ�菈����D�悳����
	for (int i = 0; i < ENEMYNUM; i++) {
		if (enemy[m->floor][i]->hp != 0) {
			if (GX == SX(enemy[m->floor][i]) + (m->x - tmp_mx) && GY == SY(enemy[m->floor][i]) + (m->y - tmp_my)) {
				charaMoveEnemy(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
				//�G�����Ă��������ړ����邽�߁AcharaMoveEnemy�͎g��Ȃ�
				enemy[m->floor][i]->x += (m->x - tmp_mx) * CHIP_SIZE;
				enemy[m->floor][i]->y += (m->y - tmp_my) * CHIP_SIZE;
				/*
				if (mapping[m->floor][SY(enemy[m->floor][i])][SX(enemy[m->floor][i])] <= 0) {
					enemy[m->floor][i]->x -= (m->x - tmp_mx) * CHIP_SIZE;
					enemy[m->floor][i]->y -= (m->y - tmp_my) * CHIP_SIZE;
				}*/

				turnToPokemon(enemy[m->floor][i], c);
				attack(enemy[m->floor][i], c);
				tmp = enemy[m->floor][i];
			}
		}
	}

	for (int i = 0; i < ENEMYNUM; i++) {
		if (tmp == enemy[m->floor][i])continue;
		if (enemy[m->floor][i]->hp != 0) {
			if (isNearEnemy(enemy[m->floor][i], 0, 0) && mapping[m->floor][SY(enemy[m->floor][i])][SX(enemy[m->floor][i])] > 0) {
				//�G�����Ă��������ړ����邽�߁AcharaMoveEnemy�͎g��Ȃ�
				enemy[m->floor][i]->x += (m->x - tmp_mx) * CHIP_SIZE;
				enemy[m->floor][i]->y += (m->y - tmp_my) * CHIP_SIZE;
			}
		}
	}

	for (int i = 0; i < ENEMYNUM; i++) {
		if (tmp == enemy[m->floor][i])continue;
		if (enemy[m->floor][i]->hp != 0) {
			charaMoveEnemy(enemy[m->floor][i], m->x - tmp_mx, m->y - tmp_my);
			//�ړ���A�O�A�E�A���̂ǂ��炩�ɂ����Ƃ�
			if (isNearPokemon(enemy[m->floor][i], c) && (GX + (m->x - tmp_mx) != SX(enemy[m->floor][i]) && GY + (m->y - tmp_my) != SY(enemy[m->floor][i]))) {
				turnToPokemon(enemy[m->floor][i], c);
				attack(enemy[m->floor][i], c);
			}
			//�ȂȂ߂ɂ���Ƃ�
			else if (!isNearPokemon(enemy[m->floor][i], c) && isNearPokemon2(enemy[m->floor][i], c)) {
				charaMoveEnemy(enemy[m->floor][i], (c->x - enemy[m->floor][i]->x) / CHIP_SIZE, (c->y - enemy[m->floor][i]->y) / CHIP_SIZE);
			}
			//8���ɂ���Ƃ�
			else if (isNearPokemon(enemy[m->floor][i], c)) {
				turnToPokemon(enemy[m->floor][i], c);
			}

			else {
				NODE* n = Astar(enemy[m->floor][i]);
				if (n != NULL)charaMoveEnemy(enemy[m->floor][i], n->x - SX(enemy[m->floor][i]), n->y - SY(enemy[m->floor][i]));
			}
		}
	}
}

void mainEnemyMove(int tmp_mx,int tmp_my) {
	if (!menuflag && isPutMoveKey() && tmp_mx == m->x && tmp_my == m->y) {
		if (keyState[KEY_INPUT_Y] == 0) {
			sortEnemy();

			for (int i = 0; i < ENEMYNUM; i++) {
				enemyMove(enemy[m->floor][i]);
			}
		}
	}
	/*�}�b�v�ړ���*/
	else if (!menuflag && isPutMoveKey() && (tmp_mx != m->x || tmp_my != m->y)) {

		sortEnemy();
		enemyMapMove(tmp_mx, tmp_my);
	}
}