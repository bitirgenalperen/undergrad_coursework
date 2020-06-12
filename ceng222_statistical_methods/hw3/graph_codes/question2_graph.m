x = [-4:0.001:4];
mu = 0;
s = 1;
b = 2.5;
z = (exp(-(x-mu).*(x-mu)/(2*s*s)))/(s*sqrt(2*pi));
r = (3.16900);
t = [-4:0.001:-b] ;
z2 = (exp(-(t-mu).*(t-mu)/(2*s*s)))/(s*sqrt(2*pi));
p = [b:0.001:4] ;
z3 = (exp(-(p-mu).*(p-mu)/(2*s*s)))/(s*sqrt(2*pi));
plot(x,z);
hold on;
title("T-Distribution Plot Two-Tails Alpha = 0.01","fontsize",15);
xlabel("T-Value","fontsize",15);
ylabel("Density of the Probability","fontsize",15);
area(t,z2,"FaceColor", "red");
area(p,z3,"FaceColor", "red");
plot([-b,-b],[0,0.0176],'r');
plot([b,b],[0,0.0176],'r');
xticks([-b 0 b]);
xticklabels({'-3.169','0','3.169'});
txt1 = ' \leftarrow Rejection Region \alpha/2';
text(x(1495),0.01,txt1,'FontSize',18)
txt2 = ' Rejection Region \alpha/2 \rightarrow';
text(x(5400),0.01,txt2,'FontSize',18)
txt3 = 'Acceptance Region';
text(x(3350),0.2,txt3,'FontSize',28)
hold off