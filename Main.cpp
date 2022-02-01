//Preproccessor definition
#define WIN_MAX_X 1600
#define WIN_MAX_Y 900
#define WIN_POS_X 0
#define WIN_POS_Y 0


//Insert header file
#include <math.h>
#include "DxLib.h"
#include "Sub.h"
#include "Pic.h"
#include "Act.h"

//Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	DxLib_Init();

	//Window Init
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);//Background position
	SetWindowText("Super Nakamura Wars");		//Background title
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//Background size
	SetBackgroundColor(255, 255, 255);			//Background color
	SetDrawScreen(DX_SCREEN_BACK);

	//Read
	Col.Read();
	Fon.Read();
	Pic.Read();

	//Case Slect
	while (ScreenFlip() == 0 &&				//Erase all back screens
		ClearDrawScreen() == 0 &&			//The number of loops becomes the same as FPS
		ProcessMessage() == 0 &&			//Link with other software
		Key.Read() == 0 &&					//Learn all key information
		Key.Inf[KEY_INPUT_ESCAPE] == 0)		//It disappears when you press ESC
	{
		// ‰æ–Ê‚ðƒNƒŠƒA‚·‚é
		ClearDrawScreen();
		Act.Out();
	}

	//WaitKey();
	DxLib_End();
	return 0;
}