x = [-4:0.001:4];
mu = 0;
s = 1;
b = 1.64;% z_critical
z = (exp(-(x-mu).*(x-mu)/(2*s*s)))/(s*sqrt(2*pi));
r = (1.64);
t = [b:0.001:4] ;
zcl = (exp(-(t-mu).*(t-mu)/(2*s*s)))/(s*sqrt(2*pi));
p = [b:0.001:4] ;
zcr = (exp(-(p-mu).*(p-mu)/(2*s*s)))/(s*sqrt(2*pi));
plot(x,z);
hold on;
title("Z-Distribution Plot Right-Tail Alpha = 0.05","fontsize",15);
xlabel("Z-Value","fontsize",15);
ylabel("Density of the Probability","fontsize",15);
area(t,zcl,"FaceColor", "red");
plot([b,b],[0,0.104],'r');
xticks([0,b]);
xticklabels({'0','1.640'});
txt1 = 'Rejection Region \alpha = 0.05 \rightarrow ';
text(x(4350),0.03,txt1,'FontSize',18)
txt3 = 'Acceptance Region';
text(x(3300),0.2,txt3,'FontSize',28)
hold off
