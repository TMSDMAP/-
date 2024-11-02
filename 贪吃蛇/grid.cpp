#include "grid.h"
using namespace std;
void Pos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}        //定义Pos函数，用来设置控制台光标位置
/*WORD wOldColorAttrs = 0;
  extern void SetConsoleColor(int ForegroundColor)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForegroundColor & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}*/
 char s[6 * M][6*N] = { 0 };
 void Grid::initialize_grid(int posX, int posY)  //初始化网格
 {
	 int s = 0;
	 int obstacleX, obstacleY;
	 int i, j;
	 system("cls");
	 if (level == 1) { m = M; n = N; }
	 if (level == 2) { m = 2 * M; n = 2 * N; }
	 if (level == 3) { m = 3 * M; n = 3 * N; }
	 if (level == 0) { m = 4 * M; n = 4 * N; }
	 for (i = 0; i < n; i++)
	 {
		 grid[0][i] = '-';
		 grid[m - 1][i] = '-';
	 }
	 for (j = 0; j < m; j++)
	 {
		 grid[j][0] = '|';
		 grid[j][n - 1] = '|';
	 }
	 for (i = 1; i < m - 1; i++)
		 for (j = 1; j < n - 1; j++)
			 grid[i][j] = '.';
	 // 双层for循环将grid的所有元素设为'.'
	 int obstacle[4] = { 30,0,10,20 };   //生成障碍
	 s = 0;
	 srand(time(NULL));
	 while (s < obstacle[level])
	 {
		 obstacleX = rand() % m;
		 obstacleY = rand() % n;
		 if (grid[obstacleX][obstacleY] == '.' && obstacleX != posX && obstacleY != posY - 1) { grid[obstacleX][obstacleY] = '#'; s++; }
	 }
	 
 }
void Grid::generateFood()     //随机生成食物
{
	int foodx, foody;
	srand(time(NULL));
	do {
		foodx = rand() % m;
		foody = rand() % n;
	} while (grid[foodx][foody] != '.');

	grid[foodx][foody] = '$';
}
bool Grid::judge()    //判断当前场上是否存在食物
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (grid[i][j] == '$') return true;
	return false;
}
void Grid::choose_mode()   //选择模式
{
	char c;
	system("mode con cols=240 lines=63");
	system("cls");
	Pos((240 - 18) / 2, 28);
	printf("Please choose mode\n");
	Pos((240 - 10) / 2, 30);
	printf("1:Run mode\n");
	Pos((240 - 14) / 2, 32);
	printf("2:Endless mode\n");
	c = _getch();
	if (c == '1')
	{
		level = 1;
		m = M; n = N;
	}
	if (c == '2')
	{
		level = 0;
		m = 4*M, n = 4*N;
	}
	if (c == 27) exit(0);
	else system("cls");
}
char Grid::pass()   //胜利界面
{
	_getch();
	char c;
	system("mode con cols=240 lines=63");
	system("cls");
	Pos((240 - 6) / 2,28);
	printf("你过关!\n");
	if (level != 3)
	{
		Pos((240 - 20) / 2, 30);
		printf("Enter for next Level\n");
		Pos((240 - 12) / 2, 32);
	}
	else Pos((240 - 12) / 2, 30);
	printf("Esc for Exit\n");
	c = _getch();
	while (c != 13)
	{
		if (c == 27) { return c; }
		else c = _getch();
	}
	if (c == 13 && level != 3) system("cls");

}
void Grid::loss()  //失败界面
{
	_getch();
	system("mode con cols=240 lines=63");
	system("cls");
	Pos((240 - 9) / 2, 29);
	printf("You died!\n");
	Pos((240 - 12) / 2, 31);
	printf("按任意键继续");
	_getch();
	system("cls");
}
void Grid::drawScene(int scores)   //绘制界面
{
	system("cls"); // 清屏,清空输出 或者printf("\033[2J");
	if (level == 1)
		printf("本关考验你驭蛇觅食功夫\n");
	if (level == 0)
		printf("本关不考验功夫\n");
	if (level == 2)
		printf("本关考验你秦王绕柱功夫\n");
	if (level == 3)
		printf("本关考验你眼疾手快功夫\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			s[i][j] = grid[i][j];  
		s[i][n] = '\0';   //复制数组元素，避免原本数组全部输出
	}
	for (int i = 0; i < m; i++)
	{
			cout << s[i]<<endl;  //相比逐个输出可以降低闪屏发生的频率
		
	}
	if (level == 0) printf("score:%d  maxscore:%d", scores, MAX_score);
	if (level == 1)
		printf("score:%d/10\n", scores);
	if (level == 2)
		printf("score:%d/20\n", scores);
	if (level == 3)
		printf("score:%d/30\n", scores);  //输出得分
}
void welcome()  //绘制欢迎界面
{
	char c;
	system("mode con cols=240 lines=63");
	system("cls");
	Pos((240 - 27) / 2, 27);
	printf("WELCOME to our SnakeGame!!!\n");
	Pos((240 - 29) / 2, 29);
	printf("w a s d for direction control\n");
	Pos((240 - 12) / 2, 31);
	printf("ESC For Exit\n");
	Pos((240 - 15) / 2, 33);
	printf("Enter For Begin\n");
	c = _getch();
	while (c != 13)
	{
		if (c == 27) exit(0);
		else c = _getch();
	}
	if (c == 13) system("cls");

}