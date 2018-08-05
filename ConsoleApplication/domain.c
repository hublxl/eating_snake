#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>//随机数，定时器_sleep() 

int spacenum=0;
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void main()
{
	char c=0;//蛇移动的方向
	char cpre;
	int grow;
	Snake snake, *head, *rear;
	Snake *lastrear;
	srand((unsigned)time(NULL));//初始化随机数种子

	//初始化蛇身，食物，刚开始蛇只有一节
	head = rear = &snake;
	Food *food = (Food*)malloc(sizeof(Food));
	lastrear = (Snake *)malloc(sizeof(Snake));

	printf("\t\t======欢迎使用贪吃蛇游戏======\t\t\n");
	printf("游戏说明：\n");
	printf("1.w(上)，s(下),a(左),d(右)\n");
	printf("2.按esc退出游戏\n");
	printf("3.蛇移动扑食中，如果蛇头碰到蛇身或墙壁，则游戏结束\n");
	printf("按任意键开始游戏\n");
	getch();

	//初始化蛇，食物，运动方向
	cpre = initSnakeFoodDir(head, food);

	drawwall();
	while (1)
	{
		grow = 0;
		//蛇是否吃到食物 
		if (isSnakemeetFood(head, food))
		{
			rear = snakegrow(head);//蛇身增长
			creatfood(food,head);    //随机生成食物，其实就是重新设置坐标 
			avoidoverlap(head, food);//避免食物和蛇身重叠
			grow = 1;
		}
		
		//玩家按键处理
		if (kbhit())
			
			c = setcurkeybutton(cpre);
		if (c != 'x'&&c != 'p')
		{
			cpre = c;//cpre只记录正常的方向,不记录退出,暂停
		}
		if (c == 'x')
		{
			gotoxy(0, 17);
			puts("用户终止\nGame over\n");
			break;
		}
		if (c == 'p')
		{
			while (spacenum % 2 != 0)
			{
				if (kbhit())
					c = setcurkeybutton(c);
				if (c == 'x')
				{
					break;
				}

			}
			if (c == 'x')
			{
				gotoxy(0, 17);
				puts("用户终止\nGame over\n");
				break;
			}
		}
		

		//蛇的移动
		snakemove(head, rear,lastrear, cpre);
		if (isfailure(head))
		{
			gotoxy(0, 17);
			printf("游戏失败\n");
			break;
		}

		//绘制画面 
		//Drawpicture(head, food);
		draw(head, lastrear, grow, food);
		//_sleep(200);//屏幕刷新间隔 
		Sleep(200);

	}
	gotoxy(0,18);
	printf("谢谢使用，再见\n");
	system("pause");

}