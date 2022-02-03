#define Number_of_cells 8
#define Number_of_units 5
#include "Arrow.h"
#include "MAP_UI.h"
class ACTION
{
public:
	ACTION();
	void Out()
	{
		Calculation();
		Change();
	}
private:
	struct GUNDAM //Define character status.
	{
		const char* Name;
		int Picture;//Character Image
		int HP;
		int Attack;
		int Defence;
		int Move;	//Movement power
	};

	GUNDAM MS1 = { "ƒKƒ“ƒ_ƒ€", Picture.Ally, 10, 10, 10, 2};
	GUNDAM MS2 = { "ƒUƒN", Picture.Enemy, 10, 10, 10, 1};

	struct
	{
		int Type[Number_of_cells][Number_of_cells];		//Identification of MS
		int Previous[Number_of_cells][Number_of_cells];	//Stores MS identification information
		int X = 0;										//X coordinate of the selected MS
		int Y = 0;										//Y coordinate of the selected MS
		int Move[Number_of_units + 1];					//Store MS movement power
		int X_state[Number_of_units + 1];				//Stores the X coordinate information of the MS
		int Y_state[Number_of_units + 1];				//Stores the Y coordinate information of the MS
	}MS;

	struct
	{
		int Type[Number_of_cells][Number_of_cells];		//Field Identification
		int Previous[Number_of_cells][Number_of_cells];	//Stores the field identification information
	}Field;

	struct
	{
		int X = 0;	//X coordinate of the cursor
		int Y = 0;	//Y coordinate of the cursor
	}Cur;

	struct
	{
		bool X_right = 0;
		bool X_left = 0;
		bool Y_up = 0;
		bool Y_down = 0;
		bool Enter = 0;
		bool Delete = 0;
	}Flag;

	int Turn = 0;
	int Phase = 0;
	int Select = 0;

	void Calculation();
	void Change();
};

ACTION Action;

ACTION::ACTION()	//Initialization
{
	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			MS.Type[x][y] = 0;
			MS.Previous[x][y] = 0;
			Field.Type[x][y] = 0;
			Field.Previous[x][y] = 0;
		}
	}

	for (int i = 0; i <= Number_of_units; i = i + 1)
	{
		MS.Move[i] = 0;
		MS.X_state[i] = 0;
		MS.Y_state[i] = 0;
	}

	MS.Type[3][7] = 1;
	MS.Move[1] = MS1.Move;
	MS.X_state[1] = 3 * 100;
	MS.Y_state[1] = 7 * 100;

	MS.Type[3][0] = 2;
	MS.Move[2] = MS2.Move;
	MS.X_state[2] = 3 * 100;
	MS.Y_state[2] = 0 * 100;
}

