clear;clc;
x = [0 1 2.5 3.6 5 7 8.1 10];
%y = sin(x);
y = [12 2.9 5.6 7.8 3.1 9.2 4.5 5.6];
xx = 0:.25:10;
yy = spline(x,y,xx);
plot(x,y,'o',xx,yy)