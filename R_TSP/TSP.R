# remove current context
rm(list = ls())
graphics.off()

source("./util.R")
# configuration parameter

city_size = 1000 
T_min = 1 
T_init = 100
r = 0.98

# entry point 
#generate_map(city_number , city_size)
cities_coordinate = read.csv("nctu.csv" , header = FALSE)
## roughly transforms transform longitude/latitude 
cities_coordinate = cities_coordinate * 111000

distmap = generate_distmap(cities_coordinate);

city_number = dim(cities_coordinate)[1]

path <-1:city_number
len = calc_total_distance(path, distmap);

opt_len = len;
opt_path = path;

# SA
temperature = T_init ;
nIter = city_number *10; 
loop_count = 1 ; 
temperature_stat = vector(mode = "numeric" , length = ceiling ((log(T_min) - log(T_init)) / log(r)));

while(temperature > T_min){
  
  for(i in c(1:nIter)){
    new_path = generate_new_path(path);
    new_len = calc_total_distance(new_path,distmap);
    if(accept(len , new_len, temperature)){
      path = new_path;
      len =new_len; 
    }
    # uodate current optimal
    if(len < opt_len)
    {
      opt_path = path;
      opt_len = len; 
    }
  }
  temperature = temperature * r ;
  print(paste("temperature = " , temperature , ", optimal = ", opt_len , sep = " "));
  temperature_stat[loop_count] = temperature ; 
  loop_count = loop_count + 1 ; 
}

# plot result 
cities_coordinate = cities_coordinate / 111000; 
X11()
par(mfrow = c(1 , 2));
plot(cities_coordinate[,2] , cities_coordinate[,1], col = 'red' , main = paste("total distance =", opt_len, sep = " ") , 
     xlab = "longitude" , ylab = "latitude")
lines(cities_coordinate[opt_path, 2], cities_coordinate[opt_path,1] , col = 'blue')
## connecting first and last cities 
lines(cities_coordinate[opt_path[c(1,city_number)] ,2],cities_coordinate[opt_path[c(1,city_number)] ,1 ], col = 'blue')

plot(temperature_stat , main = "temperature" , type = 'l')
