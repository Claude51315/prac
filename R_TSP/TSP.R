# remove current context
rm(list = ls())
graphics.off()

source("./util.R")
# configuration parameter
city_number = 20 
city_size = 1000 
T_min = 1 
T_init = 100
r = 0.98

# entry point 
generate_map(city_number , city_size)
cities_coordinate = read.csv("map.csv")

path <-1:city_number
len = calc_total_distance(path, cities_coordinate);

opt_len = len;
opt_path = path;

# SA
temperature = T_init ;
nIter = city_number *10; 
while(temperature > T_min){
  
  for(i in c(1:nIter)){
    new_path = generate_new_path(path);
    new_len = calc_total_distance(new_path,cities_coordinate);
    if(accept(len , new_len, temperature)){
      path = new_path;
      len =new_len; 
    }
    # uodate current optimal
    if(len < opt_len)
    {
      opt_path = path;
      opt_len = len; 
      print(paste("optimal = ", opt_len , sep = " "));
    }
  }
  temperature = temperature * r ;
  print(paste("temperature = " , temperature , sep = " "));
}
# brutal force
# opt_len = calc_total_distance(path, cities_coordinate)
# N = 1000 
# for(t in c(1:N)){
#   path = sample(path);
#   tmp_total = calc_total_distance(path, cities_coordinate);
#   if(tmp_total < opt_len)
#     opt_len = tmp_total; 
# }

# plot result 
X11()
plot(cities_coordinate[,1] , cities_coordinate[,2], col = 'red' , main = paste("total distance =", opt_len, sep = " "))
lines(cities_coordinate[opt_path, 1], cities_coordinate[opt_path,2] , col = 'blue')
## connecting first and last cities 
lines(cities_coordinate[opt_path[c(1,city_number)] ,1 ],cities_coordinate[opt_path[c(1,city_number)] ,2 ], col = 'blue')


