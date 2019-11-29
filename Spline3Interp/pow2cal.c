#include <stdio.h>
#define ACCURACY 10000
#define NaN 0.000000
//牛顿迭代法实现pow函数

double Absolute(double a) {
	if (a < 0) {
		a = -1 * a;
	}
	return a;
}

double doDataProcess(double x, int n) {
	int number = 1;
	int i, j;
	double x1n = 1, x1 = 1;                                  //x1n表示x1的number次幂

	for (i = 0; i < n; i++) {                                   //number即10^n
		number = number * 10;
	}

	while (Absolute(x1n - x) > 0.0001) {              //通过牛顿迭代法计算t^number=x(t为未知数)的根
		x1n = 1;
		for (j = 0; j < number; j++) {
			x1n = x1n * x1;
		}

		x1 = ((number - 1)*x1n + x) / (number*x1n / x1);

		x1n = 1;
		for (j = 0; j < number; j++) {
			x1n = x1n * x1;
		}                                                   //经过多次迭代，x1n的值逼近方程的根t
	}
	return x1;
}

double powf(double x, double y) {
	int positive = 1;                                   //用来储存y的正负
	double answer = 1;                                  //即结果

	if (x > 0 && y > 0) {
		positive = 1;
	}
	else if (x != 0 && y == 0) {
		return 1;
	}
	else if (x > 0 && y < 0) {
		y = -y;
		positive = 0;
	}
	else if (x == 0 && y > 0) {
		return 0;
	}
	else if (x == 0 && y <= 0) {
		return NaN;
	}
	else if (x < 0 && (y - (int)y < 0.0001 || (y - (int)y > 0.999))) {
		if (y > 0) {
			positive = 1;
		}
		else {
			y = -y;
			positive = 0;
		}
	}
	else {
		return NaN;
	}

	int integer = (int)y;
	int i, j;

	for (i = 0; i < integer; i++) {
		answer = answer * x;
	}

	if ((y - (int)y<0.0001 || y - (int)y>0.999) && positive == 1) {                   //如果y为整数，跳过小数运算部分
		return answer;
	}
	if ((y - (int)y<0.0001 || y - (int)y>0.999) && positive == 0) {
		return 1 / answer;
	}

	double decimal = y - (int)y;

	for (i = 1; i <= ACCURACY; i++) {                               //ACCURACY表示计算精度
		decimal = decimal * 10;

		for (j = 0; j < (int)decimal; j++) {
			answer = answer * doDataProcess(x, i);
		}
		decimal = decimal - (int)decimal;
	}

	if (positive == 1) {
		return answer;
	}
	else {
		return 1 / answer;
	}
}


//幂级数展开实现pow		麦克劳林展开式
double func1(double t, int n) {
	double answer = 1;
	for (int i = 0; i < n; i++) {
		answer = answer * t;
	}

	return answer;
}

double func2(double b, int n) {
	double answer = 1;
	for (int i = 1; i <= n; i++) {
		answer = answer * (b - i + 1) / i;
	}

	return answer;
}

double pow_f(double a, double b) {
	if (a == 0 && b > 0) {
		return 0;
	}
	else if (a == 0 && b <= 0) {
		return NaN;
	}
	else if (a < 0 && !(b - (int)b < 0.0001 || (b - (int)b > 0.999))) {
		return NaN;
	}

	if (a <= 2 && a >= 0) {
		double t = a - 1;
		double answer = 1;
		for (int i = 1; i < ACCURACY; i++) {
			answer = answer + func1(t, i)*func2(b, i);
		}
		return answer;
	}

	else if (a > 2) {
		int time = 0;

		while (a > 2) {
			a = a / 2;
			time++;
		}

		return pow_f(a, b)*pow_f(2, b*time);
	}

	else {
		if ((int)b % 2 == 0) {
			return pow_f(-a, b);
		}
		else {
			return -pow_f(-a, b);
		}
	}
}


int main(void)
{
	printf("%f\n", powf(3.2, 2.8));
	//printf("%f\n", pow_f(3.2, 4.2));
	printf("That's all!\n");
	getchar();
	return 0;
}
