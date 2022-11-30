#include "stdafx.h"
#include "Net_Connect.h"

WSADATA wsa;
SOCKET sock;
SOCKADDR_IN serveraddr;


int my_id = 0;
int retval = 0;
char send_buf[BUFSIZE];
char recv_buf[BUFSIZE];
bool start_game = true;
static bool Player1_MoveL = FALSE;
static bool Player1_MoveR = FALSE;
static bool Player2_MoveL = FALSE;
static bool Player2_MoveR = FALSE;
int n_hp = 3;

void err_display(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL);

	cout << "[" << msg << "] " << (char*)lpMsgBuf << endl;
	LocalFree(lpMsgBuf);
}

void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL);

	MessageBox(NULL, (LPTSTR)lpMsgBuf, (LPTSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

int netInit()
{
	const char* SERVERIP;
	SERVERIP = "127.0.0.1";
	//SERVERIP = "210.99.123.68";
	// 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVERIP);
	int ret = connect(sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
	if (ret == SOCKET_ERROR) {
		int err_num = WSAGetLastError();
		cout << " EROOR : Connect " << endl;
		err_quit("connect()");
	}

}

int netclose()
{
	// close socket()
	closesocket(sock);

	// 윈속종료
	WSACleanup();
	return 0;
}

void do_send(int num_bytes, void* mess)
{
	ZeroMemory(&send_buf, sizeof(send_buf));
	memcpy(send_buf, mess, num_bytes);

	retval = send(sock, send_buf, num_bytes, 0);
	if (retval == SOCKET_ERROR) { err_display("SEND()"); }
}

DWORD WINAPI do_recv(LPVOID arg)
{

	while (true) {
		retval = recv(sock, recv_buf, sizeof(recv_buf), 0);
		if (retval == SOCKET_ERROR) { err_display("RECV()");  return 0; }
		char* p = recv_buf;
		while (p < recv_buf + retval) {
			unsigned char packet_size = *p;
			char type = *(p + 1);
			if (packet_size <= 0) break;
			switch (type) {
			case SC_PACKET_START_GAME: {
				// 이제 렌더링을 시작
				start_game = true;
				break;
			}
			case SC_PACKET_MOVE: {
				cs_Player_packet_move packet;
				packet.size = sizeof(packet);
				packet.type = SC_PACKET_MOVE;
				if (packet.direction == VK_LEFT) {
					if (n_hp != 0)
					{
						Player1_MoveL = TRUE;
						Player2_MoveL = TRUE;
					}
				}
				if (packet.direction == VK_RIGHT)
				{
					if (n_hp != 0) {
						Player1_MoveR = TRUE;
						Player2_MoveR = TRUE;
					}
				}
				break;
			}
		    }
			p = p + packet_size;
		}

	}
	return 0;

}

bool get_start_game()
{
	return start_game;
}