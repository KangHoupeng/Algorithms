// Spline3Interp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include <time.h>
using namespace std;

/**
 * spline function
 *
 * @param x [in]  array of x-coordinate of control points
 * @param y [in]  array of y-coordinate of control points
 * @param n [in]  count of control points
 * @param t [in]  array of x-coordinate of output points
 * @param m [in]  count of output points
 * @param z [out]  array of y-coordinate of output points
 */
double spline(double *x, double *y, int n, double *t, int m, double *z)
{
	double* dy = new double[n];
	memset(dy, 0, sizeof(double)*n);
	dy[0] = -0.5;

	double* ddy = new double[n];
	memset(ddy, 0, sizeof(double)*n);

	double h1;
	double* s = new double[n];
	double h0 = x[1] - x[0];

	s[0] = 3.0 * (y[1] - y[0]) / (2.0 * h0) - ddy[0] * h0 / 4.0;
	for (int j = 1; j <= n - 2; ++j)
	{
		h1 = x[j + 1] - x[j];
		double alpha = h0 / (h0 + h1);
		double beta = (1.0 - alpha) * (y[j] - y[j - 1]) / h0;
		beta = 3.0 * (beta + alpha * (y[j + 1] - y[j]) / h1);
		dy[j] = -alpha / (2.0 + (1.0 - alpha) * dy[j - 1]);
		s[j] = (beta - (1.0 - alpha) * s[j - 1]);
		s[j] = s[j] / (2.0 + (1.0 - alpha) * dy[j - 1]);
		h0 = h1;
	}
	dy[n - 1] = (3.0*(y[n - 1] - y[n - 2]) / h1 + ddy[n - 1] * h1 / 2.0 - s[n - 2]) / (2.0 + dy[n - 2]);

	for (int j = n - 2; j >= 0; --j)
	{
		dy[j] = dy[j] * dy[j + 1] + s[j];
	}

	for (int j = 0; j <= n - 2; ++j)
	{
		s[j] = x[j + 1] - x[j];
	}

	for (int j = 0; j <= n - 2; ++j)
	{
		h1 = s[j] * s[j];
		ddy[j] = 6.0 * (y[j + 1] - y[j]) / h1 - 2.0 * (2.0 * dy[j] + dy[j + 1]) / s[j];
	}

	h1 = s[n - 2] * s[n - 2];
	ddy[n - 1] = 6.0 * (y[n - 2] - y[n - 1]) / h1 + 2.0 * (2.0 * dy[n - 1] + dy[n - 2]) / s[n - 2];
	double g = 0.0;
	for (int i = 0; i <= n - 2; i++)
	{
		h1 = 0.5 * s[i] * (y[i] + y[i + 1]);
		h1 = h1 - s[i] * s[i] * s[i] * (ddy[i] + ddy[i + 1]) / 24.0;
		g = g + h1;
	}

	for (int j = 0; j <= m - 1; j++)
	{
		int i;
		if (t[j] >= x[n - 1]) {
			i = n - 2;
		}
		else {
			i = 0;
			while (t[j] > x[i + 1]) {
				i = i + 1;
			}
		}
		h1 = (x[i + 1] - t[j]) / s[i];
		h0 = h1 * h1;
		z[j] = (3.0 * h0 - 2.0 * h0 * h1) * y[i];
		z[j] = z[j] + s[i] * (h0 - h0 * h1) * dy[i];
		h1 = (t[j] - x[i]) / s[i];
		h0 = h1 * h1;
		z[j] = z[j] + (3.0 * h0 - 2.0 * h0 * h1) * y[i + 1];
		z[j] = z[j] - s[i] * (h0 - h0 * h1) * dy[i + 1];
	}

	delete[] s;
	delete[] dy;
	delete[] ddy;

	return(g);
}

