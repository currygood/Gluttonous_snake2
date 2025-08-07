#ifndef _SNAKE_H
#define _SNAKE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <process.h>
#define map_wide 50       //屏幕左右
#define map_length 25    //屏幕上下
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)

void clearGetchBuffer();	//清空_getch()获得的字符
void gotoxy(int x, int y);	//控制光标位置
void hideCursor();			//隐藏控制台光标
void timelim(void* a);		//时间控制函数，另一个线程
void initialize();			//初始化
void show();				//展示地图
void gameover();			//游戏失败结束
void win();					//这一关赢了
void move_left();			//左移
void move_right();			//右移
void move_up();				//上移
void move_down();			//下移
void snake_yaya(int snake_need_length, int timerset, int level);     //整个主控

#endif