function print_plots(time, tf, data20, data40, data60)
    l20_step20 = calc_step(time, tf, 20);
    l20_step40 = calc_step(time, tf, 40);
    l20_step60 = calc_step(time, tf, 60);

    figure
    hold on
    plot(time, data20, time, l20_step20, 'r')
    plot(time, data40, time, l20_step40, 'r')
    plot(time, data60, time, l20_step60, 'r')
end