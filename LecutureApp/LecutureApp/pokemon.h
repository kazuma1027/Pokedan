#pragma once
#include "define.h"
#include "skill.h"

struct pokemon {
	char* name;					//���O
	bool isLive = true;			//�����Ă��邩�ǂ���
	
	int Max_ex = 80;
	int level = 1;				//���x��
	int experience = 0;			//�o���l(�����̏ꍇ:�G�̌o���l�����Z����@�G�̏ꍇ:�����ɉ��Z���邽�߂̌o���l������)
	int maxHp = 0;				//���x�������ɂ��̗͍ő�l�̕ω��ɑΉ�(������\��)
	int hp = 0;					//�̗�
	int speed = 0;				//����
	int type;					//�^�C�v
	int attackNum = 0;			//���ݑI��ł���Z�̎��
	int baseAttack = 0;			//��b�U����
	int moveTexture[4][2];		//���̓t�@�C������init�t�@�C���ɏ����o���A�g�p����\��
	
	int voice = 0;				//�����̃t�@�C���擾�p(init�t�@�C������ǂݍ��ݗ\��)
	
	skill skill[4];

	int direction = DOWN;		//�����Ă������
	int x, y;					//�ʒu���W
};