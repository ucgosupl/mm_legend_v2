data = importdata('../data/wall_sensor_measurements.txt', '\t', 2);
l = data.data(:,1);
v = data.data(:,5);

F = @(a, data) a(3) + exp(a(1)./(data + a(2)));
x0 = [1954 222 220];

fit = lsqcurvefit(F, x0, l(2:end-1), v(2:end-1))

plot(l, F(fit, l), l, v, 'ro')