#include "snake.h"
#include <windows.h>
extern int spacenum;
//初始化蛇身,食物，运动方向 
char initSnakeFoodDir(Snake *head, Food *food)
{
	//蛇头初始位置,围墙正中间的矩形区域内（1/2矩形）
	int t=(2*WIDTH) / 4 + rand() % (2*WIDTH) / 2;
	int x;
	while (t % 2 != 1)
	{
		t = (2 * WIDTH) / 4 + rand() % (2 * WIDTH) / 2;
	}
	x = t;
	int y = HEIGH / 4 + rand() % HEIGH / 2;
	int i;
	char c;

	head->x = x;
	head->y = y;
	head->pre = NULL;
	head->next = NULL;

	//初始化食物,此处并不考虑是否与蛇重叠	
	creatfood(food,head);
	//处理食物与蛇身重叠的情况
	avoidoverlap(head, food);
	//随即设置初始运动方向 
	i = rand() % 4;
	if (i == 0)
	{
		c = 'w';
	}
	else if (i == 1)
	{
		c = 's';

	}
	else if (i == 2)
	{
		c = 'a';
	}
	else
	{
		c = 'd';
	}
	return c;
}
//画墙壁，食物，蛇
void Drawpicture(Snake *head, Food *food)
{
	int flag = 0;
	Snake *p;
	int i, j;
	system("cls");
	printf("------------------------------\n");
	for (i = 0; i<HEIGH; i++)
	{
		printf("|");
		for (j = 0; j<WIDTH; j++)
		{
			flag = 0;
			p = head;
			//绘制蛇身
			while (p != NULL)
			{
				if (p->x == j&&p->y == i)
				{
					if (p == head)//画蛇头 
					{
						printf("■");
					}
					else
						printf("□");

					flag = 1;
					break;
				}
				p = p->next;
			}
			//绘制食物 
			if (flag == 0)
			{
				if (food->x == j&&food->y == i)
				{
					putchar(food->c);
					putchar(food->c);
					//flag=1;
					continue;
				}

				printf("  ");//绘制空白 
			}

		}
		printf("|\n");

	}


	printf("------------------------------\n");

}
//创建食物,只改坐标，不重新分配空间 
void creatfood(Food *food,Snake *head)
{
	int t,a;
	t = rand() % (2 * WIDTH - 2) + 1;
	if (head->x - t < 0)
	{
		a = t - head->x;
	}
	else
	{
		a = head->x - t;
	}
	while (a % 2 != 0)
	{
		t = rand() % (2 * WIDTH - 2) + 1;
		if (head->x - t < 0)
		{
			a = t - head->x;
		}
		else
		{
			a = head->x - t;
		}
	}
	food->x = t;
	food->y = rand() % (HEIGH - 1) + 1;
	if (head->x == food->x&&head->y == food->y)
	{
		while (food->y == head->y)
		{
			food->y = rand() % (HEIGH - 1) + 1;

		}

	}
	//food->x = rand() % (2 * WIDTH - 1) + 1;
	//food->y = rand() % (HEIGH - 1) + 1;
	food->c = 65 + rand() % 26;//生成随机大写字母 

}
//避免食物和蛇身重叠 
void avoidoverlap(Snake *head, Food *food)
{
	Snake *p;
	int num = 0;//重叠次数
	int flag = 1;//是否重叠
	while (flag)
	{
		//如果重叠次数大于阈值 
		if (num>OVERLAP)
		{
			setfoodlocation(head, food);
			return;
		}
		p = head;//从蛇头遍历，判断每一节是否与食物重叠 
		flag = 0;
		while (p != NULL)
		{
			if (isSnakemeetFood(p, food))
			{
				num++;
				flag = 1;
				creatfood(food,head);
				break;
			}
			p = p->next;
		}

	}

}
//如果生成食物和蛇身重叠次数超过阈值，则按行列顺序指定食物位置 
void setfoodlocation(Snake *head, Food *food)
{
	int i, j, flag;
	Snake *p;
	for (i = 1; i<2*WIDTH-2; i+2)
	{
		for (j = 1; j<HEIGH; j++)
		{
			p = head;
			flag = 0;
			while (p != NULL)
			{
				if (p->x == i&&p->y == j)
				{
					flag = 1;
					break;
				}
				p = p->next;
			}
			if (flag == 0)
			{
				food->x = i;
				food->y = j;
				return;
			}

		}

	}

}
//判断游戏是否失败，蛇头碰身或蛇头撞墙，游戏失败
int isfailure(Snake *head)
{
	Snake *p = head->next;
	if (head->x<=0 || head->x >= 2*WIDTH || head->y<=0 || head->y > HEIGH)
		return 1;

	while (p != NULL)
	{
		if (head->x == p->x&&head->y == p->y)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
//是否吃到食物 
int isSnakemeetFood(Snake *head, Food *food)
{
	if (head->x == food->x&&head->y == food->y)
	{
		return 1;
	}
	return 0;
}
//蛇身增长,返回新的尾结点 
Snake *snakegrow(Snake *head)
{
	Snake *pt = head;
	//新增加的一节不用马上绘制（不用立即设置坐标）
	Snake *p = (Snake*)malloc(sizeof(Snake));
	p->next = NULL;
	while (pt->next != NULL)
	{
		pt = pt->next;

	}
	p->pre = pt;
	pt->next = p;
	return p;
}
//响应用户按键，参数c是按键前的方向
char setcurkeybutton(char c)
{
	char c2 = getch();//获取用户当前的按键
	//如果前一次按下的是暂停键(空格)
	if (c == 'p')
	{
/*		while (c2 != 27 || c2 != 32)
		{
			c2 = getch();
		}
*/
			if (c2 == 27)//用户按esc，结束游戏,在暂停的状态下结束游戏 
			{
				c2 = 'x';
				return c2;
			}
			else if (c2 == 32)//在前一次是暂停的基础上,又按暂停
			{
				c2 = 'p';
				spacenum++;
				return c2;
			}
			else
				return c;
	
	}
	else
	{
		if (c2 == 27)//用户按esc，结束游戏 
		{
			c2 = 'x';
			return c2;
		}
		else if (c2 == 32)
		{
			c2 = 'p';
			spacenum++;
			return c2;
		}
		else if (c2 == 'a'&&c != 'd')
			return c2;
		else if (c2 == 'w'&&c != 's')
			return c2;
		else if (c2 == 'd'&&c != 'a')
			return c2;
		else if (c2 == 's'&&c != 'w')
			return c2;
	}

}
//蛇的移动
void snakemove(Snake *head, Snake *rear, Snake *lastrear, char c)
{
	//坐标传递，从蛇尾开始依次获取前一个结点的坐标，付给当前结点 
	Snake *p = rear;
	lastrear->x = rear->x;
	lastrear->y = rear->y;
	while (p->pre != NULL)
	{
		p->x = p->pre->x;
		p->y = p->pre->y;
		p = p->pre;
	}
	//单独处理头的移动（与运动方向有关）
	if (c == 'a')
		head->x-=2;
	if (c == 'w')
		head->y--;
	if (c == 's')
		head->y++;
	if (c == 'd')
		head->x+=2;

}

//画墙
void drawwall()
{
	int i, j;
	system("cls");
	gotoxy(0, 0);
	printf("------------------------------");
	for (i = 0; i < HEIGH; i++)
	{
		gotoxy(0, i + 1);
		printf("|");
		for (j = 0; j < WIDTH; j++)
		{
			printf("  ");

		}
		printf("|");

	}
	gotoxy(0, HEIGH + 1);
	printf("------------------------------\n");

}
void draw(Snake *head, Snake *lastrear, int grow, Food* food)
{
	Snake *p = head->next;
	//画食物
	gotoxy(food->x, food->y);
	printf("%c", food->c);
	printf("%c", food->c);
	if (grow == 0)
	{
		gotoxy(lastrear->x, lastrear->y);
		printf("  ");
	}
	else
		grow = 0;
	gotoxy(head->x, head->y);
	printf("■");
/*
	while (p != NULL)
	{
		gotoxy((p->x), p->y);
		printf("□");
		p = p->next;
	}
	//printf(" ");
*/
}