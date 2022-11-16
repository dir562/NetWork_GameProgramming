//#include "..\..\Common.h"
#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <stdio.h> // printf(), ...
#include<iostream>

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#define BUFSIZE 1024
#define SERVERPORT 9000

using namespace std;

HANDLE			hSendEvent;
HANDLE			hCalculateEvent;

int				thread_count = 0; // 몇개 클라가 접속했는지

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

	int retval; // 오류 검출 변수
	// 전달된 소켓 저장
	//
	SOCKET client_sock = (SOCKET)arg;
	char* buf;
	int len;
	// 접속패킷전달
	//send_login_ok_packet();

	// 클라이언트와 데이터 통신
	while (1) {
		retval = recv(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "강제 연결 끊김" << endl;
			//사망시 보내줄패킷전달
			//send_dead_packet();
		}

	}

	while (1) {		// 죽으면 보내주는것을 받기는 하지만 처리는 해주지 말자
		retval = recv(client_sock, buf, len, 0);
	}
	closesocket(client_sock);
	return 0;
}
