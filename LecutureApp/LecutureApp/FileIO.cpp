#include "all.h"
#include "allVariableName.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>

#define CHARBUFF 256
#define BUFFSIZE 1024

void getCurrentDirectory(char*);
void setPoke(pokemon*);
int readData(pokemon* me, char* fileName, char* outputName, char dataName[BUFFSIZE]);		//CSV�t�@�C���ǂݍ��݁A�\���̂֊i�[


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
/*
void readData(pokemon* me, char* fileName, char* outputName, char dataName[BUFFSIZE]) {

	FILE* fp;			//�t�@�C���p�ϐ�
	char s[BUFFSIZE];

	//�|�C���^���g�p���Ď��Ԃ𑀍�

	me->name = dataName;

	//�R���}��؂�
	char delim[] = ", ";
	char* ctx;
	char* ctx2;

	char* p1;
	char* p2;


	errno_t error;
	error = fopen_s(&fp, fileName, "r");

	if (error != 0)
		fprintf_s(stderr, "failed to open\n");
	else {
		//�����܂�success

		//��s���ǂݍ���
		while (fgets(s, BUFFSIZE, fp) != NULL) {

			//,�ŋ�؂���1��
			p1 = strtok_s(s, delim, &ctx);


			//5�s��΂��đ��
			if (count >= 5) {
				int c = count - 5;
				p2 = strtok_s(p1, "/", &ctx2);

				csv->year[c] = atoi(p2);			//�N���i�[�A2018

				p2 = strtok_s(NULL, "/", &ctx2);
				M = atoi(p2) - 1;					//M=��-1�A�z��p�̕ϐ�

				csv->month[c] = atoi(p2);			//�����i�[


				p2 = strtok_s(NULL, "/", &ctx2);
				D = atoi(p2) - 1;					//D=��-1�A�z��p�̕ϐ�

				csv->day[M][D] = atoi(p2);			//�����i�[


				p1 = strtok_s(NULL, delim, &ctx);

				csv->water[M][D] = atof(p1);

				//2��΂��Ă���
				for (int i = 0; i < 3; i++) { p1 = strtok_s(NULL, delim, &ctx); }

				p1 = strtok_s(NULL, delim, &ctx);

				csv->averageTemp[M][D] = atof(p1);		//���ϋC����atof��char��double�ɕϊ����đ��
				for (int i = 0; i < 3; i++) { p1 = strtok_s(NULL, delim, &ctx); }


			}

			count++;
		}

		fclose(fp);

	}


	//�����܂�success

	FILE* fp2;

	int maxMonth = 0;
	int minMonth = 0;
	int maxDay = 0;
	int minDay = 0;

	error = fopen_s(&fp2, outputName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open\n");
	else {
		char kk[BUFFSIZE];
		sprintf_s(kk, "%s\n", csv->dataName);
		fputs(kk, fp2);

		int l = 0;
		for (int i = 0; i < ALLMONTH; i++) {			//����\��
			for (int j = 0; j < allMonth[i]; j++) {		//���̌��̍ő�̓��܂ŉ�

				double t = csv->averageTemp[i][j];	//���̃C���X�^���X�̕��ϋC�����i�[
				double w = csv->water[i][j];		//���̃C���X�^���X�̍~���ʂ��i�[

				csv->sumWater += w;

				if (csv->maxTemp < t) {
					csv->maxTemp = t;
					maxMonth = i + 1;
					maxDay = j + 1;
				}
				if (csv->minTemp > t) {
					csv->minTemp = t;
					minMonth = i + 1;
					minDay = j + 1;
				}

				char charYear[BUFFSIZE];
				char charMonth[BUFFSIZE];
				char charDay[BUFFSIZE];
				char charWater[BUFFSIZE];
				char charAverageTemp[BUFFSIZE];

				sprintf_s(charYear, BUFFSIZE, "%d�N", csv->year[l++]);
				sprintf_s(charMonth, BUFFSIZE, "%d��", (i + 1));
				sprintf_s(charDay, BUFFSIZE, "%d��", (j + 1));
				sprintf_s(charAverageTemp, BUFFSIZE, "�C�� => %4.1f�� ", t);		//���ϋC���Ɖ��s�R�[�h�}��
				sprintf_s(charWater, BUFFSIZE, "�~���� => %4.1fmm \n", w);


				fputs(charYear, fp2);
				fputs(charMonth, fp2);
				fputs(charDay, fp2);
				fputs(charAverageTemp, fp2);
				fputs(charWater, fp2);

			}
		}

		csv->tempDif = csv->maxTemp - csv->minTemp;

		char charSumWater[BUFFSIZE];
		char charTempDif[BUFFSIZE];
		char charMaxTemp[BUFFSIZE];
		char charMinTemp[BUFFSIZE];

		sprintf_s(charMaxTemp, BUFFSIZE, "�N�ԍō��C�� => %d��%d�� %4.1f��\n", maxMonth, maxDay, csv->maxTemp);
		sprintf_s(charMinTemp, BUFFSIZE, "�N�ԍŒ�C�� => %d��%d�� %4.1f��\n", minMonth, minDay, csv->minTemp);
		sprintf_s(charSumWater, BUFFSIZE, "�N�ԍ~�J�� => %4.1fmm\n", csv->sumWater);
		sprintf_s(charTempDif, BUFFSIZE, "�N�ԍō��C���ƍŒ�C���̍� => %4.1f��\n", csv->tempDif);

		fputs(charMaxTemp, fp2);
		fputs(charMinTemp, fp2);
		fputs(charSumWater, fp2);
		fputs(charTempDif, fp2);

		fclose(fp2);
	}
}*/
