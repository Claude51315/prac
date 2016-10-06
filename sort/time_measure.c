#include "time_measure.h"

double diff_in_second(struct timespec start, struct timespec end)
{
    return (double) (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC ;
}
