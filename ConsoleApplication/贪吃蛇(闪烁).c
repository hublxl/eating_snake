#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>//���������ʱ��_sleep() 
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void main()
{
	char c;//���ƶ��ķ���

	Snake snake, *head, *rear;
	Snake *lastrear;
	srand((unsigned)time(NULL));//��ʼ�����������

	//��ʼ������ʳ��տ�ʼ��ֻ��һ��
	head = rear = &snake;
	Food *food = (Food*)malloc(sizeof(Food));

	printf("\t\t======��ӭʹ��̰������Ϸ======\t\t\n");
	printf("��Ϸ˵����\n");
	printf("1.w(��)��s(��),a(��),d(��)\n");
	printf("2.��esc�˳���Ϸ\n");
	printf("3.���ƶ���ʳ�У������ͷ���������ǽ�ڣ�����Ϸ����\n");
	printf("���������ʼ��Ϸ\n");
	getch();

	//��ʼ���ߣ�ʳ��˶�����
	c = initSnakeFoodDir(head, food);


	while (1)
	{

		//���Ƿ�Ե�ʳ�� 
		if (isSnakemeetFood(head, food))
		{
			rear = snakegrow(head);//��������
			creatfood(food);    //�������ʳ���ʵ���������������� 
			avoidoverlap(head, food);//����ʳ��������ص�

		}
		//��Ұ�������
		if (kbhit())

			c = setcurkeybutton(c);
		if (c == 'x')
		{
			puts("�û���ֹ\nGame over\n");
			break;
		}


		//�ߵ��ƶ�
		snakemove(head, rear, c);
		if (isfailure(head))
		{
			printf("��Ϸʧ��\n");
			break;
		}

		//���ƻ��� 
		Drawpicture(head, food);

		//_sleep(200);//��Ļˢ�¼�� 
		Sleep(200);

	}
	//gotoxy(0,17);
	printf("ллʹ�ã��ټ�\n");
	system("pause");

}