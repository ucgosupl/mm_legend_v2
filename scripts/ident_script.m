motor20 = importdata('../data/motor_20.txt');
l20 = motor20(:,1);
r20 = motor20(:,2);

motor40 = importdata('../data/motor_40.txt');
l40 = motor40(:,1);
r40 = motor40(:,2);

motor60 = importdata('../data/motor_60.txt');
l60 = motor60(:,1);
r60 = motor60(:,2);

time = 0.01:0.01:1;

l20_steady = 24.75;
r20_steady = 22.75;
l20_ts = 0.3496;
r20_ts = 0.3390;

l40_steady = 58.1;
r40_steady = 56.0;
l40_ts = 0.2739;
r40_ts = 0.2150;

l60_steady = 90.1;
r60_steady = 83.7;
l60_ts = 0.1763;
r60_ts = 0.1506;

[l20_tf, r20_tf] = calc_tf(20, l20_steady, r20_steady, l20_ts, r20_ts);

print_plots(time, l20_tf, l20, l40, l60);
title('Model for left motor - 20% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')

print_plots(time, r20_tf, -r20, -r40, -r60);
title('Model for right motor - 20% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')

[l40_tf, r40_tf] = calc_tf(40, l40_steady, r40_steady, l40_ts, r40_ts);

print_plots(time, l40_tf, l20, l40, l60);
title('Model for left motor - 40% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')

print_plots(time, r40_tf, -r20, -r40, -r60);
title('Model for right motor - 40% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')

[l60_tf, r60_tf] = calc_tf(60, l60_steady, r60_steady, l60_ts, r60_ts);

print_plots(time, l60_tf, l20, l40, l60);
title('Model for left motor - 60% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')

print_plots(time, r60_tf, -r20, -r40, -r60);
title('Model for right motor - 60% power')
xlabel('time [s]')
ylabel('speed [ticks]')
legend('data', 'model')