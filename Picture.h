class
{
public:
	int Back;
	int Enemy;
	int Ally;
	int Select;
	int Cursor;

	void Read()
	{
		Back = LoadGraph("field.png");
		Enemy = LoadGraph("brack.png");
		Ally = LoadGraph("Player.png");
		Select = LoadGraph("Selection.png");
		Cursor = LoadGraph("cursor.png");
	}
private:
}Picture;