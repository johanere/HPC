#include "functions.h"

int main(int argc, char **argv)
{
//CRS arrays, array of index of dangling pages (dangling), and pagerank score vector (pagerank)
int *col, *row_ptr, *dangling; //len(col)=Nodes+1, len(row_ptr)=tot_link,len(dangling)=number_dangling, len(val)=tot_link
double *val,*pagerank;

int Nodes, tot_link, number_dangling; //number of Nodes, number of links between sites, number of dangling pages


//const char *filename=argv[1];
dangling=NULL;

//
float d=0.1; //dampning
float eps= 0.001; //treshold


const char *filename = "WGtest.txt";//"testset.txt";
printf("Opening file %s\n",filename);
read_to_crs(filename,&col,&row_ptr,&val,&dangling,&Nodes,&tot_link,&number_dangling);

float *rows=(float*)calloc((Nodes),sizeof(int)); //rows

for(int j=0;j<tot_link;j++)
{
  rows[col[j]]=rows[col[j]]+val[j];
}

for(int j=0;j<Nodes;j++)
{
  if (rows[j] != 1.0){
  printf("index= %d sums to %f \n",j,rows[j]);
}}

//for(int i=0;i<tot_link;i++)
//{
//  printf("%f ",val[i] );

//}
printf("\n");
/*
for (int i=0;i<number_dangling;i++)
{
  printf("dangler = %d \n",dangling[i] );
}
*/
//printf("Nodes= %d, links= %d\n",Nodes,tot_link );
PageRank_iterations(col,row_ptr,val,dangling,&Nodes,&tot_link,&number_dangling,&pagerank,d,eps);



/*
printArray(row_ptr,Nodes+1);
printArray(col,tot_link);
for (int i=0;i<tot_link;i++)
{
  printf("%f ",val[i] );
}
*/
free(col);
free(row_ptr);
free(val);
free(dangling);

return 0;
}
