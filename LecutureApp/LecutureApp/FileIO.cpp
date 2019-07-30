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

	FILE* fp;

	int maxMonth = 0;
	int minMonth = 0;
	int maxDay = 0;
	int minDay = 0;

	errno_t error;
	error = fopen_s(&fp, "saveData.txt", "w");

	if (error != 0)
		return -1;
	else {
		char ss[BUFFSIZE];
		sprintf_s(ss, "���O,�ő�̗�,�̗�,�킴�J�E���g1,2,3,4,�Z�b�g�킴,���x��,�o���l,MAX�o���l,x,y,direction,�K��,m->x,m->y\n");
		fputs(ss, fp);
		int n = 0;
		if (c->name == "�q�m�A���V")n = 1;
		else if (c->name == "�[�j�K��")n = 2;
		sprintf_s(ss, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",n,c->maxHp,c->hp,c->skill[0].count,c->skill[1].count, c->skill[2].count, c->skill[3].count,c->attackNum,c->level,c->experience,c->Max_ex,c->x,c->y,c->direction,m->floor,m->x,m->y);
		fputs(ss, fp);

		fclose(fp);
		return 0;
	}
}


int readData() {

	FILE* fp;			//�t�@�C���p�ϐ�
	char ss[BUFFSIZE];

	//�R���}��؂�
	char delim[] = ", ";
	char* ctx;

	char* p1;

	char* fileName = "saveData.txt";

	errno_t error;
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
			if (count >= 1) {
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

			count++;
		}

		fclose(fp);
		return 0;
	}
}
