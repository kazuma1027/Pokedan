#include "all.h"
#include "allVariableName.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "Init.h"
#include "Message.h"

#define CHARBUFF 256
#define BUFFSIZE 1024

void getCurrentDirectory(char*);
void setPoke(pokemon*);
int saveData();
int readData();		//txt�t�@�C���ǂݍ��݁A�\���̂֊i�[


void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void setPoke(pokemon* me) {

	char keyValue[CHARBUFF];
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);

	char section[CHARBUFF];
	sprintf_s(section, me->name);
	char keyWord[CHARBUFF];
	char pokeFile[CHARBUFF];
	char skillFile[CHARBUFF];
	sprintf_s(pokeFile,CHARBUFF, "%s\\poke.ini", currentDirectory);
	sprintf_s(skillFile,CHARBUFF, "%s\\skill.ini", currentDirectory);
	sprintf_s(keyWord, CHARBUFF, "hp");
	//hp�ƌo���l�ݒ�
	
	if (GetPrivateProfileString(section, keyWord, "none",keyValue, CHARBUFF, pokeFile) != 0) {
		me->maxHp = atoi(keyValue);
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
	}
	me->hp = me->maxHp;
	
	sprintf_s(keyWord, CHARBUFF, "experience");
	if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, pokeFile) != 0) {
		me->experience = atoi(keyValue);
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
	}

	//�킴�̖��O�ݒ�
	for (int i = 1; i <= 4; i++) {
		sprintf_s(keyWord,CHARBUFF, "skill%d",i);
		if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, pokeFile) != 0) {
			strcpy_s(me->skill[i-1].name,CHARBUFF,keyValue);
		}
		else {
			fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
		}
	}

	//�킴�̒l�ݒ�
	for (int i = 0; i < 4; i++) {
		//sprintf_s(section,CHARBUFF, "%s", me->skill[i].name);
		strcpy_s(section, CHARBUFF, me->skill[i].name);
		sprintf_s(keyWord,CHARBUFF, "max");
		if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, skillFile) != 0) {
			me->skill[i].max = atoi(keyValue);
		}
		else {
			fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
		}
		sprintf_s(keyWord, CHARBUFF, "min");
		if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, skillFile) != 0) {
			me->skill[i].min = atoi(keyValue);
		}
		else {
			fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
		}
		sprintf_s(keyWord, CHARBUFF, "count");
		if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, skillFile) != 0) {
			me->skill[i].maxCount = atoi(keyValue);
		}
		else {
			fprintf(stdout, "%s doesn't contain [%s] %s\n", pokeFile, section, keyWord);
		}
		me->skill[i].count = me->skill[i].maxCount;
	}
}

