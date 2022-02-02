#define Number_of_cells 8
#include "BattleMovie.h"
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
	struct GUNDAM
	{
		const char* Name;
		int Picture;
		int HP;
		int Attack;
		int Defence;
		int Move;
		int X;
		int Y;
	};

	GUNDAM MS1 = { "ƒKƒ“ƒ_ƒ€", Picture.Ally, 10, 10, 10, 2, 0, 0};
	GUNDAM MS2 = { "ƒUƒN", Picture.Enemy, 10, 10, 10, 1, 0, 0 };

	struct
	{
		int Type[Number_of_cells][Number_of_cells];
	}MS;

	struct
	{
		int Type[Number_of_cells][Number_of_cells];
		int X[Number_of_cells][Number_of_cells];
		int Y[Number_of_cells][Number_of_cells];
	}Field;

	struct
	{
		int X = 0;
		int Y = 0;
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

ACTION::ACTION()
{
	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			MS.Type[x][y] = 0;
			Field.Type[x][y] = 0;
			Field.X[x][y] = 0;
			Field.Y[x][y] = 0;
		}
	}
	MS.Type[3][7] = 1;
	MS1.X = 3 * 100;
	MS1.Y = 7 * 100;

	MS.Type[3][0] = 2;
	MS2.X = 3 * 100;
	MS2.Y = 0 * 100;
}

void ACTION::Calculation()
{
	//Cannot be long press
	if (Key.Inf[KEY_INPUT_D] == 1) Flag.X_right = 1;
	else if (Key.Inf[KEY_INPUT_A] == 1) Flag.X_left = 1;
	else if (Key.Inf[KEY_INPUT_W] == 1) Flag.Y_down = 1;
	else if (Key.Inf[KEY_INPUT_S] == 1) Flag.Y_up = 1;

	//Cursol Move
	if (Flag.X_right == 1) Cur.X = Cur.X + 100;
	else if (Flag.X_left == 1) Cur.X = Cur.X - 100;
	else if (Flag.Y_down == 1) Cur.Y = Cur.Y - 100;
	else if (Flag.Y_up == 1) Cur.Y = Cur.Y + 100;

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
		if (Flag.Enter == 1 && MS.Type[x][y] != 0)
		{
			int i, j;
			Select = MS.Type[x][y];
			for (int y = -(MS1.Move); y <= MS1.Move; y = y + 1)
			{
				for (int x = -(MS1.Move); x <= MS1.Move; x = x + 1)
				{
					if (fabs(x) + fabs(y) <= MS1.Move && (Cur.X / 100) + x >= 0 && (Cur.Y / 100) + y >= 0)
					{
						i = Cur.X / 100 + x;
						j = Cur.Y / 100 + y;
						if (i >= 0 && i < Number_of_cells && j >= 0 && j < 8)
						{
							Field.Type[i][j] = Select;
						}
					}
				}
			}
			Phase = 1;
		}
		break;
	case 1:
		if (Flag.Enter == 1 && Field.Type[x][y] != 0)
		{
			MS.Type[x][y] = Select;
			MS1.X = Cur.X;
			MS1.Y = Cur.Y;
			for (int y = 0; y < Number_of_cells; y = y + 1)
			{
				for (int x = 0; x < Number_of_cells; x = x + 1)
				{
					Field.Type[x][y] = 0;
					Field.X[x][y] = 0;
					Field.Y[x][y] = 0;
				}
			}
			Phase = 2;
		}

		if (Flag.Delete == 1)
		{
			for (int y = 0; y < Number_of_cells; y = y + 1)
			{
				for (int x = 0; x < Number_of_cells; x = x + 1)
				{
					Field.Type[x][y] = 0;
					Field.X[x][y] = 0;
					Field.Y[x][y] = 0;
				}
			}
			Phase = 0;
		}
		break;
	case 2:
		Select = 0;
		break;
	}
}

void ACTION::Change()
{
	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			DrawGraph(x * 100, y * 100, Picture.Back, TRUE);
			if (Field.Type[x][y] == Select && Select > 0) DrawGraph(x * 100, y * 100, Picture.Select, TRUE);
		}
	}

	for (int y = 0; y < Number_of_cells; y = y + 1)
	{
		for (int x = 0; x < Number_of_cells; x = x + 1)
		{
			switch (MS.Type[x][y])
			{
			case 0:
				break;
			case 1:
				DrawGraph(MS1.X, MS1.Y, Picture.Ally, TRUE);
				break;
			case 2:
				DrawGraph(MS2.X, MS2.Y, Picture.Enemy, TRUE);
				break;
			}
		}
	}

	//Cursol
	DrawGraph(Cur.X, Cur.Y, Picture.Cursor, TRUE);
	DrawFormatStringToHandle(900, 0, Color.White, Font.c[30]
		, "(Cur.X,Cur.Y) = (%d,%d)", Cur.X, Cur.Y);
	DrawFormatStringToHandle(900, 50, Color.White, Font.c[30]
		, "(X,Y) = (%d,%d)", (Cur.X + 100) / 100, (Cur.Y + 100) / 100);
	BattleMovie();

	Flag.X_right = 0;
	Flag.X_left = 0;
	Flag.Y_down = 0;
	Flag.Y_up = 0;
	Flag.Enter = 0;
	Flag.Delete = 0;
}