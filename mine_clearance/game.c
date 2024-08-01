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

	//��ӡ�б����
	for (i = 0; i < row + 1; i++)
		printf("%d ", i);
	printf("\n");

	//��ӡ����
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
	//�õ�ĳ����3*3��Χ���׵ĸ���

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


//û��չ���汾��

//void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
//{
//	int x = 0;
//	int y = 0;
//	int win = 0; //�ҵ����׵ĸ���
//
//	while (win < ROW * COL - EASY_COUNT)
//	{
//		printf("��������Ҫ�Ų������\n");
//		scanf("%d %d", &x, &y);
//
//		if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9)) //�ж������Ƿ���Ч
//		{
//			if (mine[x][y] == '1') //ɨ������
//			{
//				printf("�浹ù��������������\n");
//				printf("��Ϸ��������������\n");
//				break;
//			}
//			else
//			{
//				win++;
//				int count = get_mine_count(mine, x, y); //�õ���Χ�׵ĸ���
//				show[x][y] = count + '0'; //ת�����ַ�
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
//		printf("��ϲ�����׳ɹ���������\n");
//		DisplayBoard(show, ROW, COL);
//	}
//		
//}


void extend_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int count = get_mine_count(mine, x, y);

	if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9))	//�ж������Ƿ���Ч
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


//����չ���汾��
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0; //�ҵ����׵ĸ���

	while (win < ROW * COL - EASY_COUNT)
	{
		printf("��������Ҫ�Ų������\n");
		scanf("%d %d", &x, &y);

		if ((x >= 1 && x <= 9) && (y >= 1 && y <= 9)) //�ж������Ƿ���Ч
		{
			if (mine[x][y] == '1') //ɨ������
			{
				printf("�浹ù��������������\n");
				printf("��Ϸ��������������\n");
				break;
			}
			else
			{
				win++;
				extend_board(mine, show, x, y); //���������Ų�����꣨x,y��,ʵ��������չ�Ĺ���
				DisplayBoard(show, ROW, COL); //��Ҫ�ڵݹ�����printf,��Ȼ��һֱprint
			}
		}
		else
		{
			printf("Invalid Input!!!!!\n");
		}
	}

	if (win == ROW * COL - EASY_COUNT)
	{
		printf("��ϲ�����׳ɹ���������\n");
		DisplayBoard(show, ROW, COL);
	}

}
