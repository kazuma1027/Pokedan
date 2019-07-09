#pragma once

#define DOWN	0
#define UP		1
#define LEFT	2
#define RIGHT	3

struct pokemon {
	char* name;				//���O
	int level = 1;				//���x��
	int experience = 0;			//�o���l
	int maxHp = 30;				//���x�������ɂ��̗͍ő�l�̕ω��ɑΉ�
	int hp = maxHp;					//�̗�
	int moveTexture[4][2];	//���̓t�@�C������init�t�@�C���ɏ����o���A�g�p����\��
	int voice;				//�����̃t�@�C���擾�p(init�t�@�C������ǂݍ��ݗ\��)
	int attack[4] = { 1,1,1,1 };			//�Z�̎��(init�t�@�C������ǂݍ��ݗ\��)
	int direction = DOWN;
	char* skillName[4];		//�Z��
	int x, y;				//�ʒu���W
	bool isLive = true;     //�����Ă��邩�ǂ���
};