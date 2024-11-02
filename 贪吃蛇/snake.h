#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include "grid.h"
using namespace std;
const int MaxN = 100010;
struct SnakeState
{
	int x, y;//坐标
	int direction;//方向
	void get_info(const SnakeState s)
	{
		x = s.x;
		y = s.y;
		direction = s.direction;
	}
};
class Snake
{
private:
	int scores;//记录得分
	vector<SnakeState> Bodies;//蛇的身体
	SnakeState LastTail;//上一次尾巴的位置
	int len;
public:
	Snake() { scores = 0; }
	void get_Snakehead(int x, int y);//获取蛇头位置
	void elongate();//变长
	bool Snake_move(char c);//蛇的移动,返回true代表成功移动，false代表失败
	bool is_over(int x, int y);//判断是否结束,false表示结束
	int show_scores();//返回分数
	int get_len();
	void reset();
};