#pragma once
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <atomic>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define M 10
#define N 20
extern char grid[6 * M][6 * N];
class Grid
{
private:
	int m, n;//³¤¡¢¿í
	int level;//¼¶Êý
	int MAX_score;
public:
	Grid() { m = 0, n = 0, level = 0, MAX_score = 0; }
	void initialize_grid(int posX, int posY);
	void generateFood();
	bool judge();
	void choose_mode();
	char pass();
	void loss();
	void drawScene(int scores);
	int show_m() { return m; }
	int show_n() { return n; }
	int show_level() { return level; }
	void get_level(int x) { level = x; }
	void get_MAX_score(int x) { MAX_score = x; }
};
void Pos(int x, int y);
void welcome();
//extern void SetConsoleColor(int ForegroundColor);