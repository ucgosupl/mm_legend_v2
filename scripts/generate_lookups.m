fdata = importdata('../data/wall_sensor_all.txt', '\t');
data = fdata.data;
dist = data(:,1);
lfront = data(:,2);
rfront = data(:,3);
ldiag = data(:,4);
rdiag = data(:,5);
lside = data(:,6);
rside = data(:,7);

fit_lfront = wall_sensor_ident(dist, lfront);
fit_rfront = wall_sensor_ident(dist, rfront);
fit_ldiag = wall_sensor_ident(dist, ldiag);
fit_rdiag = wall_sensor_ident(dist, rdiag);
fit_lside = wall_sensor_ident(dist, lside);
fit_rside = wall_sensor_ident(dist, rside);

file = fopen('adc2dist.c','w');

write_to_file(file, 'lfront', fit_lfront);
write_to_file(file, 'rfront', fit_rfront);
write_to_file(file, 'ldiag', fit_ldiag);
write_to_file(file, 'rdiag', fit_rdiag);
write_to_file(file, 'lside', fit_lside);
write_to_file(file, 'rside', fit_rside);

fclose(file);