#include"snake.h"

using namespace std;

int n_snake = 1;	//�ߵĳ���
time_t t;			//��¼ʱ��
char key_down;		//��¼�����������ĸ�
char rectang[map_length][map_wide];		//������ͼ
int* snake_x, * snake_y;			//�ߵ����ָ꣬����Ϊ�˼�¼������
int food_x, food_y;				//ʳ�������
int timelimit;					//ʱ������
int need;						//��Ҫ�೤����Ӯ
bool isover = false;           //������¼�Ƿ�����������������߳�Ҳͣ����
int nowlevel;


void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;  // �����꣨����
	pos.Y = y;  // �����꣨����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1, 0 };  // �ڶ�������Ϊ 0 ��ʾ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void timelim(void* a)
{
	while (timelimit > 0 || need<n_snake) 
	{
		timelimit--;
		if (isover)	break;
		Sleep(1000);  // ������ʱ����ˢ�»���
		gotoxy(0, 0);
		show();
		if (n_snake >= need) 
		{
			_endthread();
		}
	}
	// ʱ�䵽������Ϸ
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
		// ������������������ȡ�ڶ����ֽ�
		if (key == 0 || key == 0xE0) 
		{
			_getch();
		}
	}
}

void snake_yaya(int snake_need_length, int timerset,int level)
{
	//�����_getch()��õ��ַ�����ֹһ��ȥ��һ�أ���һ�ص��������������
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
	_beginthread(timelim, 0, NULL);  //������һ���߳�
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
	// ��ƴ���������ݵ��ַ���
	string output;
	string lev="";
	char le = nowlevel + '0';
	lev += le;
	output += "��" + lev + "��" + " ʣ��ʱ�䣺" + to_string(timelimit) + "�룬��ǰ���ȣ�" + to_string(n_snake) + "�����裺" + to_string(need - n_snake) + "\n";
	for (int i = 0; i < map_length; i++) 
	{
		for (int j = 0; j < map_wide; j++) 
		{
			output += rectang[i][j];
		}
		output += "\n";
	}
	// һ�������
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
