#include "functions.h"

int main(int argc, char **argv)
{
int *row_ptr;
//const char *filename=argv[1];
const char *filename = "WGtest.txt";
printf("Opening file %s\n",filename);
read_to_crs(filename, row_ptr);
PageRank_iterations();
free(row_ptr);
return 0;
}
