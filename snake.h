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
#define map_wide 50       //��Ļ����
#define map_length 25    //��Ļ����
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)

void clearGetchBuffer();	//���_getch()��õ��ַ�
void gotoxy(int x, int y);	//���ƹ��λ��
void hideCursor();			//���ؿ���̨���
void timelim(void* a);		//ʱ����ƺ�������һ���߳�
void initialize();			//��ʼ��
void show();				//չʾ��ͼ
void gameover();			//��Ϸʧ�ܽ���
void win();					//��һ��Ӯ��
void move_left();			//����
void move_right();			//����
void move_up();				//����
void move_down();			//����
void snake_yaya(int snake_need_length, int timerset, int level);     //��������

#endif