#define USE_ARR_DEBUG 1
#define USE_ADD_DEBUG 1
#define USE_SINGLE_DEBUG 1
int main()
{
	double xData[5] = { 1.2,2.3,3.5,4.7,6.4 };
	double yData[5] = { 3.4,5.9,7.3,2.8,9.1 };
	clock_t beg_time, end_time;
	double duration = 0.0;

	beg_time = clock();

#if USE_ARR_DEBUG

#if USE_ADD_DEBUG
#if USE_SINGLE_DEBUG
	double xDst[2] = { 3.2,5.6 };
	double yDst[2];
	spline(xData, yData, 5, xDst, 2, &yDst[0]);
	for (int i = 0; i < 2; i++)
	{
		printf("yDst[%d] = %lf\n", i, yDst[i]);
	}
#else
	double xDst[6] = { 9.2,7.8,3.2,5.6,6.2,7.8 };
	double yDst[6];
	spline(xData, yData, 5, &xDst[0], 6, &yDst[0]);
	for (int i = 0; i < 6; i++)
	{
		printf("yDst[%d] = %lf\n", i, yDst[i]);
	}
#endif
#else
	double xDst[2] = { 3.2,5.6 };
	double yDst[2];
	spline(xData, yData, 5, xDst, 2, yDst);
	for (int i = 0; i < 2; i++)
	{
		printf("yDst[%d] = %lf\n", i, yDst[i]);
}
#endif
#else
	double xDst = 3.7;
	double yDst;
	spline(xData, yData, 5, &xDst, 1, &yDst);
	printf("yDst = %lf\n", yDst);
#endif
#if 0
	double a[21][3];//第一列已知点的横坐标，2.3列是其二者之差

	double b[21];//已知点纵坐标

	double h[21];//存放步长

	double c1[21];//μ

	double c2[21];//λ

	double c3[21];//β

	double c4[21];//Ly=f,存放y的值

	double d[21];//d

	double M[21];//Ux=y,存放x的值，也就是原方程要求出的M

	double x[25] = { -5,-4.75,-4.5,-4.25,-4,-3.75,-3.5,-3.25,-3,-2.75,-2.5,-2.25,

						  -2,-1.75,-1.5,-1.25,-1,-0.75,-0.5,-0.25,0 };//原始函数横坐标

	double y[25];//三次样条所得计算值

	double z[25];//函数横坐标对应的值

	double r[25];//三次样条计算值与原函数值相对误差

	int k;

	cout << "请输入本次实验您使用的等距节点的个数：";

	cin >> k;

	cout << "请输入已知点的坐标(x,y):" << endl;

	for (int i = 0; i <= k; i++)

	{

		cin >> b[i] >> a[i][0];

		if (i >= 1)

		{

			h[i - 1] = b[i] - b[i - 1];

		}

	}

	for (int i = 0; i <= k; i++)

	{

		if (i == 0)

		{

			c2[0] = 1;

		}

		else if (i == k)

		{

			c1[k] = 1;

		}

		else

		{

			c1[i] = h[i - 1] / (h[i - 1] + h[i]);

			c2[i] = h[i] / (h[i - 1] + h[i]);

		}

	}

	//2阶均差的计算

	for (int j = 1; j < 3; j++)

	{

		for (int i = j; i <= k; i++)

		{

			a[i][j] = (a[i][j - 1] - a[i - 1][j - 1]) / (b[i] - b[i - j]);

		}

	}

	for (int i = 0; i <= k; i++)

	{

		if (i == 0)

			d[i] = (6 * (a[1][1] - 5 / 338)) / h[i];// 5/338是函数在x0处的导数值

		else if (i == k)

			d[i] = (6 * (5 / 338 - a[k][1])) / h[i - 1];

		else d[i] = 6 * a[2][i];

	}

	//追赶法解对角占优矩阵

	for (int i = 0; i <= k; i++)

	{

		if (i == 0)

		{

			c3[0] = c2[0] / 2; //2是对角占优矩阵对角线的第一个元素

			c4[0] = d[0] / 2;

		}

		else if (i < k)

		{

			c3[i] = c2[i] / (2 - c1[i] * c3[i - 1]);

			c4[i] = (d[i] - c1[i] * c4[i - 1]) / (2 - c1[i] * c3[i - 1]);

		}

		else if (i == k)

		{

			c4[i] = (d[i] - c1[i] * c4[i - 1]) / (2 - c1[i] * c3[i - 1]);

			M[k] = c4[k];

		}

	}

	for (int i = k - 1; i >= 0; i--)

	{

		M[i] = c4[i] - c3[i] * M[i + 1];

	}

	//利用所得写出三次样条表达式并计算函数值，并与原函数值进行比较

	for (int i = 0; i < 21; i++)

	{

		int j = 0;

		for (int w = 0; w < k; w++)

		{

			if ((x[i] >= b[w]) && (x[i] < b[w + 1]))

				j = w;

		}

		y[i] = M[j] * (b[j] - x[i])*(b[j] - x[i])*(b[j] - x[i]) / (6 * h[j] + M[j + 1] * (x[i] - b[j])*(x[i] - b[j])*(x[i] - b[j]) / (6 * h[j] + (a[j][0] - (M[j] * h[j] * h[j] / 6))*((b[j + 1] - x[i]) / h[j]) + (a[j + 1][0] - (M[j + 1] * h[j] * h[j] / 6))*((x[i] - b[j]) / h[j])));

		z[i] = 1 / (x[i] * x[i] + 1);

		r[i] = fabs((y[i] - z[i]) / z[i]);

		//cout << "x的值：" << x[i] << "   理论值：" << z[i] << "     计算所得：" << y[i] << "       误差为：" << r[i] << endl;
		printf("x[%d]的值：%f,\t理论值：%f\t,计算所得：%f\t,误差为：%f\t\n", i, x[i], z[i], y[i], r[i]);

	}
#endif
	end_time = clock();
	duration = (double)(end_time - beg_time);

	printf("\033[1;31;40m The %s run %lf seconds! \033[0m\n", __FUNCTION__, duration);

	system("pause");
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
