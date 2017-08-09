function step_y = calc_step(time, tf, input)

    step_y = step(tf, time);
    step_y = step_y * input;
end