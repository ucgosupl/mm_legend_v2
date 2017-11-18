import numpy as np
import matplotlib.pyplot as plt


def rise_time_and_time_const(time_vect, data, mean_samples, rise_time_samples, time_const_samples):
    steady = np.mean(data[mean_samples[0]:mean_samples[1]])
    coef = np.polyfit(time_vect[0:time_const_samples], data[0:time_const_samples], 1)
    rise_time = [x * coef[0] + coef[1] for x in time_vect[0:rise_time_samples]]
    time_const = (steady - coef[1]) / coef[0]

    return steady, rise_time, time_const


def draw_plots(file, mean_samples, rise_time_samples, time_const_samples):
    print("\nDrawing plot from data file: {}".format(file))

    left, right = np.loadtxt(file, dtype=int, unpack=True)

    step = 0.01
    time = np.linspace(step, 1, 1 / step)

    left_steady, left_rise_time, left_t = \
        rise_time_and_time_const(time, left, mean_samples, rise_time_samples, time_const_samples)
    right_steady, right_rise_time, right_t = \
        rise_time_and_time_const(time, right, mean_samples, rise_time_samples, time_const_samples)

    print("Steady state velocity for motor left is {:.6}.".format(left_steady))
    print("Steady state velocity for motor right is {:.6}.".format(right_steady))

    print("Time constant for left motor velocity is {:.6}.".format(left_t))
    print("Time constant for right motor velocity is {:.6}.".format(right_t))

    plt.figure()
    plt.plot(time, left, 'r')
    plt.plot(time, right, 'b')
    plt.plot(time, [left_steady] * len(time), 'r')
    plt.plot(time, [right_steady] * len(time), 'b')
    plt.plot(time[0:rise_time_samples], left_rise_time, 'r')
    plt.plot(time[0:rise_time_samples], right_rise_time, 'b')
    plt.plot(left_t, left_steady, 'ro')
    plt.plot(right_t, right_steady, 'bo')

motor_20 = "../data/motor_20.txt"
motor_40 = "../data/motor_40.txt"
motor_60 = "../data/motor_60.txt"

draw_plots(motor_20, [70, 90], 30, 10)
draw_plots(motor_40, [70, 90], 30, 10)
draw_plots(motor_60, [70, 90], 20, 10)

plt.show()
