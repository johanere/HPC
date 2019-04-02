#include "functions.h"

int main(int argc, char **argv)
{
//printf("%s\n",argv[1]);
//const char *filename=argv[1];
const char *filename = "WGtest.txt";
printf("Opening file %s\n",filename);
read_to_crs(filename);
PageRank_iterations();
return 0;
}
