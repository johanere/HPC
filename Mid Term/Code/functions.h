#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(int *a, int *b);
void quicksort(int arr[], int l, int r);
void printArray(int arr[], int size);
void read_to_crs(const char *filename);
void PageRank_iterations();
#endif
