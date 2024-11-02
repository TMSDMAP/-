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
	int x, y;//����
	int direction;//����
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
	int scores;//��¼�÷�
	vector<SnakeState> Bodies;//�ߵ�����
	SnakeState LastTail;//��һ��β�͵�λ��
	int len;
public:
	Snake() { scores = 0; }
	void get_Snakehead(int x, int y);//��ȡ��ͷλ��
	void elongate();//�䳤
	bool Snake_move(char c);//�ߵ��ƶ�,����true����ɹ��ƶ���false����ʧ��
	bool is_over(int x, int y);//�ж��Ƿ����,false��ʾ����
	int show_scores();//���ط���
	int get_len();
	void reset();
};