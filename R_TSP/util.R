## functions
calc_total_distance = function(path, distmap) {
  dist = vector(mode = 'numeric' , city_number); 
  total = 0;
  for(i in c(1:city_number-1)){
    dist[i] = distmap[path[i] , path[i+1]] ; 
  }
  dist[city_number] = distmap[path[city_number] , path[1]] ; 
  return(sum(dist))
}
generate_distmap = function(coordinates){
  point_number = dim(coordinates)[1];
  distmap = matrix(0 , nrow =  point_number , ncol = point_number);
  for(i in c(1:point_number))
    for(j in c(i:point_number))
    {
      distmap[i,j] = distmap[j,i] = calc_two_city_distance(i,j , coordinates);
    }
  return(distmap)
  
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
    if(runif(1, min = 0 , max = 1 ) < exp(-(new_len- opt_len)/t) ) {
      return(TRUE) ;
    }
    
  }
  return(FALSE);
}
