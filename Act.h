#define F_Size 8
class ACTION
{
public:
	ACTION();
	void Out()
	{
		Cal();
		Cha();
	}
private:
	struct GUNDAM
	{
		const char* Name;
		int Pic;
		int HP;
		int Att;
		int Def;
		int Mov;
		int X;
		int Y;
	};

	GUNDAM MS1 = { "ƒKƒ“ƒ_ƒ€", Pic.Whi, 10, 10, 10, 2, 0, 0};
	GUNDAM MS2 = { "ƒUƒN", Pic.Bla, 10, 10, 10, 1, 0, 0 };

	struct
	{
		int Typ[F_Size][F_Size];
	}MS;

	struct
	{
		int Typ[F_Size][F_Size];
		int X[F_Size][F_Size];
		int Y[F_Size][F_Size];
	}Fie;

	struct
	{
		int X = 0;
		int Y = 0;
	}Cur;

	struct
	{
		bool Xr = 0;
		bool Xl = 0;
		bool Yu = 0;
		bool Yd = 0;
		bool Ent = 0;
		bool Del = 0;
	}Fla;

	/*
	struct
	{
		bool Setting = 0;
	}Set;
	*/

	int Tur = 0;
	int Pha = 0;
	int Sle = 0;

	void Cal();
	void Cha();
};

ACTION Act;

ACTION::ACTION()
{
	for (int y = 0; y < F_Size; y = y + 1)
	{
		for (int x = 0; x < F_Size; x = x + 1)
		{
			MS.Typ[x][y] = 0;
			Fie.Typ[x][y] = 0;
			Fie.X[x][y] = 0;
			Fie.Y[x][y] = 0;
		}
	}
	MS.Typ[3][7] = 1;
	MS1.X = 3 * 100;
	MS1.Y = 7 * 100;

	MS.Typ[3][0] = 2;
	MS2.X = 3 * 100;
	MS2.Y = 0 * 100;
}

void ACTION::Cal()
{
	//Cannot be long press
	if (Key.Inf[KEY_INPUT_D] == 1) Fla.Xr = 1;
	else if (Key.Inf[KEY_INPUT_A] == 1) Fla.Xl = 1;
	else if (Key.Inf[KEY_INPUT_W] == 1) Fla.Yd = 1;
	else if (Key.Inf[KEY_INPUT_S] == 1) Fla.Yu = 1;

	//Cursol Move
	if (Fla.Xr == 1) Cur.X = Cur.X + 100;
	else if (Fla.Xl == 1) Cur.X = Cur.X - 100;
	else if (Fla.Yd == 1) Cur.Y = Cur.Y - 100;
	else if (Fla.Yu == 1) Cur.Y = Cur.Y + 100;

	if (Cur.X < 0) Cur.X = 0;
	if (Cur.X > (F_Size - 1) * 100) Cur.X = (F_Size - 1) * 100;
	if (Cur.Y < 0) Cur.Y = 0;
	if (Cur.Y > (F_Size - 1) * 100) Cur.Y = (F_Size - 1) * 100;

	//Cursol Enter
	if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1) Fla.Ent = 1;

	//Cursol Enter
	if (Key.Inf[KEY_INPUT_DELETE] == 1) Fla.Del = 1;

	int x = Cur.X / 100;
	int y = Cur.Y / 100;

	switch (Pha)
	{
	case 0:
		if (Fla.Ent == 1 && MS.Typ[x][y] != 0)
		{
			int i, j;
			Sle = MS.Typ[x][y];
			for (int y = -(MS1.Mov); y <= MS1.Mov; y = y + 1)
			{
				for (int x = -(MS1.Mov); x <= MS1.Mov; x = x + 1)
				{
					if (fabs(x) + fabs(y) <= MS1.Mov && (Cur.X / 100) + x >= 0 && (Cur.Y / 100) + y >= 0)
					{
						i = Cur.X / 100 + x;
						j = Cur.Y / 100 + y;
						if (i >= 0 && i < F_Size && j >= 0 && j < 8)
						{
							Fie.Typ[i][j] = Sle;
						}
					}
				}
			}
			Pha = 1;
		}
		break;
	case 1:
		if (Fla.Ent == 1 && Fie.Typ[x][y] != 0)
		{
			MS.Typ[x][y] = Sle;
			MS1.X = Cur.X;
			MS1.Y = Cur.Y;
			for (int y = 0; y < F_Size; y = y + 1)
			{
				for (int x = 0; x < F_Size; x = x + 1)
				{
					Fie.Typ[x][y] = 0;
					Fie.X[x][y] = 0;
					Fie.Y[x][y] = 0;
				}
			}
			Pha = 2;
		}

		if (Fla.Del == 1)
		{
			for (int y = 0; y < F_Size; y = y + 1)
			{
				for (int x = 0; x < F_Size; x = x + 1)
				{
					Fie.Typ[x][y] = 0;
					Fie.X[x][y] = 0;
					Fie.Y[x][y] = 0;
				}
			}
			Pha = 0;
		}
		break;
	case 2:
		Sle = 0;
		break;
	}
}

void ACTION::Cha()
{
	for (int y = 0; y < F_Size; y = y + 1)
	{
		for (int x = 0; x < F_Size; x = x + 1)
		{
			DrawGraph(x * 100, y * 100, Pic.Bac, TRUE);
			if (Fie.Typ[x][y] == Sle && Sle > 0) DrawGraph(x * 100, y * 100, Pic.Sel, TRUE);
		}
	}

	for (int y = 0; y < F_Size; y = y + 1)
	{
		for (int x = 0; x < F_Size; x = x + 1)
		{
			switch (MS.Typ[x][y])
			{
			case 0:
				break;
			case 1:
				DrawGraph(MS1.X, MS1.Y, Pic.Whi, TRUE);
				break;
			case 2:
				DrawGraph(MS2.X, MS2.Y, Pic.Bla, TRUE);
				break;
			}
		}
	}

	//Cursol
	DrawGraph(Cur.X, Cur.Y, Pic.Cur, TRUE);
	DrawFormatStringToHandle(900, 0, Col.Bla, Fon.c[30]
		, "(Cur.X,Cur.Y) = (%d,%d)", Cur.X, Cur.Y);
	DrawFormatStringToHandle(900, 50, Col.Bla, Fon.c[30]
		, "(X,Y) = (%d,%d)", (Cur.X + 100) / 100, (Cur.Y + 100) / 100);

	//Turn
	// Even number
	/*if (Tur % 2 == 0)
	{
		DrawFormatStringToHandle(900, 100, Col.Blu, Fon.c[30]
			, "Turn=%d", Tur);
	}*/

	//Fiag Ini
	Fla.Xr = 0;
	Fla.Xl = 0;
	Fla.Yd = 0;
	Fla.Yu = 0;
	Fla.Ent = 0;
	Fla.Del = 0;
}