int saveData() {


	pokemon* saveEnemy[FLOORNUM - 1][ENEMYNUM];
	for (int j = 0; j < FLOORNUM - 1; j++) {
		for (int i = 0; i < ENEMYNUM; i++) {
			if (enemy[j][i]->name == ENEMYNAME1) { saveEnemy[0][0] = enemy[j][i]; }
			if (enemy[j][i]->name == ENEMYNAME2) { saveEnemy[0][1] = enemy[j][i]; }
			if (enemy[j][i]->name == ENEMYNAME3) { saveEnemy[0][2] = enemy[j][i]; }
			if (enemy[j][i]->name == ENEMYNAME4) { saveEnemy[1][0] = enemy[j][i]; }
			if (enemy[j][i]->name == ENEMYNAME5) { saveEnemy[1][1] = enemy[j][i]; }
			if (enemy[j][i]->name == ENEMYNAME6) { saveEnemy[1][2] = enemy[j][i]; }
		}
	}



	FILE* fp;
	FILE* fp2;

	int maxMonth = 0;
	int minMonth = 0;
	int maxDay = 0;
	int minDay = 0;

	errno_t error,error2;
	error = fopen_s(&fp, "saveData.txt", "w");


	if (error != 0)
		return -1;
	else {
		char ss[BUFFSIZE];
		sprintf_s(ss, "���O,�ő�̗�,�̗�,�킴�J�E���g1,2,3,4,�Z�b�g�킴,���x��,�o���l,MAX�o���l,x,y,direction,�K��,m->x,m->y\n");
		fputs(ss, fp);
		int isLive = 0;
		int name = 0;
		if (c->name == "�q�m�A���V")name = 1;
		else if (c->name == "�[�j�K��")name = 2;
		sprintf_s(ss, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",name,c->maxHp,c->hp,c->skill[0].count,c->skill[1].count, c->skill[2].count, c->skill[3].count,c->attackNum,c->level,c->experience,c->Max_ex,c->x,c->y,c->direction,m->floor,m->x,m->y);
		fputs(ss, fp);
		for (int i = 0; i < FLOORNUM - 1; i++) {
			for (int j = 0; j < ENEMYNUM; j++) {
				isLive = 0;
				pokemon* e = saveEnemy[i][j];
				if (saveEnemy[i][j]->isLive)isLive = 1;//�����Ă���1
				sprintf_s(ss, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",isLive,e->hp,e->skill[0].count,e->skill[1].count,e->skill[2].count,e->skill[3].count,e->x,e->y,e->direction);
				fputs(ss, fp);
			}
		}
		isLive = 0;
		pokemon* e = lastboss;
		if (e->isLive)isLive = 1;//�����Ă���1
		sprintf_s(ss, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",isLive, e->hp, e->skill[0].count, e->skill[1].count, e->skill[2].count, e->skill[3].count, e->x, e->y, e->direction);
		fputs(ss, fp);

		fclose(fp);
	}

	error2 = fopen_s(&fp2, "miniMapData.txt","w");
	if (error2 != 0) {
		return -1;
	}
	else {
		char ss[BUFFSIZE];
		for (int i = 0; i < FLOORNUM; i++) {
			for (int j = 0; j < MAP_YNUM; j++) {
				for (int k = 0; k < MAP_XNUM; k++) {
					if (k < MAP_XNUM-1) {
						sprintf_s(ss, "%d,", miniMapFlag[i][j][k]);
						fputs(ss, fp2);
					}
					else {
						sprintf_s(ss, "%d\n", miniMapFlag[i][j][k]);
						fputs(ss, fp2);
					}
				}
			}
		}
		fclose(fp2);
	}
	return 0;
}


int readData() {

	FILE* fp;			//�t�@�C���p�ϐ�
	FILE* fp2;
	char ss[BUFFSIZE];

	//�R���}��؂�
	char delim[] = ", ";
	char* ctx;

	char* p1;

	char* fileName = "saveData.txt";

	errno_t error,error2;
	error = fopen_s(&fp, fileName, "r");

	int count = 0;

	if (error != 0)
		return -1;
	else {

		//��s���ǂݍ���
		while (fgets(ss, BUFFSIZE, fp) != NULL) {

			//,�ŋ�؂���1��
			p1 = strtok_s(ss, delim, &ctx);

			//1�s��΂��đ��
			if (count == 1) {
				switch (atoi(p1)) {
				case 0:
					c->name = "�s�J�`���E";
					break;
				case 1:
					c->name = "�q�m�A���V";
					break;
				case 2:
					c->name = "�[�j�K��";
					break;
				default:
					break;
				}
				//�킴�Ȃǂ̏����l����ꂽ��ɃZ�[�u�f�[�^���Q��
				charaSet(c);
				c->maxHp = atoi(strtok_s(NULL, delim, &ctx));
				c->hp = atoi(strtok_s(NULL, delim, &ctx));
				c->skill[0].count = atoi(strtok_s(NULL, delim, &ctx));
				c->skill[1].count = atoi(strtok_s(NULL, delim, &ctx));
				c->skill[2].count = atoi(strtok_s(NULL, delim, &ctx));
				c->skill[3].count = atoi(strtok_s(NULL, delim, &ctx));

				c->attackNum = atoi(strtok_s(NULL, delim, &ctx));
				c->level = atoi(strtok_s(NULL, delim, &ctx));
				c->experience = atoi(strtok_s(NULL, delim, &ctx));
				c->Max_ex = atoi(strtok_s(NULL, delim, &ctx));
				c->x = atoi(strtok_s(NULL, delim, &ctx));
				c->y = atoi(strtok_s(NULL, delim, &ctx));
				c->direction = atoi(strtok_s(NULL, delim, &ctx));

				m->floor = atoi(strtok_s(NULL, delim, &ctx));
				m->x = atoi(strtok_s(NULL, delim, &ctx));
				m->y = atoi(strtok_s(NULL, delim, &ctx));
			}
			else if (count >= 2) {
				pokemon* e = new pokemon;
				if (count - 2 < 3) {
					e = enemy[0][count-2];
				}
				else if (count - 2 < 6) {
					e = enemy[1][count - 5];
				}
				else {
					e = lastboss;
				}

				charaSet(e);
				if (!atoi(p1))e->isLive = false;
				e->hp = atoi(strtok_s(NULL, delim, &ctx));;
				e->skill[0].count = atoi(strtok_s(NULL, delim, &ctx));
				e->skill[1].count = atoi(strtok_s(NULL, delim, &ctx));
				e->skill[2].count = atoi(strtok_s(NULL, delim, &ctx));
				e->skill[3].count = atoi(strtok_s(NULL, delim, &ctx));
				e->x = atoi(strtok_s(NULL, delim, &ctx));
				e->y = atoi(strtok_s(NULL, delim, &ctx));
				e->direction = atoi(strtok_s(NULL, delim, &ctx));
			}
			count++;
		}

		fclose(fp);
	}
	error2 = fopen_s(&fp2, "miniMapData.txt", "r");
	if (error2 != 0) {
		return -1;
	}
	else {

		int count = 0;

		int tmpMiniMap[MAP_XNUM];

		int fl = 0;
		int y = 0;

		while (fgets(ss, BUFFSIZE, fp2) != NULL) {
			count = 0;
			p1 = strtok_s(ss, delim, &ctx);
			while (p1 != NULL) {
				tmpMiniMap[count] = atoi(p1);
				count++;
				p1 = strtok_s(NULL, delim, &ctx);
			}
			for (int i = 0; i < MAP_XNUM; i++) {
				miniMapFlag[fl][y][i] = tmpMiniMap[i];
			}
			y++;
			if (y == 50) { fl++; y = 0; }
		}
	}

	return 0;
}
