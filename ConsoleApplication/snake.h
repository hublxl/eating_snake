#ifndef _SNAKE_H
#define _SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define WIDTH 15
#define HEIGH 15
#define OVERLAP 5 //ʳ���������ص�������ֵ 


//����ṹ�� 
typedef struct SNAKE Snake;
struct SNAKE
{
	int x;
	int y;
	Snake *next;
	Snake *pre;

};

//ʳ��ṹ��
typedef struct FOOD
{
	int x;
	int y;
	char c;//ʳ������ݣ��ַ��� 

}Food;
//��ʼ������,ʳ��˶����� 
char initSnakeFoodDir(Snake *head, Food *food);
//��ǽ�ڣ�ʳ���
void Drawpicture(Snake *head, Food *food);
//����ʳ��,ֻ�����꣬�����·���ռ� 
void creatfood(Food *food,Snake *head);
//����ʳ��������ص� 
void avoidoverlap(Snake *head, Food *food);
//�������ʳ��������ص�����������ֵ��������˳��ָ��ʳ��λ�� 
void setfoodlocation(Snake *head, Food *food);
//�ж���Ϸ�Ƿ�ʧ�ܣ���ͷ�������ͷײǽ����Ϸʧ��
int isfailure(Snake *head);
//�Ƿ�Ե�ʳ�� ,�������Ƿ���ʳ���ص� 
int isSnakemeetFood(Snake *head, Food *food);
//��������,�����µ�β��� 
Snake *snakegrow(Snake *head);
//��Ӧ�û�����������c�ǰ���ǰ�ķ���
char setcurkeybutton(char c);
//�ߵ��ƶ�
void snakemove(Snake *head, Snake *rear, Snake *lastrear, char c);

//����˸ʵ��

void drawwall();
void draw(Snake *head, Snake *lastrear, int grow,Food* food);

#endif