#ifndef _SNAKE_H
#define _SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define WIDTH 15
#define HEIGH 15
#define OVERLAP 5 //食物与蛇身重叠次数阈值 


//蛇身结构体 
typedef struct SNAKE Snake;
struct SNAKE
{
	int x;
	int y;
	Snake *next;
	Snake *pre;

};

//食物结构体
typedef struct FOOD
{
	int x;
	int y;
	char c;//食物的内容（字符） 

}Food;
//初始化蛇身,食物，运动方向 
char initSnakeFoodDir(Snake *head, Food *food);
//画墙壁，食物，蛇
void Drawpicture(Snake *head, Food *food);
//创建食物,只改坐标，不重新分配空间 
void creatfood(Food *food,Snake *head);
//避免食物和蛇身重叠 
void avoidoverlap(Snake *head, Food *food);
//如果生成食物和蛇身重叠次数超过阈值，则按行列顺序指定食物位置 
void setfoodlocation(Snake *head, Food *food);
//判断游戏是否失败，蛇头碰身或蛇头撞墙，游戏失败
int isfailure(Snake *head);
//是否吃到食物 ,或蛇身是否与食物重叠 
int isSnakemeetFood(Snake *head, Food *food);
//蛇身增长,返回新的尾结点 
Snake *snakegrow(Snake *head);
//响应用户按键，参数c是按键前的方向
char setcurkeybutton(char c);
//蛇的移动
void snakemove(Snake *head, Snake *rear, Snake *lastrear, char c);

//不闪烁实现

void drawwall();
void draw(Snake *head, Snake *lastrear, int grow,Food* food);

#endif