%data = importdata('../data/wall_sensor_measurements.txt', '\t', 2);
function fit = wall_sensor_ident(len, val)

F = @(a, data) a(3) + exp(a(1)./(data + a(2)));
x0 = [1954 222 220];

fit = lsqcurvefit(F, x0, len(1:end-1), val(1:end-1));

figure
plot(len, F(fit, len), len, val, 'ro')

end