#pragma once
#include "header.h"

class Player {
public:
	Player();
	Player(SOCKET& s, int id);
	~Player();

public:
	int m_id;
	int pos_x;
	int speed;
	int hp = 3;
	SOCKET G_socket;
	char buf[BUFSIZE];
	RECT collision_rect;
	bool bdead;

public:
	void get_BoundingRect();
	void update(float fTimeElapsed);
	//플레이어의 이전위치(이동전)로 설정
	void setPrevPos();
};