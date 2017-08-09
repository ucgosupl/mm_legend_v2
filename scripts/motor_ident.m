function [left_y, right_y] = motor_ident(input, left_steady, right_steady, left_ts, right_ts)
    time = 0.01:0.01:1;

    left_k = left_steady / input;
    right_k = right_steady / input;

    left_tf = tf(left_k, [left_ts, 1]);
    right_tf = tf(right_k, [right_ts, 1]);

    left_y = step(left_tf, time);
    left_y = left_y * input;

    right_y = step(right_tf, time);
    right_y = right_y * input;
end

