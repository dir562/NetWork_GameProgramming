
#pragma once

#include "protocol.h"
// #include "Player.h"
#include <array>
//#include "global.h"


const int BUFSIZE = 2048;
void err_quit(const char* msg);

void err_display(const char* msg);

int netInit();

int netclose();

void do_send(int num_bytes, void* mess);

DWORD WINAPI do_recv(LPVOID arg);


bool get_start_game();

void send_start_game_packet(SOCKET* client_socket, int client_id);
void send_login_ok_packet(SOCKET* client_socket, int client_id);
void send_move_packet(SOCKET* client_socket, int client_id);
void send_hit_packet(SOCKET* client_socket, int client_id, int bomb_id);
void send_life_count_packet(SOCKET* client_socket, int client_id, int lifecount);
void send_winplayercheck_packet(SOCKET* client_socket, int client_id, bool bwincheck);
void send_difficulty_packet(SOCKET* client_socket, int client_id, int difficulty, bool dif);


struct cs_Player_packet_move {
	char	size;
	char	type;
	char	direction;
};

struct sc_packet_move {
	char size;
	char type;
	char id;
	float pos_x, pos_y;
};

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