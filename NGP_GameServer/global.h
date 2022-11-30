#pragma once
struct sc_packet_move {
	char size;
	char type;
	char id;
	float pos_x, pos_y;
};

struct sc_packet_boom {
	char size;
	char type;
	float pos_x, pos_y;
};

const char SC_PACKET_MOVE = 1;
const char SC_PACKET_DEAD = 2;
const char SC_PACKET_BOOM = 3;
const char SC_PACKET_START_GAME = 4;
const char SC_PACKET_LIFE_COUNT = 5;
const char SC_PACKET_WIN_CHECK = 6;
const char SC_PACKET_HIT_CHECK = 7;
//Ÿ���߰�
const char SC_PACKET_LOGIN_OK = 8;
const char SC_PACKET_HIT = 9;
const char SC_PACKET_DIFFICULTY = 10;// ���̵�


//���� �غ�� ���ӽ����� �˸�
struct sc_packet_start_game {
	char size;
	char type;
};

//ó�� ���� ������ ������ Ŭ���̾�Ʈ�� ���̵� �����ش�.
struct sc_packet_login_ok {
	char size;
	char type;
	char id;
};

//�������� �浹ó���� ���� �÷��̾ �¾����� ������ ��Ŷ
struct sc_packet_hit {
	char size;
	char type;
	char id;
	char bomb_id;
};

struct sc_packet_life_count {
	char size;
	char type;
	char id;
	int lifeCount;
};

struct sc_WinPlayerCheck_packet {
	char size;
	char type;
	char id;
	bool bWinCheck;
};

struct sc_difficulty_packet {
	char size;
	char type;
	char id;
	int difficulty_number;
	bool easy;
	bool normal;
	bool hard;
};