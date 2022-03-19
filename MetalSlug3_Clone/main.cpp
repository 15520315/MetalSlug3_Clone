/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Marco.h"


#define WINDOW_CLASS_NAME L"MetalSlugWindow"
#define MAIN_WINDOW_TITLE L"MetalSlug03_Clone"
#define WINDOW_ICON_PATH L"metalslug3.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARCO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARCO TEXTURES_DIR "\\marco.gif"
//#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
//#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"

CMarco *marco;
#define MARCO_START_X 10.0f
#define MARCO_START_Y 130.0f
#define MARCO_START_VX 0.2f

CMarcoLeg *marcoleg;
#define MARCOLEG_START_X 10.0f
#define MARCOLEG_START_Y 145.0f
#define MARCOLEG_START_VX 0.2f




LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARCO, TEXTURE_PATH_MARCO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));


	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texMarco = textures->Get(ID_TEX_MARCO);

	// readline => id, left, top, right, bottom 

	sprites->Add(10001, 13, 149, 45, 177, texMarco);
	sprites->Add(10002, 47, 148, 77, 177, texMarco);
	sprites->Add(10003, 79, 148, 107, 176, texMarco);
	sprites->Add(10004, 109, 149, 136, 176, texMarco); 
	sprites->Add(10005, 139, 149, 168, 177, texMarco); 
	sprites->Add(10006, 171, 149, 201, 177, texMarco); 
	sprites->Add(10007, 204, 149, 236, 178, texMarco); 
	sprites->Add(10008, 239, 149, 271, 178, texMarco); 
	sprites->Add(10009, 274, 149, 306, 177, texMarco); 
	sprites->Add(10010, 308, 149, 339, 176, texMarco);  
	sprites->Add(10011, 342, 149, 373, 177, texMarco); 
	sprites->Add(10012, 376, 149, 407, 177, texMarco);

	sprites->Add(10020, 256, 1533, 277, 1553, texMarco);
	sprites->Add(10021, 280, 1533, 308, 1553, texMarco);
	sprites->Add(10022, 311, 1533, 342, 1549, texMarco);
	sprites->Add(10023, 345, 1533, 364, 1553, texMarco);
	sprites->Add(10024, 367, 1533, 382, 1553, texMarco);
	sprites->Add(10024, 385, 1533, 401, 1553, texMarco);
	sprites->Add(10026, 404, 1533, 425, 1553, texMarco);
	sprites->Add(10027, 428, 1533, 454, 1553, texMarco);
	sprites->Add(10028, 457, 1533, 488, 1549, texMarco);
	sprites->Add(10029, 491, 1533, 511, 1533, texMarco);
	sprites->Add(10030, 513, 1533, 528, 1533, texMarco);
	sprites->Add(10031, 530, 1533, 548, 1533, texMarco);
	sprites->Add(10032, 551, 1533, 572, 1533, texMarco);
	sprites->Add(10033, 576, 1533, 600, 1533, texMarco);
	sprites->Add(10034, 603, 1533, 617, 1533, texMarco);
	sprites->Add(10035, 621, 1533, 640, 1533, texMarco);
	sprites->Add(10036, 644, 1533, 670, 1533, texMarco);
	sprites->Add(10037, 674, 1533, 690, 1533, texMarco);



	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	ani->Add(10009);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10020);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10024);
	ani->Add(10025);
	ani->Add(10026);
	ani->Add(10027);
	ani->Add(10028);
	ani->Add(10029);
	ani->Add(10030);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	ani->Add(10034);
	ani->Add(10035);
	ani->Add(10036);
	ani->Add(10037);
	ani->Add(10038);
	animations->Add(510, ani);

	marco = new CMarco(MARCO_START_X, MARCO_START_Y, MARCO_START_VX);
	marcoleg = new CMarcoLeg(MARCOLEG_START_X, MARCOLEG_START_Y, MARCOLEG_START_VX);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	marcoleg->Update(dt);
	marco->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);
		
		marcoleg->Render();
		marco->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}