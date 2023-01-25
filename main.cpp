#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<clocale>
#include<GL/glut.h>
#include<string>
#include<ctime>
using namespace std;
struct pole//структура для хранения координат поля
{
	float x;
	float y;
	float z;
};
struct frukt//структура для представления фруктов
{
	int x;
	int y;
	int z;
}fruittini;
struct box//структура для хранения массивов вершин
{
	float x[2];
	float y[2];
	float z[2];
	float vz;//определяет хвост или голова, или фрукт
};
struct Release//структура с элементами для управления змейкой с клавиатуры
{
	char w = 'w', a = 'a', s = 's', d = 'd';
};
int start = 2;//определяет на какой ячйки появится змейка 
int x = 0;
int y = 0;
//переменные для управления с клавиатуры
unsigned char key;
char press;
Release release;
const int N = 20;//поле 20 на 20
box b[N*N];
box fruit[1];
pole p[N][N];//для создания поля
//pole back[N][N];
int dif = 100;//сложность, определяет скорость движения змейки
int n = 0;//число элементов в змейке
int last = 0;//предыдущий результат
int best = 0;//лучший результат

void draw_cube(box *b, int i)
{
	if (b[i].vz != 1&&i>0)
		glColor3f(0.0f, 0.196078f, 0.039215f);//тело змейки красим тёмно зелёным
	else if (b[i].vz == 1)
		glColor3f(0.0f, 0.784313f, 0.0f);//голову змейки красим в светло зелёный 
	else if (b[i].vz == 0.5)//выбираем цвет для фруктов
	{
		if (n % 2 == 0)
			glColor3f(0.352941f, 0.0f, 0.784313f);
		else
			glColor3f(0.803921f,0.0f,0.352941f);
	}
	//рисуем кубы змейки
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
	//отрисовываем сетку поля
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
	for (int i = 0; i <= n; i++)//рисуем змейку
	{
		draw_cube(b, i);
	}
	draw_cube(fruit, 0);
	glutSwapBuffers();//переключаем буфер
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
void move_other_cubes(box *b, int n)//смещаем хвост змеи при движении
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
bool move_cube(box *b, const int i)//управление змеёй 
{
	bool lose = false;//логическая переменная, если lose==true, то поражение
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
		fruit[0].vz = 0.0;//если съели фрукт, то нужно создать новый
	}
	system("cls");
	cout << "Snake 3d:" << endl;
	cout << endl << "Help:" << endl;
	cout << "The snake needs to eat as many fruits as possible." << endl << "If the snake eats its tail, the game will end!" << endl << "Good luck :)" << endl;
	cout << endl << "Last score : " << 100*last << endl;
	cout << endl << "Best score : " << 100*best << endl;
	cout << endl << "Your score : " << 100 * n << endl;
	if (fruit[0].vz == 0.0)//если нет фрукта, то создаём новый
	{
		fruittini.x = rand() % 18 + 1;
		fruittini.y = rand() % 18 + 1;
		fruit[0].x[0] = fruittini.x * 480 / N;
		fruit[0].x[1] = (fruittini.x + 1) * 480 / N;
		fruit[0].y[0] = fruittini.y * 480 / N;
		fruit[0].y[1] = (fruittini.y + 1) * 480 / N;
		fruit[0].z[0] = 0 * 480 / N;
		fruit[0].z[1] = 1 * 480 / N;
		fruit[0].vz = 0.5;//фрукт есть на поле
	}
}
void timer(int = 0)//функция для анимации
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
	glutTimerFunc(dif, timer, 0);//после каждого шага змейки мы её перерисовываем (цикл для движения по полю)
}
int main(int argc, char **argv)
{
	int times = (int)time(NULL);
	srand(times);//чтобы случайные числа были действительно случайными при каждой компиляции
	//выбираем случайное место, в котором разместим первый фрукт
	fruittini.x = rand() % 18 + 1;
	fruittini.y = rand() % 18 + 1;
	//просчитываем клетку для 1 фрукта
	fruit[0].x[0] = fruittini.x * 480 / N;
	fruit[0].x[1] = (fruittini.x + 1) * 480 / N;
	fruit[0].y[0] = fruittini.y * 480 / N;
	fruit[0].y[1] = (fruittini.y + 1) * 480 / N;
	fruit[0].z[0] = 0 * 480 / N;
	fruit[0].z[1] = 1 * 480 / N;
	fruit[0].vz = 0.5;
	//просчитаем клетку для головы змейки(клетка из которой начнётся игра)
	b[0].x[0] = start * 480 / N;
	b[0].x[1] = (start + 1) * 480 / N;
	b[0].y[0] = start * 480 / N;
	b[0].y[1] = (start + 1) * 480 / N;
	b[0].z[0] = 0 * 480 / N;
	b[0].z[1] = 1 * 480 / N;
	b[0].vz = 1;
	for (int x = 0; x < N; x++)//просчитываем игровое поле
		for (int y = 0; y < N; y++)
		{
			p[x][y].x = x * 480 / N;
			p[x][y].y = (y + 1) * 480 / N;
		}
	glutInit(&argc, argv);//инициализуерм glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//выбираем двойной буфер и цветовой режим RGB
	glutInitWindowSize(860, 480);//выбираем размер окна
	glutInitWindowPosition(700, 450);//выбираем позицию окна на экране
	glutCreateWindow("Snake 3d");//создаём окно
	glClearColor(0.0, 0.0, 0.0, 1.0);//цвет окна
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-100, 100, -100, 100, 100, 500);//параметры пирамиды видимости(задаём расстояние от камеры до ближней и дальней отсекающей плоскости)
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-230, -150, -220);//смещаем камеру
	glRotatef(-30, 1, 0, 0);//вращение матрицы на угол
	glutDisplayFunc(display);//функция отображения на дисплей
	timer();//функия для анимации
	glutKeyboardFunc(key_pressed);//функция управления с клавиатуры
	glutMainLoop();//передаём управление glut
	return 0;
}
