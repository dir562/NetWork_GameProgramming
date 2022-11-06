// 최종 프로젝트.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "최종 프로젝트.h"
#include "resource1.h"


#include <windows.h>
#include "resource.h"
#include <time.h>
#include <math.h>
#include <MMSystem.h>
#include <Digitalv.h>
#include "resource1.h"
#include "global.h"



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PauseChildProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("패닉의 생존");

void DoubleBuffering(void);
void MakeBoom(void);

void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask);



INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	HMENU D_menu;
	g_hInst = hInstance;

		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = hInstance;
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		WndClass.lpszMenuName = NULL;
		

	
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&WndClass);
		WndClass.lpszMenuName = MAKEINTRESOURCE(IDC_MY);
		WndClass.lpfnWndProc = PauseChildProc;
		WndClass.lpszClassName = "PauseChild";



		WndClass.style = CS_SAVEBITS;
		RegisterClass(&WndClass);
	



	    D_menu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MY));
		hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			0, 0, 675, 775,
			NULL, NULL, hInstance, NULL);
		ShowWindow(hWnd, nCmdShow);



//		hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
//			0, 0, 675, 775,
//			NULL, (HMENU)NULL, hInstance, NULL);


	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

////////////////////////////////////////////////////////////
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);

	DeleteDC(MemDC);
}


void Easy_Mode()
{
	int x, y;
	x = rand() % 625 + 1;
	y = 50;
	for (int i = 0; i < 300; i++)
	{
		if (ass[i].be == FALSE)
		{
			ass[i].be = TRUE;
			ass[i].x = x;
			ass[i].y = y;
			if (easy == TRUE)
			{
				ass[i].speed = 1 + rand() % 3 + 1;
			}
			else if (Normal == TRUE)
			{
				ass[i].speed = 5 + rand() % 9 + 1;
			}
			else if (Hard == TRUE)
			{
				ass[i].speed = 11 + rand() % 13 + 1;
			}
			else if (Hell == TRUE)
			{
				ass[i].speed = 15 + rand() % 20 + 1;
			}
			break;
		}
	}
}

void Normal_Mode()
{

	int x, y;
	x = rand() % 625 + 1;
	y = 50;
	for (int i = 0; i < 300; i++)
	{
		if (ass[i].be == FALSE)
		{
			ass[i].be = TRUE;
			ass[i].x = x;
			ass[i].y = y;
			if (easy == TRUE)
			{

				ass[i].speed = 3 + rand() % 4 + 1;
				ass[i].speed = 3 + rand() % 4 + 1;

			}
			else if (Normal == TRUE)
			{
				ass[i].speed = 4 + rand() % 6 + 1;
				ass[i].speed = 4 + rand() % 6 + 1;
			}
			else if (Hard == TRUE)
			{
				ass[i].speed = 7 + rand() % 9 + 1;
				ass[i].speed = 7 + rand() % 9 + 1;
			}
			else if (Hell == TRUE)
			{
				ass[i].speed = 9 + rand() % 13 + 1;
				ass[i].speed = 9 + rand() % 13 + 1;
			}
			break;
		}
	}
}

void Hard_Mode()
{
	int x, y;
	x = rand() % 625 + 1;
	y = 50;
	for (int i = 0; i < 300; i++)
	{
		if (ass[i].be == FALSE)
		{
			ass[i].be = TRUE;
			ass[i].x = x;
			ass[i].y = y;
			if (easy == TRUE)
			{
				ass[i].speed = 3 + rand() % 4 + 1;
				ass[i].speed = 3 + rand() % 4 + 1;
				ass[i].speed = 3 + rand() % 4 + 1;
			}
			else if (Normal == TRUE)
			{
				ass[i].speed = 4 + rand() % 6 + 1;
				ass[i].speed = 4 + rand() % 6 + 1;

				ass[i].speed = 4 + rand() % 6 + 1;
			}
			else if (Hard == TRUE)
			{

				ass[i].speed = 7 + rand() % 9 + 1;
				ass[i].speed = 7 + rand() % 9 + 1;
				ass[i].speed = 7 + rand() % 9 + 1;

			}
			else if (Hell == TRUE)
			{

				ass[i].speed = 9 + rand() % 13 + 1;
				ass[i].speed = 9 + rand() % 13 + 1;
				ass[i].speed = 9 + rand() % 13 + 1;

			}
			break;
		}
	}
}

void Many_things()
{
	int x, y;
	x = rand() % 625 + 1;
	y = 50;

	if (one == TRUE)
	{
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
	}
	else if (two == TRUE)
	{
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
	}
	else if (three == TRUE)
	{
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
		for (int i = 0; i < 300; i++)
		{
			if (ass[i].be == FALSE)
			{
				ass[i].be = TRUE;
				ass[i].x = x;
				ass[i].y = y;


				ass[i].speed = 6 + rand() % 8 + 1;

				break;
			}
		}
	}
}


