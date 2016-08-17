rm(list = ls())
graphics.off()
## configuration parameter
city_number = 20 
city_size = 1000 

T_min = 1 
T_init = 1000
r = 0.98

## functions
calc_total_distance = function(path, cities_coordinate) {
  dist = vector(mode = 'numeric' , city_size); 
  total = 0;
  for(i in c(1:city_number-1)){
    dist[i] = calc_two_city_distance(path[i] , path[i+1] ,cities_coordinate);
  }
    dist[city_number] =  calc_two_city_distance( path[city_number],path[1] , cities_coordinate); 
  return(sum(dist))
}


calc_two_city_distance = function(city_a , city_b ,cities_coordinate ){
  dist = 0 ; 
  dist = sqrt ( (cities_coordinate[city_a,1] - cities_coordinate[city_b,1])^2 + 
                  (cities_coordinate[city_a,2] - cities_coordinate[city_b,2])^2 );
  return(dist)
}
generate_map = function(city_number,city_size){
  cities_coordinate = matrix( data = 0,ncol = 2 , nrow = city_number )
  cities_coordinate[,1] = floor(runif(city_number , min = 0 , max = city_size));
  cities_coordinate[,2] = floor(runif(city_number , min = 0 , max = city_size));
  write.csv(cities_coordinate, file = "map.csv");
}

# swap the n1-th and n2-th elements in arrray N
swap = function(N, n1, n2){
  tmp = N[n1];
  N[n1] = N[n2];
  N[n2] = tmp ; 
  return(N)
}
# reverse the order of array N from n1-th and n2-th elements
reverse = function(N, n1, n2){
  if(n1 > n2){
    tmp = n1;
    n2 = n1;
    n1 = tmp; 
  }
  N[n1:n2] = N[n2:n1]; 
  return(N)  
}
# left shift elements from n1-th to n2-th
rotate = function(N, n1, n2){
  if(n1 > n2){
    tmp = n1;
    n2 = n1;
    n1 = tmp; 
  }
  tmp = N[n1:n2];
  N[(n1+1):n2] = tmp[1:(length(tmp)-1)];
  N[n1] =tmp[length(tmp)]; 
  return(N)
}

generate_new_path = function(path){
  select = floor(runif(1, min = 0, max =3));
  n1 = floor(runif(1, min = 1 , max = city_number +1));
  n2 = floor(runif(1, min = 1 , max = city_number +1));
  if(n1 == n2)
    return(path)
  if(n1> n2){
    tmp = n1 ; 
    n1 = n2;
    n2 = tmp; 
  }
  if(select == 0){
    new_path = swap(path,n1,n2);
    
  }else if(select == 1){
    new_path = reverse(path,n1,n2);
  }else{
    new_path = rotate(path,n1, n2);
  }
  return(new_path)
}

accept = function(opt_len, new_len ,t){
  if(new_len<opt_len){
    return(TRUE);
  }else{
    if(runif(1, min = 0 , max = 1 ) < exp((new_len- opt_len)/t) ) {
      return(TRUE) ;
    }
   
  }
  return(FALSE);
}

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
      print(opt_len)
    }
  }
  temperature = temperature * r ;
  
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



