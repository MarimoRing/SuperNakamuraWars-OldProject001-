#define A 900
#define B 300
#define C 1000
#define D 500

void MAP_Command()
{
	DrawBox( A, B, A+100, B+200, Color.Blue, TRUE);
	DrawFormatStringToHandle( A+20, B+10, Color.White, Font.c[30],
		"à⁄ìÆ");
	DrawFormatStringToHandle(A + 20, B + 60, Color.White, Font.c[30],
		"çUåÇ");
	DrawFormatStringToHandle(A + 20, B + 110, Color.White, Font.c[30],
		"ê∏ê_");
	DrawFormatStringToHandle(A + 20, B + 160, Color.White, Font.c[30],
		"ë“ã@");
}
