scenario4;

pointer = Ploss;
contour(Qc, Qc, pointer, 80, 'ShowText', 'on');
%surf(Qc, Qc, pointer);
title('Konturni prikaz optimalnog izbora kondenzatora', 'FontSize', 18);
xlabel('C cvora 4 [MVAr]', 'FontSize', 12);
ylabel('C cvora 5 [MVAr]', 'FontSize', 12);

[minval, minind] = min(min(pointer))
Ppoc = pointer(1,1)