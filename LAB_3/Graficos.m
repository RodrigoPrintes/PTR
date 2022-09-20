close all, clc

M = csvread("ArqGrav9.csv");

%plot(M(:,17),M(:,18));
%t 1,refX 2  ,refY 3, ymX 4,ymY 5, ymdotX 6 ,ymdotY 7,Vx 8,Vy 9,
%Ux 10 ,Uy 11 ,Xc 12 ,Xyc 13 ,Xteta 14 ,XdotX 15 ,XdotY 16 ,Yx 17 ,Yy 18


figure();
plot(M(:,2),M(:,3));
title("XRef x Yref");

figure();
plot(M(:,4),M(:,5));
title("Xm x Ym");

figure();
plot(M(:,6),M(:,7));
title("Xmdot x Ymdot");

figure();
plot(M(:,8),M(:,9));
title("V");

figure();
plot(M(:,10),M(:,11));
title("U");

figure();
plot(M(:,12),M(:,13));
title("Xc vs Yc");

figure();
plot(M(:,1)/1000,M(:,12));
title("Xc vs t");

figure();
plot(M(:,1)/1000,M(:,13));
title("Yc vs t");

figure();
plot(M(:,1)/1000,M(:,14));
title("Theta vs t");

figure();
plot(M(:,15),M(:,16));
title("Xdotc vs Ydotc");

figure();
plot(M(:,17),M(:,18));
title("Y final");