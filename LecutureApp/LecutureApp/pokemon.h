#pragma once

struct pokemon {
	char* name;				//���O
	int level = 1;				//���x��
	int experience = 0;			//�o���l
	int maxHp = 30;				//���x�������ɂ��̗͍ő�l�̕ω��ɑΉ�
	int hp = maxHp;					//�̗�
	int moveTexture[4][2];	//���̓t�@�C������init�t�@�C���ɏ����o���A�g�p����\��
	int voice;				//�����̃t�@�C���擾�p(init�t�@�C������ǂݍ��ݗ\��)
	int attack[4];			//�Z�̎��(init�t�@�C������ǂݍ��ݗ\��)
	int x, y;				//�ʒu���W
	bool isLive = true;     //�����Ă��邩�ǂ���
};