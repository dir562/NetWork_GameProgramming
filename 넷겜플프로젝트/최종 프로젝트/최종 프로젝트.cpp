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

UINT wDeviceID = 0;

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
HWND hState;
HWND hPauseChild;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = PauseChildProc;
	WndClass.lpszClassName = "PauseChild";
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_SAVEBITS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 675, 775,
		NULL, (HMENU)NULL, hInstance, NULL);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 675, 775,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
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
typedef struct _Boom {
	int x;
	int y;
	int speed;
	bool be;
} Boom;
Boom ass[300];

HBITMAP hBufBit;
HBITMAP hBit[11];
HBITMAP gBit;
HBITMAP gBitmap;
int nx = 110;
int c = 0;
int count = 0;
bool MoveL = FALSE;
bool MoveR = FALSE;
int Score = 0;
int Time = 0;
int RankScore = 0;
bool isGameRunning = FALSE;
bool bPause = FALSE;
bool bFade = TRUE;
bool bdead = FALSE;
HDC gMemDC;
HBITMAP Gbit;
static HBITMAP oBitmap;
static HBITMAP hBis[3];
static HBITMAP Backg;
static HBITMAP Mok;
static BOOL Menu = TRUE;
static BOOL Help = FALSE;
static HBITMAP sp;
static HBITMAP sps;

static BOOL easy = TRUE;
static BOOL Normal = FALSE;
static BOOL Hard = FALSE;
static BOOL Hell = FALSE;

