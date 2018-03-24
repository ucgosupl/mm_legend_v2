fdata = importdata('../data/wall_sensor_all.txt', '\t');
data = fdata.data;
dist = data(:,1);
front_l = data(:,2);
front_r = data(:,3);
diag_l = data(:,4);
diag_r = data(:,5);
side_l = data(:,6);
side_r = data(:,7);

fit_front_l = wall_sensor_ident(dist, front_l);
fit_front_r = wall_sensor_ident(dist, front_r);
fit_diag_l = wall_sensor_ident(dist, diag_l);
fit_diag_r = wall_sensor_ident(dist, diag_r);
fit_side_l = wall_sensor_ident(dist, side_l);
fit_side_r = wall_sensor_ident(dist, side_r);

file = fopen('adc2dist.c','w');

write_to_file(file, 'front_l', fit_front_l);
write_to_file(file, 'front_r', fit_front_r);
write_to_file(file, 'diag_l', fit_diag_l);
write_to_file(file, 'diag_r', fit_diag_r);
write_to_file(file, 'side_l', fit_side_l);
write_to_file(file, 'side_r', fit_side_r);

fclose(file);