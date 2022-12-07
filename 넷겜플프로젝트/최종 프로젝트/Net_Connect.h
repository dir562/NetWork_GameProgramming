
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

//전부 준비시 게임시작을 알림
struct sc_packet_start_game {
	char size;
	char type;
};

//처음 접속 했을때 접속한 클라이언트의 아이디를 보내준다.
struct sc_packet_login_ok {
	char size;
	char type;
	char id;
};

//서버에서 충돌처리를 통해 플레이어가 맞았을때 보내는 패킷
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