static BOOL on = TRUE;
static BOOL tw = FALSE;
static BOOL thr = FALSE;
static BOOL four = FALSE;

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
		case ID_40001:
			MessageBox(hWndMain, "이지모드.", "알림", MB_OK);
			easy = TRUE;
			Normal = FALSE;
			Hard = FALSE;
			Hell = FALSE;
			break;
		case ID_40002:
			MessageBox(hWndMain, "노말모드.", "알림", MB_OK);
			easy = FALSE;
			Normal = TRUE;
			Hard = FALSE;
			Hell = FALSE;
			break;
		case ID_40003:
			MessageBox(hWndMain, "하드모드.", "알림", MB_OK);
			easy = FALSE;
			Normal = FALSE;
			Hard = TRUE;
			Hell = FALSE;
			break;
		case ID_40004:
			MessageBox(hWndMain, "헬모드.", "알림", MB_OK);
			easy = FALSE;
			Normal = FALSE;
			Hard = FALSE;
			Hell = TRUE;
			break;
		case ID_40005:
			on = TRUE;
			tw = FALSE;
			thr = FALSE;
			break;
		case ID_40006:
			MessageBox(hWndMain, "미사일 2배.", "알림", MB_OK);
			on = FALSE;
			tw = TRUE;
			thr = FALSE;
			break;
		case ID_40007:
			MessageBox(hWndMain, "미사일 3배.", "알림", MB_OK);
			on = FALSE;
			tw = FALSE;
			thr = TRUE;
			break;
		case ID_40015:
			MessageBox(hWndMain, "시작.", "알림", MB_OK);
			if (!isGameRunning)
			{

				for (int i = 0; i < 300; i++) {
					ass[i].be = FALSE;
				}
				bdead = FALSE;
				Score = 0;
				Time = 0;

				nx = 110;
				SetTimer(hWnd, 1, 10, NULL);
				SetTimer(hWnd, 2, 200, NULL);
				SetTimer(hWnd, 5, 1000, NULL);
				isGameRunning = TRUE;
			}
			break;
		case ID_40016:
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
			break;

		case ID_40017:
			MessageBox(hWndMain, "게임이 종료되었습니다.", "알림", MB_OK);
			PostQuitMessage(0);
			break;
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
		hWndMain = hWnd;
		SetWindowPos(hPauseChild, NULL, 625 / 2 - 100, 1000 / 2 - 100, 200, 100, SWP_NOZORDER);
		ShowWindow(hPauseChild, SW_SHOW);
		oBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		srand((unsigned int)time(NULL));

		for (int i = 0; i < 11; i++) {
			hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		}
		for (int h = 0; h < 3; h++)
		{
			hBis[h] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13 + h));
		}
		Backg = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
		Mok = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));

		sp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
		sps = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));

		memset(&ass, 0, sizeof(Boom));

		SetTimer(hWnd, 0, 100, NULL);

		SetTimer(hWnd, 3, 1, NULL);
		SetTimer(hWnd, 4, 1, NULL);
		SetTimer(hWnd, 6, 1, NULL);
		SetTimer(hWnd, 8, 1, NULL);

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
			c++;
			if (c > 2)
				c = 0;
			DoubleBuffering();
			break;
		case 1:
			for (int i = 0; i < 300; i++)
			{
				if (ass[i].be == TRUE)
				{
					ass[i].y += ass[i].speed;
					if (((ass[i].x < nx + 15 && nx + 15 < ass[i].x + 20) || (ass[i].x < nx && nx < ass[i].x + 20)) && ass[i].y > 600)
					{

						bdead = TRUE;
						KillTimer(hWnd, 5);
						KillTimer(hWnd, 1);
						KillTimer(hWnd, 2);
						isGameRunning = FALSE;
						MoveR = FALSE;
						MoveL = FALSE;
						TCHAR buf[10]{ 0 };
						_itoa_s(RankScore, buf, 10);

						MessageBox(hWndMain, "죽었습니다. Space bar를 누르시면 재시작 합니다.", "알림", MB_OK);
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
			break;
		case 2:
			MakeBoom();
			break;
		case 3:
			if (MoveL) // 캐릭터 이동......
			{
				nx -= 3;
				if (nx < 0)
					nx = 0;
			}
			break;
		case 4:
			if (MoveR) // 캐릭터 이동.... 
			{
				nx += 3;
				if (nx > 625)
					nx = 625;
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

		}
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {

		case 'H':
			if (Help == FALSE)
			{
				Help = TRUE;
			}
			else if (Help == TRUE)
			{
				Help = FALSE;
			}
			break;
		case 'P':
			Menu = FALSE;
			Help = FALSE;
			break;
		case VK_LEFT:

			if (!bdead)
			{

				MoveL = TRUE;
			}

			break;
		case VK_RIGHT:

			if (!bdead)
			{

				MoveR = TRUE;
			}
			break;
		case VK_SPACE:
			if (!isGameRunning)
			{

				for (int i = 0; i < 300; i++) {
					ass[i].be = FALSE;
				}
				bdead = FALSE;
				Score = 0;
				Time = 0;

				nx = 110;
				SetTimer(hWnd, 1, 10, NULL);
				SetTimer(hWnd, 2, 200, NULL);
				SetTimer(hWnd, 5, 1000, NULL);
				isGameRunning = TRUE;
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

			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam) {
		case VK_LEFT:
			MoveL = FALSE;
			break;
		case VK_RIGHT:
			MoveR = FALSE;
			break;
		}

		count = 0;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawBitmap(hdc, 0, 0, hBufBit);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		for (int i = 0; i < 4; i++) {
			DeleteObject(hBit[i]);
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
	DrawBitmap(hMemDC, 0, 625, Mok);
	DrawBitmap(hMemDC, 122, 625, Mok);
	DrawBitmap(hMemDC, 244, 625, Mok);
	DrawBitmap(hMemDC, 366, 625, Mok);
	DrawBitmap(hMemDC, 488, 625, Mok);
	DrawBitmap(hMemDC, 610, 625, Mok);

	DrawBitmap(hMemDC, 100, 0, hBis[2]);
	DrawBitmap(hMemDC, 200, 0, hBis[2]);
	DrawBitmap(hMemDC, 300, 0, hBis[2]);
	DrawBitmap(hMemDC, 400, 0, hBis[2]);
	DrawBitmap(hMemDC, 500, 0, hBis[2]);


	for (int i = 0; i < 100; i++)
	{
		if (ass[i].be == TRUE)
		{
			//DrawBitmap(hMemDC, ass[i].x, ass[i].y, hBit[3]);
			TransBlt(hMemDC, ass[i].x, ass[i].y, hBit[3], RGB(255, 0, 0));
		}
	}

	if (MoveL)
		DrawBitmap(hMemDC, nx, 625, hBit[4 + c]);
	else if (MoveR)
		DrawBitmap(hMemDC, nx, 625, hBit[7 + c]);
	else if (!bdead)
		DrawBitmap(hMemDC, nx, 625, hBit[c]);
	else
		TransBlt(hMemDC, nx, 625, hBit[10], RGB(255, 0, 0));

	DrawBitmap(hMemDC, 0, 675, oBitmap);

	if (Menu == TRUE)
	{
		DrawBitmap(hMemDC, -60, 0, sp);
		if (Help == TRUE && Menu == TRUE)
		{
			DrawBitmap(hMemDC, -10, 0, sps);
		}
	}
	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);
	InvalidateRect(hWndMain, NULL, FALSE);
}
void MakeBoom(void)
{
	int x, y;
	x = rand() % 625 + 1;
	y = 50;

	if (on == TRUE && tw == FALSE && thr == FALSE)
	{
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
	else if (on == FALSE && tw == TRUE && thr == FALSE)
	{
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
	else if (thr == TRUE && tw == FALSE && on == FALSE)
	{
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

	/// <summary>
	///  난이도에 따른 속도 변화.
	/// </summary>
	/// <param name=""></param>


	/// <summary>
	///  미사일 배수 조정
	/// </summary>
	/// <param name=""></param>
	if (on == TRUE)
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
	else if (tw == TRUE)
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
	else if (thr == TRUE)
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
	HDC  hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)& bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

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

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

