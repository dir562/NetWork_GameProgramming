#pragma once
#pragma comment(lib, "ws2_32")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include<unordered_map>
#include <chrono>
#include <thread>
#include <array>
#include "global.h"

#define BUFSIZE 2048
#define NOBJECTS 42
using namespace std;


//�� �ٽ� �����;���

const int wall_width = 50;
const int wall_height = 50;

const int player_width = 50;
const int player_height = 50;


