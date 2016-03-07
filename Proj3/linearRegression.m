close all;
clear all;
clc;
P=[
36961	2503;
43621	2992;
15694	1042;
36231	2487;
29945	2014;
40588	2805;
75255	5062;
37709	2643;
30899	2126;
25486	1784;
37497	2641;
40398	2766;
74105	5047;
76725	5312;
18317	1215;%%french

35680	2217;%english
42514	2761;
15162	990;
35298	2274;
29800	1865;
40255	2606;
74532	4805;
37464	2396;
31030	1993;
24843	1627;
36172	2375;
39552	2560;
72545	4597;
75352	4871;
18031	1119;];
P=P';
[m,n]=size(P);

W=rand(1,2)
b=rand

y=[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ...
   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
subplot(2,1,1);
hold on
plot(P(1,1:15),P(2,1:15),'o',P(1,16:30),P(2,16:30),'or')
title('Hard classification');
xlabel('Number of weight updates');
loss=ones(1,30);
repeat=0;
i=1;

while sum(loss)~=0
% for k=1:950
    repeat=repeat+1;
    hw=hardlim(W*P+b);
    loss=y-hw;
    error(i)=1-sum(y.^2)/(sum(y.^2)+sum(loss.^2));
    W=W+loss*P';
    b=b+sum(loss);
    i=i+1;
end
W
b
repeat
%%slope
px=-(b/(W(1,1)));
py=-(b/(W(1,2)));

x=0:80000;
curve=((py-0)/(0-px))*x+py;
plot(x,curve);
legend('French','English','Classifier','Location','northwest');
subplot(2,1,2);
plot(error);
title('Error with hard classification');
xlabel('Number of weight updates');
ylabel('Error');
axis([0 repeat+uint16(repeat/100) 0 1]);



Wl=rand(1,2)
bl=rand
figure()
subplot(2,1,1);
hold on
plot(P(1,1:15),P(2,1:15),'o')
plot(P(1,16:30),P(2,16:30),'or')
loss=ones(1,30);
repeat=0;
i=1;
e=0;
while sum(loss)~=0
% for k=1:70370
    hw=1./(1+exp(-(Wl*P+bl)));
    loss=y-hw;
    error(i)=1-sum(y.^2)/(sum(y.^2)+sum(loss.^2));
    Wl=Wl+loss*P';
    bl=bl+sum(loss);
    repeat=repeat+1;
    i=i+1;
end
loss;
Wl
bl
repeat

%%slope
px=-(bl/(Wl(1,1)));
py=-(bl/(Wl(1,2)));
x=0:80000;
curve2=((py-0)/(0-px))*x+py;
plot(x,curve2);
legend('French','English','Classifier','Location','northwest');
title('Clasification with logistic regression');
xlabel('Number of weight updates');
subplot(2,1,2);
plot(error);
title('Error with logistic regression');
xlabel('Number of weight updates');
ylabel('Error');
axis([0 repeat+uint32(repeat/100) 0 1]);

