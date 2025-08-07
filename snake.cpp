#include"snake.h"

using namespace std;

int n_snake = 1;	//蛇的长度
time_t t;			//记录时间
char key_down;		//记录按键按下是哪个
char rectang[map_length][map_wide];		//整个地图
int* snake_x, * snake_y;			//蛇的坐标，指针是为了记录整条蛇
int food_x, food_y;				//食物的坐标
int timelimit;					//时间限制
int need;						//需要多长才算赢
bool isover = false;           //用来记录是否结束，结束就让子线程也停下来
int nowlevel;


void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;  // 列坐标（横向）
	pos.Y = y;  // 行坐标（纵向）
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1, 0 };  // 第二个参数为 0 表示隐藏
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void timelim(void* a)
{
	while (timelimit > 0 || need<n_snake) 
	{
		timelimit--;
		if (isover)	break;
		Sleep(1000);  // 仅倒计时，不刷新画面
		gotoxy(0, 0);
		show();
		if (n_snake >= need) 
		{
			_endthread();
		}
	}
	// 时间到结束游戏
	gotoxy(0, 0);
	system("cls");
	cout << "You lost" << endl;
	exit(0);
}

void clearGetchBuffer() 
{
	while (_kbhit()) 
	{
		int key = _getch();
		// 处理方向键等特殊键，读取第二个字节
		if (key == 0 || key == 0xE0) 
		{
			_getch();
		}
	}
}

void snake_yaya(int snake_need_length, int timerset,int level)
{
	//先清空_getch()获得的字符，防止一进去下一关，上一关的输入给到了这里
	clearGetchBuffer();
	nowlevel = level;
	hideCursor();
	n_snake = 1;
	timelimit = timerset;
	need = snake_need_length;
	snake_x = (int*)realloc(snake_x, snake_need_length * sizeof(int));
	snake_y = (int*)realloc(snake_y, snake_need_length * sizeof(int));
	srand((unsigned int)time(&t));
	initialize();
	food_x = (rand() % (map_length - 4)) + 2;
	food_y = (rand() % (map_wide - 4)) + 2;
	rectang[food_x][food_y] = '$';
	gotoxy(0, 0);
	show();
	_beginthread(timelim, 0, NULL);  //启动另一个线程
	while (1)
	{
		if (snake_x[0] < 1 || snake_x[0] >= map_length - 1 ||
			snake_y[0] < 1 || snake_y[0] >= map_wide - 1)
		{
			system("cls");
			gameover();
		}
		if (n_snake >= snake_need_length)
		{
			system("cls");
			win();
			break;
		}
		key_down = _getch();
		switch (key_down)
		{
		case 27:
			system("cls");
			gameover();
			break;
		case 75:
			move_left();
			break;
		case 72:
			move_up();
			break;
		case 77:
			move_right();
			break;
		case 80:
			move_down();
			break;
		default:
			break;
		}
		gotoxy(0, 0);
		show();
	}
	fflush(stdin);
	return;
}

void show()
{
	// 先拼接所有内容到字符串
	string output;
	string lev="";
	char le = nowlevel + '0';
	lev += le;
	output += "第" + lev + "关" + " 剩余时间：" + to_string(timelimit) + "秒，当前长度：" + to_string(n_snake) + "，还需：" + to_string(need - n_snake) + "\n";
	for (int i = 0; i < map_length; i++) 
	{
		for (int j = 0; j < map_wide; j++) 
		{
			output += rectang[i][j];
		}
		output += "\n";
	}
	// 一次性输出
	cout << output;
}