void make_easy_by_toolbar()
{
	MessageBox(hWndMain, "이지모드.", "알림", MB_OK);
	easy = TRUE;
	Normal = FALSE;
	Hard = FALSE;
	Hell = FALSE;
}

void make_normal_by_toolbar()
{
	MessageBox(hWndMain, "노말모드.", "알림", MB_OK);
	easy = FALSE;
	Normal = TRUE;
	Hard = FALSE;
	Hell = FALSE;
}

void make_hard_by_toolbar()
{
	MessageBox(hWndMain, "하드모드.", "알림", MB_OK);
	easy = FALSE;
	Normal = FALSE;
	Hard = TRUE;
	Hell = FALSE;
}

void make_hell_by_toolbar()
{
	MessageBox(hWndMain, "헬모드.", "알림", MB_OK);
	easy = FALSE;
	Normal = FALSE;
	Hard = FALSE;
	Hell = TRUE;
}	




void Pause_and_Resume(HWND hWnd)
{
	if (!isGameRunning)
	{

		for (int i = 0; i < 300; i++) {
			ass[i].be = FALSE;
		}
		bdead = FALSE;
		Score = 0;
		Time = 0;

		player1.x = 110;
		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 200, NULL);
		SetTimer(hWnd, 5, 1000, NULL);
		isGameRunning = TRUE;
		GameKey_On = FALSE;
	}
	else if (isGameRunning)
	{
		if (bPause) {
			bPause = FALSE;
			SetTimer(hWnd, 1, 10, NULL);
			SetTimer(hWnd, 2, 200, NULL);
			SetTimer(hWnd, 5, 1000, NULL);
			KillTimer(hWnd, 7);
			ShowWindow(hPauseChild, SW_HIDE);
		}
		else {
			bPause = TRUE;
			bFade = TRUE;
			SetTimer(hWnd, 7, 1000, NULL);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 5);
		}
	}
}


void Game_Setting(HWND hWnd)
{
	hWndMain = hWnd;
	SetWindowPos(hPauseChild, NULL, 625 / 2 - 100, 1000 / 2 - 100, 200, 100, SWP_NOZORDER);
	ShowWindow(hPauseChild, SW_SHOW);
	oBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 11; i++) {
		hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}
	for (int i = 0; i < 11; i++)
	{
		hBit2[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24 + i));
	}
	for (int h = 0; h < 3; h++)
	{
		hLauncher[h] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13 + h));
	}
	Backg = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
	CrossHair = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));

	menu = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
	help = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
	hHeart1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
	hHeart2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
	hHeart3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
	hHeart4 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP35));

	

	memset(&ass, 0, sizeof(Boom));

	SetTimer(hWnd, 0, 100, NULL);

	SetTimer(hWnd, 3, 1, NULL);
	SetTimer(hWnd, 4, 1, NULL);
	SetTimer(hWnd, 6, 1, NULL);
	SetTimer(hWnd, 8, 1, NULL);
	SetTimer(hWnd, 9, 1, NULL);

}

void Pause_by_toolbar(HWND hWnd)
{
	MessageBox(hWndMain, "시작.", "알림", MB_OK);
	if (!isGameRunning)
	{

		for (int i = 0; i < 300; i++) {
			ass[i].be = FALSE;
		}
		bdead = FALSE;
		Score = 0;
		Time = 0;

		player1.x = 110;
		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 200, NULL);
		SetTimer(hWnd, 5, 1000, NULL);
		isGameRunning = TRUE;
	}
}

void Resume_by_toolbar(HWND hWnd)
{
	MessageBox(hWndMain, "일시정지 및 다시시작", "알림", MB_OK);
	if (isGameRunning)
	{
		if (bPause) {
			bPause = FALSE;
			SetTimer(hWnd, 1, 10, NULL);
			SetTimer(hWnd, 2, 200, NULL);
			SetTimer(hWnd, 5, 1000, NULL);
			KillTimer(hWnd, 7);
			ShowWindow(hPauseChild, SW_HIDE);
		}
		else {
			bPause = TRUE;
			bFade = TRUE;
			SetTimer(hWnd, 7, 1000, NULL);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 5);
		}
	}
}


