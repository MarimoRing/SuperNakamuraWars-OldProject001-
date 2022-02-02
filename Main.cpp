//Preproccessor definition
#define WIN_MAX_X 1600
#define WIN_MAX_Y 900
#define WIN_POSITION_X 0
#define WIN_POSITION_Y 0


//Insert header file
#include <math.h>
#include "DxLib.h"
#include "Setting.h"
#include "Picture.h"
#include "Action.h"

//Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	DxLib_Init();

	//Window Init
	SetWindowInitPosition(WIN_POSITION_X, WIN_POSITION_Y);//Background position
	SetWindowText("Super Nakamura Wars");		//Background title
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//Background size
	SetBackgroundColor(0, 0, 0);			//Background color
	SetDrawScreen(DX_SCREEN_BACK);

	//Read
	Color.Read();
	Font.Read();
	Picture.Read();

	//Case Slect
	while (ScreenFlip() == 0 &&				//Erase all back screens
		ClearDrawScreen() == 0 &&			//The number of loops becomes the same as FPS
		ProcessMessage() == 0 &&			//Link with other software
		Key.Read() == 0 &&					//Learn all key information
		Key.Inf[KEY_INPUT_ESCAPE] == 0)		//It disappears when you press ESC
	{
		// ‰æ–Ê‚ðƒNƒŠƒA‚·‚é
		ClearDrawScreen();
		Action.Out();
	}

	//WaitKey();
	DxLib_End();
	return 0;
}