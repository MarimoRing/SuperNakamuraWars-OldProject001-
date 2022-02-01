//Color Class
class
{
public:

	int Whi;
	int Bla;
	int Gre;
	int Red;
	int Blu;

	void Read()
	{
		Whi = GetColor(255, 255, 255);
		Bla = GetColor(0, 0, 0);
		Gre = GetColor(0, 255, 0);
		Red = GetColor(255, 0, 0);
		Blu = GetColor(0, 0, 255);
	}

private:
}Col;

//Chara Font Class
class
{
public:

	int c[50 + 1];

	void Read()
	{
		for (int i = 0; i < 50 + 1; i = i + 1)
		{
			c[i] = CreateFontToHandle("MS ƒSƒVƒbƒN", i, 6, DX_FONTTYPE_NORMAL);
		}
	}

private:
}Fon;

//Key Class
class
{
public:
	//Key Info
	int Inf[256];
	//Key Function
	int Read()
	{
		char allkey[256];
		GetHitKeyStateAll(allkey);
		for (int i = 0; i < 256; i = i + 1) {
			if (allkey[i] == 1) {
				Inf[i] = Inf[i] + 1;
			}
			else if (allkey[i] == 0) {
				Inf[i] = 0;
			}
		}
		return 0;
	}
private:
}Key;