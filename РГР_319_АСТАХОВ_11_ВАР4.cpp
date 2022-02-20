#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;
double F(double x)
{
	return (3.0 * x + 4.0) / (2.0 * x + 7.0);
}
double trap_method(double* y,int size,double y_first,double y_last,double h)
{
	double res = 0;
	for (int i = 1; i < size-1;i++)
	{
		res += y[i];
	}
	res = h/2.0*((2*res)+y_first+y_last);
	return res;
}
double square_method(double* y, int size, double x_first, double x_last,double h)
{
	double res = 0, left = 0, right = 0;
	for (int i = 1; i < size; i++)
		left += y[i];
	for (int i = 0; i < size-1 ; i++)
		right += y[i];
	left = left * h;
	right = right * h;
	res = (right+left) / 2.0;
	return res;
}
double sympson_method(double* y, int size, double y_first, double y_last, double h)
{
	double res = 0;
	for (int i = 1; i < size-1 ; i++)
	{
		if (i % 2 == 1)
			res += 4*y[i];
	}
	res = res;
	for (int i = 2; i < size-2 ; i++)
	{
		if (i % 2 == 0)
			res += 2*y[i];
	}
	res = res + (y_first + y_last);
	res = (h / 3.0)*res;
	return res;
}
double runge_check(double res1, double res2, double R,int acc)
{
	double res = abs((res1 - res2) / (pow(R, acc) - 1));
	return res;
}
void main()
{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	int sizex = 5;
	double x_first=-2.0, x_last=2.0, * x,*y,h=1.0,*x1,*y1,check;
	x = new double[sizex];
	y = new double[sizex];
	for (int i = 0; i < sizex; i++)		
	{
		x[i] = x_first;
		x_first += 1.0;
	}
	x_first = -2.0;
	for (int i = 0; i < sizex; i++)
	{
		y[i] = F(x[i]);
	}
	double res = trap_method(y, sizex, y[0], y[4], h),trap,square,symp;
	cout <<"Шаг 1.0:\nМетод трапеций:"<< res<<endl;
	trap = res;
	res = square_method(y, sizex, y[0], y[4],1.0);
	cout <<"Метод прямоугольников:"<< res << endl;
	square = res;
	res = sympson_method(y, sizex, y[0], y[4], 1.0);
	cout << "Метод Симпсона:" << res << endl;
	cout << endl << endl;
	symp = res;
	//////////////////////
	h = 0.5; sizex = 9;
	x_first = -2.0; x_last = 2.0;
	x1 = new double[sizex]; y1 = new double[sizex];
	double res1,XD1,XD2,XD3;
	for (int i = 0; i < sizex; i++)
	{
		x1[i] = x_first;
		x_first += 0.5;
	}
	x_first = -2.0;
	for (int i = 0; i < sizex; i++)
		y1[i] = F(x1[i]);
	res1 = trap_method(y1, sizex, y1[0],y1[8], h);
	cout << "Шаг 0.5:\nМетод трапеций:" << res1 << endl;
	check = runge_check(trap, res1, 1.0 / 0.5, 2);
	XD1 = check;
	res1 = square_method(y1, sizex, y1[0], y1[8],0.5);
	cout << "Метод прямоугольников:" << res1 << endl;
	check = runge_check(square, res1, 1.0 / 0.5, 2);
	XD2 = check;
	res1 = sympson_method(y1, sizex, y1[0], y1[8], 0.5);
	cout << "Метод Симпсона:" << res1 << endl;
	check = runge_check(symp, res1, 1.0 / 0.5, 4);
	XD3 = check;
	cout << endl << endl;
	cout << "погрешность:\nМетодтрапеций:" << XD1 << endl << "Метод прямоугольников:" << XD2 << endl << "Метод Симпосона:" << XD3 << endl;
}