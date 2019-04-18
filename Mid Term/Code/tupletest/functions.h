#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

void swap(int *a, int *b);
void quicksort(int arr[], int l, int r);
void printArray(int arr[], int size);
void read_to_crs(const char *filename,int **pp1,int **pp2, float **pp3, int **pp4, int *Nodes,int *tot_link, int *number_dangling);
void PageRank_iterations(int *col,int *row_ptr, float *val, int *dangling, int *Nodes,int *tot_link, int *number_dangling,float **pp1,float d,float eps);
void top_n_webpages(int n);
#endif
