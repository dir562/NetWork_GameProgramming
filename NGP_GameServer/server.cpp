//#include "..\..\Common.h"
#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <stdio.h> // printf(), ...
#include<iostream>
#include"global.h"
#include"Player.h"

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#define BUFSIZE 1024
#define SERVERPORT 9000

using namespace std;

HANDLE			hSendEvent;
HANDLE			hCalculateEvent;
unordered_map<int, Player>new_clients;
int				thread_count = 0; // 몇개 클라가 접속했는지


//함수
void send_start_game_packet(SOCKET* client_socket, int client_id);		
void gameStart();						// 게임 시작 처리
void send_login_ok_packet(SOCKET* client_socket, int client_id);					// 로그인 성공을 알려주는 패킷 전송// 게임이 시작하면 모든 클라이언트에게 패킷 전송	
void send_move_packet(SOCKET* client_socket, int client_id);
void send_hit_packet(SOCKET* client_socket, int client_id, int bullet_id);

void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main(int argc, char* argv[])
{
	int retval;		// 오류 검출 변수

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("SOCKET()");

	// bind()
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
	if (retval == SOCKET_ERROR) err_quit("BIND()");

	// listen()
	retval = listen(sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("LISTEN()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int addrlen;

	// 이벤트 사용 준비

	hSendEvent = CreateEvent(NULL, FALSE, TRUE, NULL);		// 콘솔창에 쓰는것은 비신호로 시작
	if (hSendEvent == NULL) return 1;
	hCalculateEvent = CreateEvent(NULL, FALSE, TRUE, NULL);		// 콘솔창에 쓰는것은 비신호로 시작
	if (hCalculateEvent == NULL) return 1;

	//쓰레드 생성
	HANDLE hThread;
	while (1)
	{
		addrlen = sizeof(client_addr);
		client_sock = accept(sock, (SOCKADDR*)&client_addr, &addrlen);
		if (client_sock == INVALID_SOCKET) { err_display("ACCEPT()"); break; }


		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)player, 0, NULL);
		if (hThread == NULL) { closesocket(player->m_c_socket); }
		else { CloseHandle(hThread); }

		thread_count++;
	}

	//게임스타트
	//gameStart();
}

DWORD WINAPI ProcessClient(LPVOID arg)
{

	int retval;
	SOCKET client_sock = (SOCKET)arg;
	char* buf;
	int len;

	// send_login_ok_packet();

	// 클라이언트와 데이터 통신
	while (1) {
		retval = recv(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "강제 연결 끊김" << endl;
			//send_dead_packet();
		}

	}

	while (1) {		
		retval = recv(client_sock, buf, len, 0);
	}
	closesocket(client_sock);
	return 0;
}

void processing_client(int client_id, char*p)
{
	unsigned char packet_type = p[1];
	Player& cl = new_clients[client_id];
	switch (packet_type)
	{
	case SC_PACKET_MOVE: {
		sc_packet_move* packet = reinterpret_cast<sc_packet_move*>(p);

		switch (packet->id)
		{
		case 0:
			cl.pos_x += cl.speed;
			break;
		case 1:
			cl.pos_x -= cl.speed;
			break;
		default:
			cout << "오류값 전달!!\n" << client_id << endl;
			exit(-1);
		}

	}
     


	}
}



void gameStart()
{
	send_start_game_packet(&client_socket, client_id);
	cout << "게임시작" << endl;
}


void send_start_game_packet(SOCKET* client_socket, int client_id)
{
	sc_packet_start_game packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_START_GAME;
	send(*client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
}


void send_login_ok_packet(SOCKET* client_socket, int client_id)
{
	sc_packet_login_ok packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_LOGIN_OK;
	packet.id = client_id;
	send(*client_socket, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
}


void send_move_packet(SOCKET* client_socket, int client_id)
{
	sc_packet_move packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_MOVE;
	packet.pos_x = new_clients[client_id].pos_x;
	packet.id = client_id;
	send(*client_socket, reinterpret_cast<const char*>(&packet), packet.size, 0);
}

void send_bomb_packet(SOCKET* client_socket, int client_id) {
	sc_packet_boom packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_BOOM;
	packet.pos_x = Boom.x;
	packet.pos_y = Boom.y;
	send(*client_socket, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
}

void send_hit_packet(SOCKET* client_socket, int client_id, int bomb_id)
{
	sc_packet_hit packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_HIT;
	packet.id = client_id;
	packet.bomb_id = bomb_id;
	send(*client_socket, reinterpret_cast<const char*>(&packet), packet.size, 0);
}

void send_life_count_packet(SOCKET* client_socket, int client_id, int lifecount)
{
	sc_packet_life_count packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_HIT;
	packet.id = client_id;
	packet.lifeCount = lifecount;
	send(*client_socket, reinterpret_cast<const char*>(&packet), packet.size, 0);
}