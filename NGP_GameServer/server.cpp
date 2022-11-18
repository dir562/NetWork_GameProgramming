//#include "..\..\Common.h"
#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <stdio.h> // printf(), ...
#include<iostream>
#include"global.h"

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

#define BUFSIZE 1024
#define SERVERPORT 9000

using namespace std;

HANDLE			hSendEvent;
HANDLE			hCalculateEvent;

int				thread_count = 0; // � Ŭ�� �����ߴ���


//�Լ�
void send_start_game_packet(SOCKET* client_socket, int client_id);				// ������ �����ϸ� ��� Ŭ���̾�Ʈ���� ��Ŷ ����	

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
	int retval;		// ���� ���� ����

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int addrlen;

	// �̺�Ʈ ��� �غ�

	hSendEvent = CreateEvent(NULL, FALSE, TRUE, NULL);		// �ܼ�â�� ���°��� ���ȣ�� ����
	if (hSendEvent == NULL) return 1;
	hCalculateEvent = CreateEvent(NULL, FALSE, TRUE, NULL);		// �ܼ�â�� ���°��� ���ȣ�� ����
	if (hCalculateEvent == NULL) return 1;

	//������ ����
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

	//���ӽ�ŸƮ
	//gameStart();
}

DWORD WINAPI ProcessClient(LPVOID arg)
{

	int retval; // ���� ���� ����
	// ���޵� ���� ����
	//
	SOCKET client_sock = (SOCKET)arg;
	char* buf;
	int len;
	// ������Ŷ����
	//send_login_ok_packet();

	// Ŭ���̾�Ʈ�� ������ ���
	while (1) {
		retval = recv(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "���� ���� ����" << endl;
			//����� ��������Ŷ����
			//send_dead_packet();
		}

	}

	while (1) {		// ������ �����ִ°��� �ޱ�� ������ ó���� ������ ����
		retval = recv(client_sock, buf, len, 0);
	}
	closesocket(client_sock);
	return 0;
}

void send_start_game_packet(SOCKET* client_socket, int client_id)
{
	sc_packet_start_game packet;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_START_GAME;
	send(*client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
}
