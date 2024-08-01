#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}

}


void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;

	printf("-----------------------------------\n");

	//打印列编号栏
	for (i = 0; i < row + 1; i++)
		printf("%d ", i);
	printf("\n");

	//打印棋盘
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------------------\n");
}


void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;

	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}


int get_mine_count(char mine[ROWS][COLS], int x, int y) 
{
	//得到某坐标3*3范围内雷的个数

	int num = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			num += mine[i][j];
		}
	}
	num = num - (9 * '0');

	return num;
}


//没有展开版本的

//void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
//{
//	int x = 0;
//	int y = 0;
//	int win = 0; //找到非雷的个数
//
//	while (win < ROW * COL - EASY_COUNT)
//	{
//		printf("输入你想要排查的坐标\n");
//		scanf("%d %d", &x, &y);
//
//		if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9)) //判断输入是否有效
//		{
//			if (mine[x][y] == '1') //扫到雷了
//			{
//				printf("真倒霉啊哈哈哈哈哈哈\n");
//				printf("游戏结束！！！！！\n");
//				break;
//			}
//			else
//			{
//				win++;
//				int count = get_mine_count(mine, x, y); //得到周围雷的个数
//				show[x][y] = count + '0'; //转换成字符
//				DisplayBoard(show, ROW, COL);
//			}
//		}
//		else
//		{
//			printf("Invalid Input!!!!!\n");
//		}
//	}
//	
//	if (win == ROW * COL - EASY_COUNT)
//	{
//		printf("恭喜你排雷成功！！！！\n");
//		DisplayBoard(show, ROW, COL);
//	}
//		
//}


void extend_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int count = get_mine_count(mine, x, y);

	if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9))	//判断输入是否有效
	{
		if (count == 0 && show[x][y] == '*')
		{
			show[x][y] = count + '0';
			extend_board(mine, show, x - 1, y - 1);
			extend_board(mine, show, x - 1, y);
			extend_board(mine, show, x - 1, y + 1);
			extend_board(mine, show, x, y - 1);
			extend_board(mine, show, x, y + 1);
			extend_board(mine, show, x + 1, y - 1);
			extend_board(mine, show, x + 1, y);
			extend_board(mine, show, x + 1, y + 1);
		}
		else if (count != 0)
		{
			show[x][y] = count + '0';
		}
	}
	
}


//带有展开版本的
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0; //找到非雷的个数

	while (win < ROW * COL - EASY_COUNT)
	{
		printf("输入你想要排查的坐标\n");
		scanf("%d %d", &x, &y);

		if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9)) //判断输入是否有效
		{
			if (mine[x][y] == '1') //扫到雷了
			{
				printf("真倒霉啊哈哈哈哈哈哈\n");
				printf("游戏结束！！！！！\n");
				break;
			}
			else
			{
				win++;
				extend_board(mine, show, x, y); //根据输入排查的坐标（x,y）,实现区域扩展的功能
				DisplayBoard(show, ROW, COL); //不要在递归里面printf,不然会一直print
			}
		}
		else
		{
			printf("Invalid Input!!!!!\n");
		}
	}

	if (win == ROW * COL - EASY_COUNT)
	{
		printf("恭喜你排雷成功！！！！\n");
		DisplayBoard(show, ROW, COL);
	}

}
