#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>//���������ʱ��_sleep() 

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
	char c=0;//���ƶ��ķ���
	char cpre;
	int grow;
	Snake snake, *head, *rear;
	Snake *lastrear;
	srand((unsigned)time(NULL));//��ʼ�����������

	//��ʼ������ʳ��տ�ʼ��ֻ��һ��
	head = rear = &snake;
	Food *food = (Food*)malloc(sizeof(Food));
	lastrear = (Snake *)malloc(sizeof(Snake));

	printf("\t\t======��ӭʹ��̰������Ϸ======\t\t\n");
	printf("��Ϸ˵����\n");
	printf("1.w(��)��s(��),a(��),d(��)\n");
	printf("2.��esc�˳���Ϸ\n");
	printf("3.���ƶ���ʳ�У������ͷ���������ǽ�ڣ�����Ϸ����\n");
	printf("���������ʼ��Ϸ\n");
	getch();

	//��ʼ���ߣ�ʳ��˶�����
	cpre = initSnakeFoodDir(head, food);
	
	drawwall();
	gotoxy(0, 19);
	printf("��ʼ���ķ�����%c\n", cpre);
	while (1)
	{
		grow = 0;
		//���Ƿ�Ե�ʳ�� 
		if (isSnakemeetFood(head, food))
		{
			rear = snakegrow(head);//��������
			creatfood(food,head);    //�������ʳ���ʵ���������������� 
			avoidoverlap(head, food);//����ʳ��������ص�
			grow = 1;
		}
		
		//��Ұ�������
		if (kbhit())
		{
			c = setcurkeybutton(cpre);
			gotoxy(0, 20);
			printf("���µļ�%c", c);
		}
			
		if (c != 'x'&&c != 'p'&&c!=0)
		{
			cpre = c;//cpreֻ��¼�����ķ���,����¼�˳�,��ͣ
			gotoxy(0, 21);
			printf("���µķ���%c", cpre);
		}
		if (c == 'x')
		{
			gotoxy(0, 17);
			puts("�û���ֹ\nGame over\n");
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
				puts("�û���ֹ\nGame over\n");
				break;
			}
		}
		gotoxy(0, 22);
		printf("��ʼ��֮��Ҫ�˶��ķ���%c", cpre);

		//�ߵ��ƶ�
		snakemove(head, rear,lastrear, cpre);
		if (isfailure(head))
		{
			gotoxy(0, 17);
			printf("��Ϸʧ��\n");
			break;
		}

		//���ƻ��� 
		//Drawpicture(head, food);
		draw(head, lastrear, grow, food);
		//_sleep(200);//��Ļˢ�¼�� 
		Sleep(200);

	}
	gotoxy(0,18);
	printf("ллʹ�ã��ټ�\n");
	system("pause");

}