void Game_Cycle(HWND hWnd) {
	for (int i = 0; i < 300; i++)
	{
		if (ass[i].be == TRUE)
		{
			ass[i].y += ass[i].speed;
			if (((ass[i].x < player1.x + 15 && player1.x + 15 < ass[i].x + 20) || (ass[i].x < player1.x && player1.x < ass[i].x + 20)) && ass[i].y > 600)
			{

				bdead = TRUE;
				KillTimer(hWnd, 5);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				isGameRunning = FALSE;
				Player1_MoveR = FALSE;
				Player1_MoveL = FALSE;
			
				TCHAR buf[10]{ 0 };
				_itoa_s(RankScore, buf, 10);

				MessageBox(hWndMain, "죽었습니다. Space bar를 누르시면 재시작 합니다.", "알림", MB_OK);
				GameKey_On = TRUE;
			}
			if (ass[i].y > 625)
			{
				memset(&ass[i], 0, sizeof(Boom));
				memset(&ass[i], 0, sizeof(Boom));
				memset(&ass[i], 0, sizeof(Boom));
				if (isGameRunning)
				{
					Score += 1;
					if (Score > RankScore)
						RankScore++;

				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////// 이 아래가 본 함수, 위는 함수 쪼갠거
//// 이 아래가 게임 작동하는 부분.


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int SBPart[3];


	switch (iMsg) {
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_32775:
			MessageBox(hWndMain, "게임이 종료되었습니다.", "알림", MB_OK);
			PostQuitMessage(0);
			break;
		/*case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;*/
		default:
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
		Game_Setting(hWnd);
		return 0;
	case WM_SIZE:
		for (int i = 0; i < 3; i++)
		{
			SBPart[i] = LOWORD(lParam) / 3 * (i + 1);
		}


		return 0;
	case WM_TIMER:
		switch (wParam) {
		case 0:
		//	c++;
		//	if (c > 2)
		//		c = 0;
		//	DoubleBuffering();
			break;
		case 1:
			Game_Cycle(hWnd);
			break;
		case 2:
			MakeBoom();
			break;
		case 3:
			if (Player1_MoveL&&isGameRunning==TRUE&&bPause == FALSE) // 캐릭터 이동......
			{
				player1.x -= 3;
				if (player1.x < 0)
					player1.x = 0;
				
			}
	
			break;
		case 4:
			if (Player1_MoveR&&isGameRunning==TRUE&&bPause == FALSE) // 캐릭터 이동.... 
			{
				player1.x += 3;
				if (player1.x > 625)
					player1.x = 625;
			}	

			break;
		case 5:

			Time++;
			break;
		case 6:
			DoubleBuffering();
			break;
		case 7:
			if (bFade)
			{
				ShowWindow(hPauseChild, SW_HIDE);
				bFade = !bFade;
			}
			else
			{
				ShowWindow(hPauseChild, SW_SHOW);
				bFade = !bFade;
			}
			break;
		case 8:
			if (Player2_MoveL&& isGameRunning == TRUE && bPause == FALSE) // 캐릭터 이동......
			{
				player2.x -= 3;
//				if (player2.x < 0)
	//				player2.x = 0;

			}
			break;
		case 9:
			if (Player2_MoveR && isGameRunning == TRUE && bPause == FALSE) // 캐릭터 이동.... 
			{
				player2.x += 3;
				if (player2.x > 625)
					player2.x = 625;
			}

			break;
		}

		return 0;
	case WM_KEYDOWN:
		switch (wParam) {

		case 'H':
			if (isHelp == FALSE)
			{
				isHelp = TRUE;
			}
			else if (isHelp == TRUE)
			{
				isHelp = FALSE;
			}
			break;
		case 'P':
			isMenu = FALSE;
			isHelp = FALSE;
			break;
		case 'Q':
			if (GameKey_On)
			{
				make_easy_by_toolbar();
			}
			break;
		case 'W':
			if (GameKey_On)
			{
				make_normal_by_toolbar();
			}
			break;
		case 'E':
			if (GameKey_On)
			{
				make_hard_by_toolbar();
			}
			break;
		case 'R':
			if (GameKey_On)
			{
				make_hell_by_toolbar();
			}
			break;
		case VK_LEFT:

			if (!bdead)
			{

				Player1_MoveL = TRUE;
			}

			break;
		case VK_RIGHT:
			if (!bdead)
			{

				Player1_MoveR = TRUE;
			}
			break;
		case VK_NUMPAD4:
			if (!bdead)
			{
				Player2_MoveL = TRUE;
				
			}
			break;
		case VK_NUMPAD6:
			if (!bdead)
			{
				Player2_MoveR = TRUE;

			}
			break;
		case VK_SPACE:
			Pause_and_Resume(hWnd);
			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam) {
		case VK_LEFT:
			Player1_MoveL = FALSE;
			break;
		case VK_RIGHT:
			Player1_MoveR = FALSE;
			break;
		case VK_NUMPAD4:
			Player2_MoveL = FALSE;
			break;
		case VK_NUMPAD6:
			Player2_MoveR = FALSE;
			break;
		}
	
		count = 0;
		count2 = 0;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawBitmap(hdc, 0, 0, hBufBit);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		for (int i = 0; i < 4; i++) {
			DeleteObject(hBit[i]);
			DeleteObject(hBit2[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}
void DoubleBuffering(void)
{
	RECT crt;
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	GetClientRect(hWndMain, &crt);
	hdc = GetDC(hWndMain);


	if (hBufBit == NULL)
		hBufBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBufBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	DrawBitmap(hMemDC, 0, 0, Backg);
	DrawBitmap(hMemDC, 0, 625, CrossHair);
	DrawBitmap(hMemDC, 122, 625, CrossHair);
	DrawBitmap(hMemDC, 244, 625, CrossHair);
	DrawBitmap(hMemDC, 366, 625, CrossHair);
	DrawBitmap(hMemDC, 488, 625, CrossHair);
	DrawBitmap(hMemDC, 610, 625, CrossHair);

	DrawBitmap(hMemDC, 0, 24, hHeart1);
	DrawBitmap(hMemDC, 60, 24, hHeart2);
	DrawBitmap(hMemDC, 120, 24, hHeart3);


//	DrawBitmap(hMemDC, 100, 0, hLauncher[2]);
//	DrawBitmap(hMemDC, 200, 0, hLauncher[2]);
//	DrawBitmap(hMemDC, 300, 0, hLauncher[2]);
//	DrawBitmap(hMemDC, 400, 0, hLauncher[2]);
//	DrawBitmap(hMemDC, 500, 0, hLauncher[2]);
//	DrawBitmap(hMemDC, 600, 0, hLauncher[2]);

	for (int i = 0; i < 100; i++)
	{
		if (ass[i].be == TRUE)
		{
			//DrawBitmap(hMemDC, ass[i].x, ass[i].y, hBit[3]);
			TransBlt(hMemDC, ass[i].x, ass[i].y, hBit[3], RGB(255, 0, 0));
		}
	}



	if (Player1_MoveL)
		DrawBitmap(hMemDC, player1.x , 625, hBit[4 + count]);
	else if (Player1_MoveR)
		DrawBitmap(hMemDC, player1.x, 625, hBit[7 + count]);
	else if (!bdead)
		DrawBitmap(hMemDC, player1.x, 625, hBit[count]);
	else
		TransBlt(hMemDC, player1.x, 625, hBit[10], RGB(255, 0, 0));

	if (Player2_MoveL)
		DrawBitmap(hMemDC, player2.x+300, 625, hBit2[4 + count2]);
	else if (Player2_MoveR)
		DrawBitmap(hMemDC, player2.x+300, 625, hBit2[7 + count2]);
	else if (!bdead)
		DrawBitmap(hMemDC, player2.x+300, 625, hBit2[count2]);
	else
		TransBlt(hMemDC, player2.x+300, 625, hBit2[10], RGB(255, 0, 0));

	DrawBitmap(hMemDC, 0, 675, oBitmap);

	if (isMenu == TRUE)
	{
		DrawBitmap(hMemDC, -60, 0, menu);
		if (isHelp == TRUE && isMenu == TRUE)
		{
			DrawBitmap(hMemDC, -10, 0, help);
		}
	}


	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);
	InvalidateRect(hWndMain, NULL, FALSE);
}
void MakeBoom(void)
{


	if (one == TRUE && two == FALSE && three == FALSE)
	{
		Easy_Mode();
	}
	else if (one == FALSE && two == TRUE && three == FALSE)
	{
		Normal_Mode();
	}
	else if (three == TRUE && two == FALSE && one == FALSE)
	{
		Hard_Mode();
	}

	Many_things();

	/// <summary>
	///  미사일 배수 조정
	/// </summary>
	/// <param name=""></param>


	/// 
}

LRESULT CALLBACK PauseChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;



	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HBITMAP bmHeart1, bmHeart2, bmHeart3;
	HBITMAP bmHeart1Old, bmHeart2Old, bmHeart3Old;

	HDC  hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	HDC hdcheart;
	POINT ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);
	hdcheart = CreateCompatibleDC(hdc);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmHeart1 = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmHeart2 = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmHeart3 = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	bmHeart1Old = (HBITMAP)SelectObject(hdcheart, bmHeart1);
	bmHeart2Old = (HBITMAP)SelectObject(hdcheart, bmHeart2);
	bmHeart3Old = (HBITMAP)SelectObject(hdcheart, bmHeart3);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, clrMask);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, x, y, SRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
	BitBlt(hdc, x, y, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);
	BitBlt(hdcheart, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));
	DeleteObject(SelectObject(hdcheart, bmHeart1Old));
	DeleteObject(SelectObject(hdcheart, bmHeart2Old));
	DeleteObject(SelectObject(hdcheart, bmHeart3Old));

	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
	DeleteDC(hdcheart);
}


int main()
{
	
}