file = '../data/motor_ang_ident_200_15.txt';

motor_data = importdata(file);

left = motor_data(:,1);
right = motor_data(:,2);
angular = motor_data(:,3) / 100;

t = 1:max(size(left));
t = t * 0.01;

figure;
plot(t, left, t, right, 'r');
figure;
plot(t, left - right);
figure;
plot(t, angular);

xlabel('time [s]')
ylabel('angular velocity [dps]')