import numpy as np
import matplotlib.pyplot as plt


step = 0.01
time = np.linspace(step, 2, 2 / step)

mean_samples = [50, 150]
rise_time_samples = 25
time_const_samples = 10


def process_file(file, is_angular):
    left, right, angle = np.loadtxt(file, dtype=int, unpack=True)

    if is_angular:
        data = right - left
        name = "angular velocity"
    else:
        data = right + left
        name = "linear velocity"

    steady, rise_time, ts = \
        rise_time_and_time_const(time, data, mean_samples, rise_time_samples, time_const_samples)
    print_steady_and_ts(steady, ts, name)
    do_plot(data, time, steady, rise_time, ts, rise_time_samples)


def rise_time_and_time_const(time_vect, data, mean_samples, rise_time_samples, time_const_samples):
    steady = np.mean(data[mean_samples[0]:mean_samples[1]])
    coef = np.polyfit(time_vect[0:time_const_samples], data[0:time_const_samples], 1)
    rise_time = [x * coef[0] + coef[1] for x in time_vect[0:rise_time_samples]]
    time_const = (steady - coef[1]) / coef[0]

    return steady, rise_time, time_const


def do_plot(data, time, steady, rise_time, ts, rise_time_samples):
    plt.figure()
    plt.plot(time, data, 'r')
    plt.plot(time, [steady] * len(time), 'r')
    plt.plot(time[0:rise_time_samples], rise_time, 'r')
    plt.plot(ts, steady, 'ro')
    plt.show()


def print_steady_and_ts(steady, ts, name):
    print("Steady state for {} is {:.6}.".format(name, steady))
    print("Time constant for {} is {:.6}.".format(name, ts))


motor_ang = "../data/motor_ang_ident_200_0.txt"
motor_lin = "../data/motor_ident_200_0.txt"

process_file(motor_ang, True)
process_file(motor_lin, False)
