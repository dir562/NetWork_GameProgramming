HWND hState;
HWND hPauseChild;

typedef struct _Boom {
	int x;
	int y;
	int speed;
	bool be;
} Boom;

typedef struct _player {
	int x =110;
	int y;
}Player;

typedef struct _player2 {
	int x= 775;
	int y;
}Player_s;

Player player1;
Player_s player2;


int speeds_2 = 3;

Boom ass[300];

HBITMAP hBufBit;
HBITMAP hBit[11];
HBITMAP hBit2[11];
HBITMAP gBit;
HBITMAP gBitmap;
//int nx = 110;
//int c = 0;
int count = 0;
int count2 = 0;
bool Player1_MoveL = FALSE;
bool Player1_MoveR = FALSE;
bool Player2_MoveL = FALSE;
bool Player2_MoveR = FALSE;
int Score = 0;
int Time = 0;
int RankScore = 0;
bool isGameRunning = FALSE;
bool bPause = FALSE;
bool bFade = TRUE;
bool bdead = FALSE;
bool bdead_2 = FALSE;
HDC gMemDC;
HBITMAP Gbit;
static HBITMAP oBitmap;
static HBITMAP hLauncher[3];
static HBITMAP hHeart1;
static HBITMAP hHeart2;
static HBITMAP hHeart3;
static HBITMAP hHeart4;
static HBITMAP Backg;
static HBITMAP CrossHair;
static BOOL isMenu = TRUE;
static BOOL isHelp = FALSE;
static HBITMAP menu;
static HBITMAP help;

static BOOL easy = TRUE;
static BOOL Normal = FALSE;
static BOOL Hard = FALSE;
static BOOL Hell = FALSE;

static BOOL one = TRUE;
static BOOL two = FALSE;
static BOOL three = FALSE;
static BOOL four = FALSE;


static BOOL GameKey_On = TRUE;
UINT wDeviceID = 0;