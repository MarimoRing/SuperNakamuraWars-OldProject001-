#define A 900
#define B 300

void MS_Command()
{
	DrawBox( A, B, A+100, B+200, Color.Blue, TRUE);
	DrawFormatStringToHandle( A+20, B+10, Color.White, Font.c[30],
		"移動");
	DrawFormatStringToHandle(A + 20, B + 60, Color.White, Font.c[30],
		"攻撃");
	DrawFormatStringToHandle(A + 20, B + 110, Color.White, Font.c[30],
		"精神");
	DrawFormatStringToHandle(A + 20, B + 160, Color.White, Font.c[30],
		"待機");
	DrawFormatStringToHandle(A + 20 - 60, B + 10 + Arrow.X, Color.White, Font.c[30],
		"→");
}
void MAP_Command2()
{
	DrawBox(A, B, A + 200, B + 200, Color.Blue, TRUE);
	DrawFormatStringToHandle(A + 20, B + 10, Color.White, Font.c[30],
		"ターン終了");
	DrawFormatStringToHandle(A + 20, B + 60, Color.White, Font.c[30],
		"全体マップ");
	DrawFormatStringToHandle(A + 20, B + 110, Color.White, Font.c[30],
		"部隊一覧");
	DrawFormatStringToHandle(A + 20, B + 160, Color.White, Font.c[30],
		"セーブ");
	DrawFormatStringToHandle(A + 20 - 60, B + 10 + Arrow.X, Color.White, Font.c[30],
		"→");
}
