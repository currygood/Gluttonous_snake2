#include"snake.h"

void Meun()//�˵�
{
	std::cout << "****Welcome you play Gluttonous Snake****\n";
	std::cout << "****************0.�޾�ģʽ***************\n";
	std::cout << "****************1.�ؿ�ģʽ***************\n";
	std::cout << "****��Ϸ��ʼ�󰴼��̵�ESC���������˳�****\n";
}

int main()
{
	// �ر�ͬ�������cin��cout�İ�
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int choose;
	Meun();
	std::cin >> choose;
	
	if (choose == 1)    //�ؿ�ģʽ
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
			std::cout << "��ϲ��ͨ����һ�� " << i + 1 << "\n";
			std::cout << "��ȴ�������һ��\n";
			Sleep(3000);
		}
	}
	else if(choose==0)   //�޾�ģʽ
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