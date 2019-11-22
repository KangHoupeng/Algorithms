%参考文献：《二次样条插值的MATLAB实现》 东北大学信息科学与工程学院
clear;clc;
syms z;
x = 0 : (1/5)*pi : pi;
y = [1.0000 2.1756 2.9021 2.9021 2.1756 1.0000];
y1(1,1) = 2;
n1 = length(x)- 1;
y11 = zeros(n1);
y12 = zeros(n1);
y13 = zeros(n1);

for i = 1 : 1 : n1
A1 = (y(1,i+1)- y(1,i)- (x(1,i+1)- x(1,i))*y1(1,i))/(x(1,i+1)- x(1,i))^2;
A2 = y1(1,i);
A3 = y(1,i);
y11(1,i) = A1;
y12(1,i) = A2 - 2*A1*x (1,i);
y13 (1,i) = A1 * x (1,i)^2- A2*x (1,i)+A3;
y1(1,i+1) = 2 * (y(1,i+1)- y(1,i))/(x(1,i+1)- x(1,i))- y1(1,i);
end

for i = 1 : 1 : n1
ai = y11(1,i);
bi = y12(1,i);
ci = y13(1,i);fi=ai*z.^2+bi*z+ci;
%ezplot(z,fi,[x(1,i),x(1,i+1)]);
fplot(z,fi,[x(1,i),x(1,i+1)]);
hold on;
end