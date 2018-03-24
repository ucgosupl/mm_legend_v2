function write_to_file(file, name, fit)

% Equation: ADC = exp (a / (l + b)) + c
% Parameter values obtained from measurement data.
a = fit(1);
b = fit(2);
c = fit(3);

adc = 0:4095;
distance = a ./ log(adc - c) - b;

fprintf(file, 'static const uint8_t adc2dist_%s_lookup[4096] = {\n\t', name);

for i = 1:max(size(distance))
    
    % Distance below zero
    if i < c + 50
        fprintf(file,'WALL_NOT_FOUND, ');
    % Wall too far
    elseif round(distance(i)) > 150
        fprintf(file,'WALL_NOT_FOUND, ');
    % Wall too close
    elseif round(distance(i)) < 30
        fprintf(file,'WALL_TOO_CLOSE, ');
    else
        fprintf(file,'%d, ',round(distance(i)));
    end

    if i == max(size(distance))
        fprintf(file,'\n};\n\n');
    elseif (mod(i,8) == 0)
        fprintf(file,'\n\t');
    end
end

end
