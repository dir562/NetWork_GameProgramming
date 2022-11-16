#pragma once
struct sc_packet_move {
	char size;
	char type;
	char id;
	float pos_x, pos_y;
};

const char SC_PACKET_MOVE = 1;
const char SC_PACKET_DEAD = 2;
const char SC_PACKET_BOOM = 3;
const char SC_PACKET_START_GAME = 4;
const char SC_PACKET_LIFE_COUNT = 5;
const char SC_PACKET_WIN_CHECK = 6;
const char SC_PACKET_HIT_CHECK = 7;