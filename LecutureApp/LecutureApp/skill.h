#pragma once
#include "define.h"

struct skill {

	int min;
	int max;
	char name[256];		//�Z��
	int count;			//�킴���g�����
	int maxCount;		//�킴���g����ő��
	int type;			//�킴�^�C�v

	//0:�m�[�}��,1:�ق̂�,2:�݂�,3:�ł�,4:����,5:������,6:�����Ƃ�,7:�ǂ�,8:���߂�,9:�Ђ���,10:�G�X�p�[,11:�ނ�,12:����,13:�S�[�X�g,14:�h���S��,15:����,16:�͂���
};