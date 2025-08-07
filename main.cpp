#include"snake.h"

void Meun()//菜单
{
	std::cout << "****Welcome you play Gluttonous Snake****\n";
	std::cout << "****************0.无尽模式***************\n";
	std::cout << "****************1.关卡模式***************\n";
	std::cout << "****游戏开始后按键盘的ESC按键可以退出****\n";
}

int main()
{
	// 关闭同步并解除cin与cout的绑定
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int choose;
	Meun();
	std::cin >> choose;
	
	if (choose == 1)    //关卡模式
	{
		int timelimit[5] = { 30,60,70,80,90 };
		int need_length[5] = { 5,15,28,38,50 };
		for (int i = 0; i < 5; i++)
		{
			snake_yaya(need_length[i], timelimit[i], i + 1);
			//gotoxy(0, 0);
			Sleep(1000);
			system("cls");
			system("cls");
			system("cls");
			system("cls");
			std::cout << "恭喜你通过这一关 " << i + 1 << "\n";
			std::cout << "请等待进入下一关\n";
			Sleep(3000);
		}
	}
	else if(choose==0)   //无尽模式
	{
		snake_yaya(1e9, 1e9,1);
		gotoxy(0, 0);
	}
	else
	{ 
		std::cout << "Have not other mode...\n";
	}
	return 0;
}