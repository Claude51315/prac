#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H
#include<stdio.h>
#include<stdlib.h>
void merge_sort(int *data, int n);
void merge(int *result, int *L, int l_len, int *R, int r_len);
void quick_sort(int *data, int start, int end);
void bubble_sort(int *data, int n);
void print(int *data, int n, char* filename);
#endif
