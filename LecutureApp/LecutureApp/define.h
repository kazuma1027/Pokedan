#pragma once

#define DOWN		0
#define UP			1
#define LEFT		2
#define RIGHT		3
#define RIGHT_DOWN	4
#define RIGHT_UP	5
#define LEFT_DOWN	6
#define LEFT_UP		7
#define CENTER		8

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (600)                          // ��ʂ̏c��
#define CHIP_SIZE        (40)                           // ��̃`�b�v�̃T�C�Y
#define MAP_HEIGHT		 (400)
#define MAP_WIDTH		 (680)

#define SCREEN_WIDTH     (800)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (600)                          // ��ʂ̏c��
#define CHIP_SIZE        (40)                           // ��̃`�b�v�̃T�C�Y
#define MAP_HEIGHT		 (400)
#define MAP_WIDTH		 (680)


//�F�̒�`
#define WHITE	GetColor(255,255,255)
#define RED		GetColor(255,0,0)
#define GREEN	GetColor(0,255,0)
#define BLUE	GetColor(0,0,255)
#define YELLOW	GetColor(255,242,0)
#define BLACK	GetColor(0,0,0)
#define BG		GetColor(20,20,20)


//�G�L����
#define ENEMYNAME1	"�t�V�M�_�l"
#define ENEMYNAME2	"�f�B�O�_"
#define ENEMYNAME3	"�O���[�h��"
#define ENEMYNAME4	"�_�[�N���C"
#define ENEMYNAME5	"�{�X�S�h��"
#define ENEMYNAME6	"�X�C�N��"
#define BOSSNAME	"�~���E�c�["

//���C���L�����A����������������Ǝg�p�ł���L�������ς��
#define MAINCHARANAME1 "�s�J�`���E"
#define MAINCHARANAME2 "�q�m�A���V"
#define MAINCHARANAME3 "�[�j�K��"

//�^�C�v
#define NORMAL 0
#define FIRE 1
#define WATER 2
#define ELECTRIC 3
#define GLASS 4
#define ICE 5
#define FIGHT 6
#define POISON 7
#define GROUND 8
#define FLIGHT 9
#define ESPER 10
#define INSECT 11
#define ROCK 12
#define GHOST 13
#define DRAGON 14
#define EVIL 15
#define STEEL 16

//�����ĉ񕜂���܂łɂ�����^�[����
#define RECOVERYTURN 5

#define ENEMYNUM 3
#define PI 3.141592654

#define KEY(X,Y) ((X) * 100 + (Y))
#define KEYDATA(X, Y, N) std::pair<int, NODE>(KEY(X,Y), N)		//���W�ƃm�[�h���y�A�ɂ���


struct pokemon;
struct skill;
struct maps;
struct NODE;
