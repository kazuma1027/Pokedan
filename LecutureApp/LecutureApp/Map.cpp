#pragma once
#include "allVariableName.h"
#include "Generic.h"
#include "Enemy.h"
#include "Character.h"

/*�}�b�v�\����*/
maps mp;
maps* m = &mp;

/*�~�j�}�b�v�\���t���O*/
int miniMapFlag[FLOORNUM][MAP_YNUM][MAP_XNUM];


void stairsMove(int stairs) {
	m->floor += stairs;
	sprintf_s(s, "�͂��܂�̃_���W����\n�@�@�@�@B%dF", m->floor + 1);
	wait(2000, s);
	if (m->floor != 2) {
		randomEnemyPut(enemy[m->floor]);
	}
}

void mapMove(maps* m, pokemon* me, pokemon* enemy[ENEMYNUM], int x, int y) {

	int nextCell = mapping[m->floor][me->y / CHIP_SIZE - m->y - y][me->x / CHIP_SIZE - m->x - x];

	//�ړ������ƈ����|���菈��
	if (nextCell > 0 && !keyState[KEY_INPUT_Y]) {
		for (int i = 0; i < ENEMYNUM; i++) {
			int nextEnemyCell = mapping[m->floor][enemy[i]->y / CHIP_SIZE - m->y - y][enemy[i]->x / CHIP_SIZE - m->x - x];
			if (nextEnemyCell <= 0)charaMoveEnemy(enemy[i], x, y);
		}
		m->x += x;
		m->y += y;
	}

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


void drawMiniMap() {

	for (int i = GX - 1; i <= GX + 1; i++) {
		for (int j = GY - 1; j <= GY + 1; j++) {
			miniMapFlag[m->floor][j][i] = 1;
		}
	}

	for (int i = 0; i < MAP_XNUM; i++) {
		for (int j = 0; j < MAP_YNUM; j++) {
			if ((mapping[m->floor][j][i] == 1 || mapping[m->floor][j][i] == 2) && miniMapFlag[m->floor][j][i] == 1)DrawFormatString(i * 3, j * 3, WHITE, ".");
			if (i == GX && j == GY)DrawFormatString(i * 3, j * 3, RED, ".");
			for (int k = 0; k < ENEMYNUM; k++) {
				if (i == SX(enemy[m->floor][k]) && j == SY(enemy[m->floor][k]) && enemy[m->floor][k]->isLive)DrawFormatString(i * 3, j * 3, BLUE, ".");
			}
			if (mapping[m->floor][j][i] == 100)DrawFormatString(i * 3, j * 3, GREEN, ".");
			if (mapping[m->floor][j][i] == 101)DrawFormatString(i * 3, j * 3, GREEN, ".");
		}
	}
}