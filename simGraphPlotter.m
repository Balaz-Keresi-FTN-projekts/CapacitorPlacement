clear;
scenario2;
scenario3;
scenario4;
scenario5;
scenario6;
scenario7;

% Poslednja je x osa

my_graph = figure();

% AKTIVNA SANAGA
plot(  Pdist2(:,1), Pdist2(:,2), Pdist4(:,1), Pdist4(:,2), Pdist6(:,1), Pdist6(:,2), 'LineWidth', 2 );
title('Protok aktivne snage preko korena mreze [MW]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Pdist1.jpg');

plot(  Pdist3(:,1), Pdist3(:,2), Pdist5(:,1), Pdist5(:,2), Pdist7(:,1), Pdist7(:,2), 'LineWidth', 2 );
title('Protok aktivne snage preko korena mreze [MW]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Pdist2.jpg');


% REAKTIVNA SNAGA
plot(  Qdist2(:,1), Qdist2(:,2), Qdist4(:,1), Qdist4(:,2), Qdist6(:,1), Qdist6(:,2), 'LineWidth', 2 );
title('Protok reaktivne snage preko korena mreze [MVAr]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northeast');

print(my_graph, 'Qdist1.jpg');

plot(  Qdist3(:,1), Qdist3(:,2), Qdist5(:,1), Qdist5(:,2), Qdist7(:,1), Qdist7(:,2), 'LineWidth', 2 );
title('Protok reaktivne snage preko korena mreze [MVAr]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northeast');

print(my_graph, 'Qdist2.jpg');


% AKTIVNI GUBICI
plot(  Ploss2(:,1), Ploss2(:,2), Ploss4(:,1), Ploss4(:,2), Ploss6(:,1), Ploss6(:,2), 'LineWidth', 2 );
title('Gubici aktivne snage [MW]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Ploss1.jpg');

plot(  Ploss3(:,1), Ploss3(:,2), Ploss5(:,1), Ploss5(:,2), Ploss7(:,1), Ploss7(:,2), 'LineWidth', 2 );
title('Gubici aktivne snage [MW]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Ploss2.jpg');



% REAKTIVNI GUBICI
plot(  Qloss2(:,1), Qloss2(:,2), Qloss4(:,1), Qloss4(:,2), Qloss6(:,1), Qloss6(:,2), 'LineWidth', 2 );
title('Gubici reaktivne snage [MVAr]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Qloss1.jpg');

plot(  Qloss3(:,1), Qloss3(:,2), Qloss5(:,1), Qloss5(:,2), Qloss7(:,1), Qloss7(:,2), 'LineWidth', 2 );
title('Gubici reaktivne snage [MVAr]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Qloss2.jpg');



% STRUJA PREKO KORENA MREZE
plot(  Iroot2(:,1), Iroot2(:,2), Iroot4(:,1), Iroot4(:,2), Iroot6(:,1), Iroot6(:,2), 'LineWidth', 2 );
title('Struja preko korena mreze [A]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Iroot1.jpg');

plot(  Iroot3(:,1), Iroot3(:,2), Iroot5(:,1), Iroot5(:,2), Iroot7(:,1), Iroot7(:,2), 'LineWidth', 2 );
title('Struja preko korena mreze [A]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Iroot2.jpg');



% NAPON CVORA 6
plot(  Vendprim2(:,1), Vendprim2(:,2), Vendprim4(:,1), Vendprim4(:,2), Vendprim6(:,1), Vendprim6(:,2), 'LineWidth', 2 );
title('Napon cvora 6 [kV]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Vendprim1.jpg');

plot(  Vendprim3(:,1), Vendprim3(:,2), Vendprim5(:,1), Vendprim5(:,2), Vendprim7(:,1), Vendprim7(:,2), 'LineWidth', 2 );
title('Struja cvora 6 [kV]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Vendprim2.jpg');



% STRUJA PREKO KORENA MREZE
plot(  Vendsecond2(:,1), Vendsecond2(:,2), Vendsecond4(:,1), Vendsecond4(:,2), Vendsecond6(:,1), Vendsecond6(:,2), 'LineWidth', 2 );
title('Napon cvora 7 [kV]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 2', 'C u cvoru 4', 'C u cvoru 6', 'location', 'northwest');

print(my_graph, 'Vendsecond1.jpg');

plot(  Vendsecond3(:,1), Vendsecond3(:,2), Vendsecond5(:,1), Vendsecond5(:,2), Vendsecond7(:,1), Vendsecond7(:,2), 'LineWidth', 2 );
title('Napon cvora 7 [kV]' , 'FontSize', 16);
xlabel('Velicina kondenzatora [MVAr]', 'Fontsize', 12);
legend('C u cvoru 3', 'C u cvoru 5', 'C u cvoru 7', 'location', 'northwest');

print(my_graph, 'Vendsecond2.jpg');

% !!! Izbor minimuma fali u skriptu, jos nisam realizovao u ovom skriptu