void ACTION::Calculation()
{
	//Cannot be long press
	if (Key.Inf[KEY_INPUT_D] == 1) Flag.X_right = 1;
	else if (Key.Inf[KEY_INPUT_A] == 1) Flag.X_left = 1;
	else if (Key.Inf[KEY_INPUT_W] == 1) Flag.Y_down = 1;
	else if (Key.Inf[KEY_INPUT_S] == 1) Flag.Y_up = 1;

	if (Phase != 1)
	{
		//Cursol Move
		if (Flag.X_right == 1) Cur.X = Cur.X + 100;
		else if (Flag.X_left == 1) Cur.X = Cur.X - 100;
		else if (Flag.Y_down == 1) Cur.Y = Cur.Y - 100;
		else if (Flag.Y_up == 1) Cur.Y = Cur.Y + 100;
	}

	if (Cur.X < 0) Cur.X = 0;
	if (Cur.X > (Number_of_cells - 1) * 100) Cur.X = (Number_of_cells - 1) * 100;
	if (Cur.Y < 0) Cur.Y = 0;
	if (Cur.Y > (Number_of_cells - 1) * 100) Cur.Y = (Number_of_cells - 1) * 100;

	//Cursol Enter
	if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1) Flag.Enter = 1;

	//Cursol Enter
	if (Key.Inf[KEY_INPUT_DELETE] == 1) Flag.Delete = 1;

	int x = Cur.X / 100;
	int y = Cur.Y / 100;

	switch (Phase)
	{
	case 0:
		//If a character is selected, show the range in which it can move.
		if (Flag.Enter == 1 && MS.Type[x][y] != 0)
		{
			MAP_Command();	//Display map commands 
			if (Flag.Enter == 1)
			{
				int i, j;
				Select = MS.Type[x][y];
				MS.Previous[x][y] = MS.Type[x][y];
				MS.X = x;
				MS.Y = y;
				for (int y = -(MS.Move[Select]); y <= MS.Move[Select]; y = y + 1)
				{
					for (int x = -(MS.Move[Select]); x <= MS.Move[Select]; x = x + 1)
					{
						if (fabs(x) + fabs(y) <= MS.Move[Select] && (Cur.X / 100) + x >= 0 && (Cur.Y / 100) + y >= 0)
						{
							i = Cur.X / 100 + x;
							j = Cur.Y / 100 + y;
							if (i >= 0 && i < Number_of_cells && j >= 0 && j < Number_of_cells)
							{
								Field.Type[i][j] = 1;
								Field.Previous[i][j] = 1;
							}
						}
					}
				}
				Phase = 1;
			}
		}
		break;
	case 1: 
		//Change selection
		if (Flag.Y_down == 1 && Arrow.X > 0) Arrow.X = Arrow.X - 50;
		if (Flag.Y_up == 1 && Arrow.X < 150) Arrow.X = Arrow.X + 50;

		//If "Move" is selected, make the character ready to move.
		if (Flag.Enter == 1 && Arrow.X == 0) Phase = 2;
		
		//If you press Delete, return the board to the previous state.
		if (Flag.Delete == 1)
		{
			for (int y = 0; y < Number_of_cells; y = y + 1)
			{
				for (int x = 0; x < Number_of_cells; x = x + 1)
				{
					Field.Type[x][y] = 0;
					Field.Previous[x][y] = 0;
				}
			}
			Select = 0;
			Phase = 0;
		}
		break;
	case 2:
		//If you have selected a movable range, move the character.
		if (Flag.Enter == 1 && Field.Type[x][y] != 0)
		{
			MS.Type[MS.X][MS.Y] = 0;
			MS.Type[x][y] = Select;
			MS.X_state[Select] = Cur.X;
			MS.Y_state[Select] = Cur.Y;
			for (int y = 0; y < Number_of_cells; y = y + 1)
			{
				for (int x = 0; x < Number_of_cells; x = x + 1)
				{
					Field.Type[x][y] = 0;
				}
			}
			Phase = 3;
		}

		//If you press Delete, return the board to the previous state.
		if (Flag.Delete == 1)
		{
			Phase = 1;
		}
		break;
	case 3:
		//Select = 0;
		//If you press Delete, return the board to the previous state.
		if (Flag.Delete == 1)
		{
			MS.X_state[Select] = MS.X * 100;
			MS.Y_state[Select] = MS.Y * 100;
			for (int y = 0; y < Number_of_cells; y = y + 1)
			{
				for (int x = 0; x < Number_of_cells; x = x + 1)
				{
					if (MS.Type[x][y] == Select) 
					{
						MS.Type[x][y] = 0;
					}
					Field.Type[x][y] = Field.Previous[x][y];
				}
			}
			MS.Type[MS.X][MS.Y] = MS.Previous[MS.X][MS.Y];
			Phase = 2;
		}
		break;
	}
}

void ACTION::Change()
{
	//Change the display of the board
	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			DrawGraph(x * 100, y * 100, Picture.Back, TRUE);
			if (Field.Type[x][y] == 1) DrawGraph(x * 100, y * 100, Picture.Select, TRUE);
		}
	}

	//Display of characters
	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			switch (MS.Type[x][y])
			{
			case 0://Nothing
				break;
			case 1:
				DrawGraph(MS.X_state[MS.Type[x][y]], MS.Y_state[MS.Type[x][y]], Picture.Ally, TRUE);
				break;
			case 2:
				DrawGraph(MS.X_state[MS.Type[x][y]], MS.Y_state[MS.Type[x][y]], Picture.Enemy, TRUE);
				break;
			}
		}
	}
	if (Phase == 1)
	{
		MAP_Command();	//Display map commands
	}
	//off-screen display
	DrawGraph(Cur.X, Cur.Y, Picture.Cursor, TRUE);
	DrawFormatStringToHandle(900, 0, Color.White, Font.c[30]
		, "(Cur.X,Cur.Y) = (%d,%d)", Cur.X, Cur.Y);
	DrawFormatStringToHandle(900, 50, Color.White, Font.c[30]
		, "(X,Y) = (%d,%d)", (Cur.X + 100) / 100, (Cur.Y + 100) / 100);

	//Resetting the flags
	Flag.X_right = 0;
	Flag.X_left = 0;
	Flag.Y_down = 0;
	Flag.Y_up = 0;
	Flag.Enter = 0;
	Flag.Delete = 0;
}