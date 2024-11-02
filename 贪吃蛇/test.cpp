#include "snake.h"
#include "grid.h"
using namespace std;
#define M 10
#define N 20
char grid[6 * M][6 * N];
int level;
int len;
int MAX_score = 0;
char c1;
char direction;  // �ƶ��ķ���
Snake snake;
Grid g;
atomic<bool> musicPlaying(true); // ��־λ�����ڿ������ֲ����߳�

void playMusicLoop() {
	while (musicPlaying) {
		mciSendString("open \"����.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3 wait", NULL, 0, NULL); // ʹ�� wait �����ȴ����Ž���
		mciSendString("close mp3", NULL, 0, NULL);
	}
}
// ��ʼ��
void initialize() 
{
	// �˶�����initialize_grid�����λ�á���ʾ��
	direction = 'a';
	int m = g.show_m(), n = g.show_n();
	g.initialize_grid(m/2,n/2);
	snake.get_Snakehead(m/2, n/2);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << grid[i][j];
		printf("\n");
	}
}

int get_dir(int old_dir)
{
	int new_dir = old_dir;
	if (_kbhit()) {
		//_getch();
		new_dir = _getch();
	}
	if (len > 1 && (abs(new_dir - old_dir) == 2) || abs(new_dir - old_dir) == 8) new_dir = old_dir;
	return new_dir;
}
// �����û��ļ�������
void getInput()
{
	char key = get_dir(direction);
	if (key == 27) { exit(0); }
	switch (key)
	{
	case 'a'://����
	case 'A':
		if (direction != 'd') { direction = 'a'; } break;
	case 'd'://����
	case 'D':
		if (direction != 'a') { direction = 'd'; } break;
	case 'w':
	case 'W':
		if (direction != 's') { direction = 'w'; } break;
	case 's':
	case 'S':
		if (direction != 'w') { direction = 's'; } break;
	default:break;
	}
}

bool PlayGame()
{
	int scores[4] = { 0,10,20,30 };
	unsigned int Speed[4] = { 300,500,400,300 };
	level = g.show_level();
	snake.reset();
	initialize();
	g.drawScene(snake.show_scores());
	g.generateFood();
	while (1) 
	{
		len = snake.get_len();
		if (level != 0 && snake.show_scores() == scores[level])
		{
			if(g.pass()==27) return false;
			level++; 
			g.get_level(level);
			break;
		}
		if (!g.judge())
			g.generateFood();
		getInput();
		if (!snake.Snake_move(direction))
		{
			if (level == 0)
			{
				MAX_score = max(MAX_score, snake.show_scores());
				g.get_MAX_score(MAX_score);
			}
			g.loss();
			return false;
		}
		g.drawScene(snake.show_scores());
		Sleep(Speed[level]);  // �����ٶ�
	}
	return true;
}


int main() 
{
	thread musicThread(playMusicLoop);  // �������ֲ����߳�
	/*mciSendString("open ����.mp3", 0, 0, 0);
	mciSendString("play ����.mp3", 0, 0, 0);*/
	system("color F4");
up:
	welcome();
	g.choose_mode();
	while (1)
	{
		if (!PlayGame())
			goto up;
	}
	musicPlaying = false;
	if (musicThread.joinable())
		musicThread.join();    // ֹͣ���ֲ����߳�
	/*mciSendString("stop ����.mp3", 0, 0, 0);
	mciSendString("close ����.mp3", 0, 0, 0);*/
	return 0;
}
