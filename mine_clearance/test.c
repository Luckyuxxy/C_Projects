#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"


void menu()
{
	printf("**********************\n");
	printf("********1.play********\n");
	printf("********0.exit********\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	//初始化数组的内容
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//展示两个数组的内容
	DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);

	//设置雷
	SetMine(mine, ROW, COL);
	DisplayBoard(mine, ROW, COL);

	//排查雷
	FindMine(mine, show, ROW, COL);

	
}

int main()
{
	int i = 0;
	
	//设置随机数种子
	srand((unsigned int)time(NULL));

	do
	{
		menu();

		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("开始游戏！\n");
			game();
			break;
		case 0:
			printf("退出游戏");
			break;
		default:
			printf("输入错误！！");
		}
	} while (i);


	return 0;
}