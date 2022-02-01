class
{
public:
	int Bac;
	int Bla;
	int Whi;
	int Sel;
	int Cur;

	void Read()
	{
		Bac = LoadGraph("field.png");
		Bla = LoadGraph("brack.png");
		Whi = LoadGraph("Player.png");
		Sel = LoadGraph("Selection.png");
		Cur = LoadGraph("cursor.png");
	}
private:
}Pic;