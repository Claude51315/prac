rm(list = ls())
graphics.off()

data = read.csv("execution_time.txt", header = FALSE);
BUBBLE_ARRAY = data[data[1] == 'BUBBLE_ARRAY',]
QUICK_LIST = data[data[1] == 'QUICK_LIST',]
QUICK_ARRAY = data[data[1] == 'QUICK_ARRAY',]
MERGE_LIST = data[data[1] == 'MERGE_LIST',]
MERGE_ARRAY =  data[data[1] == 'MERGE_ARRAY',]

# plot orignal data
png(filename = "orignal.png" , width = 1280 , height = 1280*0.75)
plot(BUBBLE_ARRAY[,2], BUBBLE_ARRAY[,3], type = 'l' , col = "red",
     xlab = "N", ylab = "execution time(sec)" , main = "performance comparison (original)")
lines(QUICK_LIST[,2], QUICK_LIST[,3], type = 'l' , col = "blue")
lines(QUICK_ARRAY[,2], QUICK_ARRAY[,3], type = 'l' , col = "black")
lines(MERGE_LIST[,2], MERGE_LIST[,3], type = 'l' , col = "yellow")
lines(MERGE_ARRAY[,2], MERGE_ARRAY[,3], type = 'l' , col = "green")

legend('topleft', # places a legend at the appropriate place 
      c("BUBBLE_ARRAY", "QUICK_LIST", "QUICK_ARRAY","MERGE_LIST","MERGE_ARRAY"), # puts text in the legend
      lty=c(1,1,1,1,1), # gives the legend appropriate symbols (lines)
      lwd=c(2.5,2.5,2.5,2.5,2.5),col=c("red","blue", "black","yellow","green"))
dev.off()
