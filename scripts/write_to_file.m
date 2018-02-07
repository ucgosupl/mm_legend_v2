wall_sensor_ident

% Equation: ADC = exp (a / (l + b)) + c
% Parameter values obtained from measurement data.
a = fit(1);
b = fit(2);
c = fit(3);

adc = 0:4095;
distance = a ./ log(adc - c) - b;

file = fopen('adc2dist.c','w');
fprintf(file, 'static const int32_t adc2dist_lookup_table[4096] = {\n\t');

for i = 1:max(size(distance))
    
    if i < c + 50
        fprintf(file,'WALL_NOT_FOUND, ');
    elseif round(distance(i)) > 180
        fprintf(file,'WALL_NOT_FOUND, ');
    elseif round(distance(i)) < 30
        fprintf(file,'WALL_TOO_CLOSE, ');
    else
        fprintf(file,'%d, ',round(distance(i)));
    end

    if i == max(size(distance))
        fprintf(file,'\n};\n');
    elseif (mod(i,8) == 0)
        fprintf(file,'\n\t');
    end
end

fclose(file);
