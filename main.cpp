#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<clocale>
#include<GL/glut.h>
#include<string>
#include<ctime>
using namespace std;
struct pole//��������� ��� �������� ��������� ����
{
	float x;
	float y;
	float z;
};
struct frukt//��������� ��� ������������� �������
{
	int x;
	int y;
	int z;
}fruittini;
struct box//��������� ��� �������� �������� ������
{
	float x[2];
	float y[2];
	float z[2];
	float vz;//���������� ����� ��� ������, ��� �����
};
struct Release//��������� � ���������� ��� ���������� ������� � ����������
{
	char w = 'w', a = 'a', s = 's', d = 'd';
};
int start = 2;//���������� �� ����� ����� �������� ������ 
int x = 0;
int y = 0;
//���������� ��� ���������� � ����������
unsigned char key;
char press;
Release release;
const int N = 20;//���� 20 �� 20
box b[N*N];
box fruit[1];
pole p[N][N];//��� �������� ����
//pole back[N][N];
int dif = 100;//���������, ���������� �������� �������� ������
int n = 0;//����� ��������� � ������
int last = 0;//���������� ���������
int best = 0;//������ ���������

void draw_cube(box *b, int i)
{
	if (b[i].vz != 1&&i>0)
		glColor3f(0.0f, 0.196078f, 0.039215f);//���� ������ ������ ���� ������
	else if (b[i].vz == 1)
		glColor3f(0.0f, 0.784313f, 0.0f);//������ ������ ������ � ������ ������ 
	else if (b[i].vz == 0.5)//�������� ���� ��� �������
	{
		if (n % 2 == 0)
			glColor3f(0.352941f, 0.0f, 0.784313f);
		else
			glColor3f(0.803921f,0.0f,0.352941f);
	}
	//������ ���� ������
	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[1]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[0]);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[1], b[i].y[0], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[0], b[i].y[0], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[1]);
	glVertex3f(b[i].x[0], b[i].y[1], b[i].z[0]);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//������������ ����� ����
	glColor3f(0.0, 1.0, 1.0);
	for (int x = 0; x < N; x++)
	{
		glBegin(GL_LINE_STRIP);
		for (int y = 0; y < N; y++)
			glVertex3f(p[x][y].x, p[x][y].y, p[x][y].z * 10);
		glEnd();
	}
	for (int y = 0; y < N; y++)
	{
		glBegin(GL_LINE_STRIP);
		for (int x = 0; x < N; x++)
			glVertex3f(p[x][y].x, p[x][y].y, p[x][y].z * 10);
		glEnd();
	}
	for (int i = 0; i <= n; i++)//������ ������
	{
		draw_cube(b, i);
	}
	draw_cube(fruit, 0);
	glutSwapBuffers();//����������� �����
}
bool valid_move(box *b, const int i)
{
	int tempx1, tempy1;
	int tempx2, tempy2;
	tempx1 = b[0].x[0];
	tempx2 = b[0].x[1];
	tempy1 = b[0].y[0];
	tempy2 = b[0].y[1];

	if (release.a = 'a')
	{
		tempx1 -= 480 / N;
		tempx2 -= 480 / N;
		for (int m = 4; m < i; m++)
		{
			if (tempx1 == b[m - 1].x[0] && tempx2 == b[m - 1].x[1] && tempy1 == b[m - 1].y[0] && tempy2 == b[m - 1].y[1])
				return false;
		}
		return true;
	}
	if (release.s = 's')
	{
		tempy1 -= 480 / N;
		tempy2 -= 480 / N;
		for (int m = 4; m < i; m++)
		{
			if (tempx1 == b[m - 1].x[0] && tempx2 == b[m - 1].x[1] && tempy1 == b[m - 1].y[0] && tempy2 == b[m - 1].y[1])
				return false;
		}
		return true;
	}
	if (release.w = 'w')
	{
		tempy1 += 480 / N;
		tempy2 += 480 / N;
		for (int m = 4; m < i; m++)
		{
			if (tempx1 == b[m - 1].x[0] && tempx2 == b[m - 1].x[1] && tempy1 == b[m - 1].y[0] && tempy2 == b[m - 1].y[1])
				return false;
		}
		return true;
	}
	if (release.d = 'd')
	{
		tempx1 += 480 / N;
		tempx2 += 480 / N;
		for (int m = 4; m < i; m++)
		{
			if (tempx1 == b[m - 1].x[1] && tempx2 == b[m - 1].x[0] && tempy1 == b[m - 1].y[1] && tempy2 == b[m - 1].y[0])
				return false;
		}
		return true;
	}
	return true;
}
void move_other_cubes(box *b, int n)//������� ����� ���� ��� ��������
{
	if (n != 0)
	{
		for (int m = n; m > 0; m--)
		{
			b[m].x[0] = b[m - 1].x[0];
			b[m].x[1] = b[m - 1].x[1];
			b[m].y[0] = b[m - 1].y[0];
			b[m].y[1] = b[m - 1].y[1];
			b[m].z[0] = b[m - 1].z[0];
			b[m].z[1] = b[m - 1].z[1];
		}
	}
}
void key_pressed(unsigned char key, int x, int y)
{
	if (key == 'd'&&b[1].x[0] != b[0].x[1])
	{
		press = 'd';
		release.d = 0;
	}
	if (key == 'a'&&b[1].x[1] != b[0].x[0])
	{
		press = 'a';
		release.a = 0;
	}
	if (key == 'w' && b[1].y[0] != b[0].y[1])
	{
		press = 'w';
		release.w = 0;
	}
	if (key == 's' && b[1].y[1] != b[0].y[0])
	{
		press = 's';
		release.s = 0;
	}
}
//void key_Up(unsigned char key, int x, int y){}
bool move_cube(box *b, const int i)//���������� ���� 
{
	bool lose = false;//���������� ����������, ���� lose==true, �� ���������
	if (lose==false)
	{
		if (press == 'a'/*&&release.a=='a'*/)
		{
			if (b[0].x[0] != 0)
			{
				move_other_cubes(b, i);
				b[0].x[0] -= 480 / N;
				b[0].x[1] -= 480 / N;
			}
			if (valid_move(b,i)==false)
				lose = true;
		}
		if (press == 's'/*&&release.s!='s'*/)
		{
			if (b[0].y[0] != 480 / N)
			{
				move_other_cubes(b, i);
				b[0].y[0] -= 480 / N;
				b[0].y[1] -= 480 / N;
			}
			if (valid_move(b, i) == false)
				lose = true;
		}
		if (press == 'd'/*&&release.d!='d'*/)
		{
			if (b[0].x[0] != (N - 2) * 480 / N)
			{
				move_other_cubes(b, i);
				b[0].x[0] += 480 / N;
				b[0].x[1] += 480 / N;
			}
			if (valid_move(b, i) == false)
				lose = true;
		}

		if (press == 'w'/*&&release.w!='w'*/)
		{
			if (b[0].y[0] != (N - 1) * 480 / N)
			{
				move_other_cubes(b, i);
				b[0].y[0] += 480 / N;
				b[0].y[1] += 480 / N;
			}
			if (valid_move(b, i) == false)
				lose = true;
		}
	}
	return lose;
}
void check_fruit(box *b)
{
	if (b[0].x[0] == fruit[0].x[0] && b[0].x[1] == fruit[0].x[1] && b[0].y[0] == fruit[0].y[0] && b[0].y[1] == fruit[0].y[1] && b[0].z[0] == fruit[0].z[0] && b[0].z[1] == fruit[0].z[1])
	{
		n++;
		fruit[0].vz = 0.0;//���� ����� �����, �� ����� ������� �����
	}
	system("cls");
	cout << "Snake 3d:" << endl;
	cout << endl << "Help:" << endl;
	cout << "The snake needs to eat as many fruits as possible." << endl << "If the snake eats its tail, the game will end!" << endl << "Good luck :)" << endl;
	cout << endl << "Last score : " << 100*last << endl;
	cout << endl << "Best score : " << 100*best << endl;
	cout << endl << "Your score : " << 100 * n << endl;
	if (fruit[0].vz == 0.0)//���� ��� ������, �� ������ �����
	{
		fruittini.x = rand() % 18 + 1;
		fruittini.y = rand() % 18 + 1;
		fruit[0].x[0] = fruittini.x * 480 / N;
		fruit[0].x[1] = (fruittini.x + 1) * 480 / N;
		fruit[0].y[0] = fruittini.y * 480 / N;
		fruit[0].y[1] = (fruittini.y + 1) * 480 / N;
		fruit[0].z[0] = 0 * 480 / N;
		fruit[0].z[1] = 1 * 480 / N;
		fruit[0].vz = 0.5;//����� ���� �� ����
	}
}
void timer(int = 0)//������� ��� ��������
{
	if (move_cube(b, n) == false)
	{
		display();
		check_fruit(b);
	}
	else
	{
		cout << endl << "Game over!!!" << endl;
		cout << endl << "Start a new game" << endl;
		if (n > best)
			best = n;
		last = n;
		n = 0;
	}
	glutTimerFunc(dif, timer, 0);//����� ������� ���� ������ �� � �������������� (���� ��� �������� �� ����)
}
int main(int argc, char **argv)
{
	int times = (int)time(NULL);
	srand(times);//����� ��������� ����� ���� ������������� ���������� ��� ������ ����������
	//�������� ��������� �����, � ������� ��������� ������ �����
	fruittini.x = rand() % 18 + 1;
	fruittini.y = rand() % 18 + 1;
	//������������ ������ ��� 1 ������
	fruit[0].x[0] = fruittini.x * 480 / N;
	fruit[0].x[1] = (fruittini.x + 1) * 480 / N;
	fruit[0].y[0] = fruittini.y * 480 / N;
	fruit[0].y[1] = (fruittini.y + 1) * 480 / N;
	fruit[0].z[0] = 0 * 480 / N;
	fruit[0].z[1] = 1 * 480 / N;
	fruit[0].vz = 0.5;
	//���������� ������ ��� ������ ������(������ �� ������� ������� ����)
	b[0].x[0] = start * 480 / N;
	b[0].x[1] = (start + 1) * 480 / N;
	b[0].y[0] = start * 480 / N;
	b[0].y[1] = (start + 1) * 480 / N;
	b[0].z[0] = 0 * 480 / N;
	b[0].z[1] = 1 * 480 / N;
	b[0].vz = 1;
	for (int x = 0; x < N; x++)//������������ ������� ����
		for (int y = 0; y < N; y++)
		{
			p[x][y].x = x * 480 / N;
			p[x][y].y = (y + 1) * 480 / N;
		}
	glutInit(&argc, argv);//������������� glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//�������� ������� ����� � �������� ����� RGB
	glutInitWindowSize(860, 480);//�������� ������ ����
	glutInitWindowPosition(700, 450);//�������� ������� ���� �� ������
	glutCreateWindow("Snake 3d");//������ ����
	glClearColor(0.0, 0.0, 0.0, 1.0);//���� ����
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-100, 100, -100, 100, 100, 500);//��������� �������� ���������(����� ���������� �� ������ �� ������� � ������� ���������� ���������)
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-230, -150, -220);//������� ������
	glRotatef(-30, 1, 0, 0);//�������� ������� �� ����
	glutDisplayFunc(display);//������� ����������� �� �������
	timer();//������ ��� ��������
	glutKeyboardFunc(key_pressed);//������� ���������� � ����������
	glutMainLoop();//������� ���������� glut
	return 0;
}