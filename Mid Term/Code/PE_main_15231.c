#include "functions.h"

int main(int argc, char **argv)
{
//const char *filename=argv[1];
int *row_ptr;
const char *filename = "WGtest.txt";
printf("Opening file %s\n",filename);
read_to_crs(filename);
PageRank_iterations();
return 0;
}