void move_left()
{
	int i;
	for (i = 1; i < n_snake; i++)
	{
		if (snake_y[0] - 1 == snake_y[i] && snake_x[0] == snake_x[i])
		{
			gotoxy(0, 0);
			cout << "You can't eat yourself!" << endl;
			Sleep(5000);
			gameover();
		}
	}
	for (i = 0; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = ' ';
	}
	for (i = n_snake - 1; i > 0; i--)
	{
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	snake_y[0] -= 1;
	rectang[snake_x[0]][snake_y[0]] = '@';
	for (i = 1; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = '#';
	}
	if (food_x == snake_x[0] && food_y == snake_y[0])
	{
		snake_x[n_snake] = snake_x[n_snake - 1];
		snake_y[n_snake] = snake_y[n_snake - 1] + 1;
		rectang[snake_x[n_snake]][snake_y[n_snake]] = '#';
		n_snake += 1;
		food_x = (rand() % (map_length - 4)) + 2;
		food_y = (rand() % (map_wide - 4)) + 2;
		rectang[food_x][food_y] = '$';
	}
}

void move_right()
{
	int i;
	for (i = 1; i < n_snake; i++)
	{
		if (snake_y[0] + 1 == snake_y[i] && snake_x[0] == snake_x[i])
		{
			gotoxy(0, 0);
			cout << "You can't eat yourself!" << endl;
			Sleep(5000);
			gameover();
		}
	}
	for (i = 0; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = ' ';
	}
	for (i = n_snake - 1; i > 0; i--)
	{
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	snake_y[0] += 1;
	rectang[snake_x[0]][snake_y[0]] = '@';
	for (i = 1; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = '#';
	}
	if (food_x == snake_x[0] && food_y == snake_y[0])
	{
		snake_x[n_snake] = snake_x[n_snake - 1];
		snake_y[n_snake] = snake_y[n_snake - 1] - 1;
		rectang[snake_x[n_snake]][snake_y[n_snake]] = '#';
		n_snake += 1;
		food_x = (rand() % (map_length - 4)) + 2;
		food_y = (rand() % (map_wide - 4)) + 2;
		rectang[food_x][food_y] = '$';
	}
}

void move_up()
{
	int i;
	for (i = 1; i < n_snake; i++)
	{
		if (snake_x[0] - 1 == snake_x[i] && snake_y[0] == snake_y[i])
		{
			gotoxy(0, 0);
			cout << "You can't eat yourself!" << endl;
			Sleep(5000);
			gameover();
		}
	}
	for (i = 0; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = ' ';
	}
	for (i = n_snake - 1; i > 0; i--)
	{
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	snake_x[0] -= 1;
	rectang[snake_x[0]][snake_y[0]] = '@';
	for (i = 1; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = '#';
	}
	if (food_x == snake_x[0] && food_y == snake_y[0])
	{
		snake_x[n_snake] = snake_x[n_snake - 1] + 1;
		snake_y[n_snake] = snake_y[n_snake - 1];
		rectang[snake_x[n_snake]][snake_y[n_snake]] = '#';
		n_snake += 1;
		food_x = (rand() % (map_length - 4)) + 2;
		food_y = (rand() % (map_wide - 4)) + 2;
		rectang[food_x][food_y] = '$';
	}
}

void move_down()
{
	int i;
	for (i = 1; i < n_snake; i++)
	{
		if (snake_x[0] + 1 == snake_x[i] && snake_y[0] == snake_y[i])
		{
			gotoxy(0, 0);
			cout << "You can't eat yourself!" << endl;
			Sleep(5000);
			gameover();
		}
	}
	for (i = 0; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = ' ';
	}
	for (i = n_snake - 1; i > 0; i--)
	{
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	snake_x[0] += 1;
	rectang[snake_x[0]][snake_y[0]] = '@';
	for (i = 1; i < n_snake; i++)
	{
		rectang[snake_x[i]][snake_y[i]] = '#';
	}
	if (food_x == snake_x[0] && food_y == snake_y[0])
	{
		snake_x[n_snake] = snake_x[n_snake - 1] - 1;
		snake_y[n_snake] = snake_y[n_snake - 1];
		rectang[snake_x[n_snake]][snake_y[n_snake]] = '#';
		n_snake += 1;
		food_x = (rand() % (map_length - 4)) + 2;
		food_y = (rand() % (map_wide - 4)) + 2;
		rectang[food_x][food_y] = '$';
	}
}

void initialize()
{
	int i, j;
	for (i = 0; i < map_length; i++)
	{
		for (j = 0; j < map_wide; j++)
		{
			if (j == 0 || i == 0 || j == map_wide - 1 || i == map_length - 1)
			{
				rectang[i][j] = '+';
			}
			else if (i == 1 && j == 1)
			{
				rectang[i][j] = '@';
			}
			else
			{
				rectang[i][j] = ' ';
			}
		}
	}
	//define snake head location;
	snake_x[0] = 1;
	snake_y[0] = 1;
}

void win()
{
	cout << "     You win. Congration\n    " << endl;
}

void gameover()
{
	isover = true;
	cout << "     You loss. Game over\n    " << endl;
	free(snake_x);
	free(snake_y);
	exit(0);
}
