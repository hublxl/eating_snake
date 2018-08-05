#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>//随机数，定时器_sleep() 
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void main()
{
	char c;//蛇移动的方向

	Snake snake, *head, *rear;
	Snake *lastrear;
	srand((unsigned)time(NULL));//初始化随机数种子

	//初始化蛇身，食物，刚开始蛇只有一节
	head = rear = &snake;
	Food *food = (Food*)malloc(sizeof(Food));

	printf("\t\t======欢迎使用贪吃蛇游戏======\t\t\n");
	printf("游戏说明：\n");
	printf("1.w(上)，s(下),a(左),d(右)\n");
	printf("2.按esc退出游戏\n");
	printf("3.蛇移动扑食中，如果蛇头碰到蛇身或墙壁，则游戏结束\n");
	printf("按任意键开始游戏\n");
	getch();

	//初始化蛇，食物，运动方向
	c = initSnakeFoodDir(head, food);


	while (1)
	{

		//蛇是否吃到食物 
		if (isSnakemeetFood(head, food))
		{
			rear = snakegrow(head);//蛇身增长
			creatfood(food);    //随机生成食物，其实就是重新设置坐标 
			avoidoverlap(head, food);//避免食物和蛇身重叠

		}
		//玩家按键处理
		if (kbhit())

			c = setcurkeybutton(c);
		if (c == 'x')
		{
			puts("用户终止\nGame over\n");
			break;
		}


		//蛇的移动
		snakemove(head, rear, c);
		if (isfailure(head))
		{
			printf("游戏失败\n");
			break;
		}

		//绘制画面 
		Drawpicture(head, food);

		//_sleep(200);//屏幕刷新间隔 
		Sleep(200);

	}
	//gotoxy(0,17);
	printf("谢谢使用，再见\n");
	system("pause");

}