
#pragma once

#include "protocol.h"
// #include "Player.h"
#include <array>


const int BUFSIZE = 2048;
void err_quit(const char* msg);

void err_display(const char* msg);

int netInit();

int netclose();

void do_send(int num_bytes, void* mess);

DWORD WINAPI do_recv(LPVOID arg);


bool get_start_game();