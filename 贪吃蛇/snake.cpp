#include "snake.h"
#include "grid.h"
void Snake::get_Snakehead(int x, int y)
{
	SnakeState head;
	head.x = x, head.y = y;
	head.direction = 0;
	Bodies.push_back(head);
	grid[x][y] = 'O';
}

void Snake::elongate()
{
	Bodies.push_back(LastTail);
	grid[LastTail.x][LastTail.y] = 'O';
}

bool Snake::is_over(int x, int y)
{
	return grid[x][y] == '.' || grid[x][y] == '$';
}


bool Snake::Snake_move(char c)
{
	int dir;
	SnakeState head = Bodies[0];
	switch (c)
	{
	case 'w':dir = 0; break;
	case 's':dir = 3; break;
	case 'a':dir = 2; break;
	case 'd':dir = 1;; break;
	}

	int dx[4] = { -1,0,0,1 }, dy[4] = { 0,1,-1,0 };

	if (dir == head.direction || dir == 3 - head.direction)
		dir = head.direction;
	int mx = Bodies[0].x + dx[dir], my = Bodies[0].y + dy[dir];

	if (!is_over(mx, my))
	{
		return false;
	}

	LastTail.get_info(Bodies[Bodies.size() - 1]);
	grid[Bodies[Bodies.size() - 1].x][Bodies[Bodies.size() - 1].y] = '.';

	for (int i = Bodies.size() - 1; i > 0; i--)
	{
		Bodies[i].get_info(Bodies[i - 1]);
	}

	if (grid[mx][my] == '$')
	{
		elongate();
		scores += 1;
	}

	Bodies[0].direction = dir;
	Bodies[0].x = mx, Bodies[0].y = my;
	grid[Bodies[0].x][Bodies[0].y] = 'O';

	return true;
}

int Snake::show_scores()
{
	return scores;
}
int Snake::get_len()
{
	return Bodies.size();
}
void Snake::reset()
{
	scores = 0; 
	Bodies.clear();
	len = 0;
	LastTail = { 0, 0, 0 }; 
}

