#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void swap(int *a, int *b);
void quicksort(int arr[], int l, int r);
void printArray(int arr[], int size);
void read_to_crs(const char *filename,int **pp1,int **pp2, double **pp3, int **pp4, int *Nodes,int *tot_link, int *number_dangling);
void PageRank_iterations(int *col,int *row_ptr, double *val, int *dangling, int *Nodes,int *tot_link, int *number_dangling,double **pp1,float d,float eps);
#endif
