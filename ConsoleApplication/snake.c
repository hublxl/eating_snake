#include "snake.h"
#include <windows.h>

//��ʼ������,ʳ��˶����� 
char initSnakeFoodDir(Snake *head, Food *food)
{
	//��ͷ��ʼλ��,Χǽ���м�ľ��������ڣ�1/2���Σ� 
	int x = WIDTH / 4 + rand() % WIDTH / 2;
	int y = HEIGH / 4 + rand() % HEIGH / 2;
	int i;
	char c;

	head->x = x;
	head->y = y;
	head->pre = NULL;
	head->next = NULL;

	//��ʼ��ʳ��,�˴����������Ƿ������ص�	
	creatfood(food);
	//����ʳ���������ص������
	avoidoverlap(head, food);
	//�漴���ó�ʼ�˶����� 
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
//��ǽ�ڣ�ʳ���
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
			//��������
			while (p != NULL)
			{
				if (p->x == j&&p->y == i)
				{
					if (p == head)//����ͷ 
					{
						printf("��");
					}
					else
						printf("��");

					flag = 1;
					break;
				}
				p = p->next;
			}
			//����ʳ�� 
			if (flag == 0)
			{
				if (food->x == j&&food->y == i)
				{
					putchar(food->c);
					putchar(food->c);
					//flag=1;
					continue;
				}

				printf("  ");//���ƿհ� 
			}

		}
		printf("|\n");

	}


	printf("------------------------------\n");

}
//����ʳ��,ֻ�����꣬�����·���ռ� 
void creatfood(Food *food)
{
	food->x = rand() % (WIDTH - 1) + 1;
	food->y = rand() % (HEIGH - 1) + 1;
	food->c = 65 + rand() % 26;//���������д��ĸ 

}
//����ʳ��������ص� 
void avoidoverlap(Snake *head, Food *food)
{
	Snake *p;
	int num = 0;//�ص�����
	int flag = 1;//�Ƿ��ص�
	while (flag)
	{
		//����ص�����������ֵ 
		if (num>OVERLAP)
		{
			setfoodlocation(head, food);
			return;
		}
		p = head;//����ͷ�������ж�ÿһ���Ƿ���ʳ���ص� 
		flag = 0;
		while (p != NULL)
		{
			if (isSnakemeetFood(p, food))
			{
				num++;
				flag = 1;
				creatfood(food);
				break;
			}
			p = p->next;
		}

	}

}
//�������ʳ��������ص�����������ֵ��������˳��ָ��ʳ��λ�� 
void setfoodlocation(Snake *head, Food *food)
{
	int i, j, flag;
	Snake *p;
	for (i = 0; i<WIDTH; i++)
	{
		for (j = 0; j<HEIGH; j++)
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
//�ж���Ϸ�Ƿ�ʧ�ܣ���ͷ�������ͷײǽ����Ϸʧ��
int isfailure(Snake *head)
{
	Snake *p = head->next;
	if (head->x<0 || head->x >= WIDTH || head->y<0 || head->y >= HEIGH)
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
//�Ƿ�Ե�ʳ�� 
int isSnakemeetFood(Snake *head, Food *food)
{
	if (head->x == food->x&&head->y == food->y)
	{
		return 1;
	}
	return 0;
}
//��������,�����µ�β��� 
Snake *snakegrow(Snake *head)
{
	Snake *pt = head;
	//�����ӵ�һ�ڲ������ϻ��ƣ����������������꣩
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
//��Ӧ�û�����������c�ǰ���ǰ�ķ���
char setcurkeybutton(char c)
{
	char c2 = getch();//��ȡ�û���ǰ�İ���
	if (c2 == 27)//�û���esc��������Ϸ 
		c = 'x';
	else if (c2 == 'a'&&c != 'd')
		c = c2;
	else if (c2 == 'w'&&c != 's')
		c = c2;
	else if (c2 == 'd'&&c != 'a')
		c = c2;
	else if (c2 == 's'&&c != 'w')
		c = c2;
	return c;
}
//�ߵ��ƶ�
void snakemove(Snake *head, Snake *rear, char c)
{
	//���괫�ݣ�����β��ʼ���λ�ȡǰһ���������꣬������ǰ��� 
	Snake *p = rear;

	while (p->pre != NULL)
	{
		p->x = p->pre->x;
		p->y = p->pre->y;
		p = p->pre;
	}
	//��������ͷ���ƶ������˶������йأ�
	if (c == 'a')
		head->x--;
	if (c == 'w')
		head->y--;
	if (c == 's')
		head->y++;
	if (c == 'd')
		head->x++;

}


