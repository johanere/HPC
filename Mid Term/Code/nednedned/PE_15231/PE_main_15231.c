#include "functions.h"
#include <time.h>

int main(int argc, char **argv)
{

if (argc <= 4)
{
  printf("Bad Usage: - provide as CL args: input file, dampening, threshold, and number of top pages to be displayed \n");
  exit(1);
}
const char *filename = argv[1];
float d=atof(argv[2]);// //dampning
float eps=atof(argv[3]);//threshold
int numb_pages=atoi(argv[4]); //number of top pages to be displayed.

//CRS arrays, array of index of dangling pages (dangling), and pagerank score vector (pagerank)
int *col, *row_ptr, *dangling; //len(col)=Nodes+1, len(row_ptr)=tot_link,len(dangling)=number_dangling, len(val)=tot_link
float *val,*PageRank;
dangling=NULL;

//arrays to hold index of top ranking pages and their values
int *index_topranked;
float *toprank;
int Nodes, tot_link, number_dangling; //number of Nodes, number of links between sites, number of dangling pages

double start = omp_get_wtime(); // start clock


printf("Opening file %s \n",filename);
read_to_crs(filename,&col,&row_ptr,&val,&dangling,&Nodes,&tot_link,&number_dangling); //reading data from file into CRS arrays
printf("#Nodes= %d, #Links= %d, #Dangling pages=%d \n",Nodes,tot_link,number_dangling);
PageRank_iterations(col,row_ptr,val,dangling,&Nodes,&tot_link,&number_dangling,&PageRank,d,eps); //finding page ranks by itartions
top_n_webpages(numb_pages,&Nodes,PageRank,&index_topranked,&toprank); //sorting out top ranked web pages


printf("Top %d ranked pages after PageRank iterations with dampning d=%f to a convergence threshold of %f: \n", numb_pages,d,eps);
for (int i=0;i<numb_pages;i++)
{
printf("Page number %8d has a PageRank of %f\n",index_topranked[i],toprank[i] );
}

double end = omp_get_wtime(); //stop clock
double tot = end - start;
printf("Total run time: %f seconds\n",tot ); //print total run time

// de-alloc
free(col);
free(row_ptr);
free(val);
free(dangling);
free(index_topranked);
free(toprank);

return 0;
}
