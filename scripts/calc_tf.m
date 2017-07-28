function [left_tf, right_tf] = calc_tf(input, left_steady, right_steady, left_ts, right_ts)
    left_k = left_steady / input;
    right_k = right_steady / input;

    left_tf = tf(left_k, [left_ts, 1]);
    right_tf = tf(right_k, [right_ts, 1]);
end