#include "functions.h"
#include <time.h>

int main(int argc, char **argv)
{
//const char *filename=argv[1];
const char *filename = "web-NotreDame.txt"; //"WGtest.txt"; //"web-NotreDame.txt"; //
float d=0.85; //dampning
float eps=0.00001; //treshold
int n=10; //number of top pages to be displayed.

//CRS arrays, array of index of dangling pages (dangling), and pagerank score vector (pagerank)
int *col, *row_ptr, *dangling; //len(col)=Nodes+1, len(row_ptr)=tot_link,len(dangling)=number_dangling, len(val)=tot_link
float *val,*PageRank;
dangling=NULL;

clock_t begin = clock();

int Nodes, tot_link, number_dangling; //number of Nodes, number of links between sites, number of dangling pages

printf("Opening file %s\n",filename);
read_to_crs(filename,&col,&row_ptr,&val,&dangling,&Nodes,&tot_link,&number_dangling);


printf("Nodes= %d, links= %d, dangling pages=%d \n",Nodes,tot_link,number_dangling);
PageRank_iterations(col,row_ptr,val,dangling,&Nodes,&tot_link,&number_dangling,&PageRank,d,eps);

for (int i=0;i<Nodes;i++)
{
; //printf("%f\n",PageRank[i] );
}

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("Time:%f\n",time_spent );

/*
printArray(row_ptr,Nodes+1);
printArray(col,tot_link);
for (int i=0;i<tot_link;i++)
{
  printf("%f ",val[i] );
}


for(int i=0;i<number_dangling;i++)
{
  printf("%d\n", dangling[i] );
}
*/
free(col);
free(row_ptr);
free(val);
free(dangling);

return 0;
}


/*float *rows=(float*)calloc((Nodes),sizeof(int)); //rows

for(int j=0;j<tot_link;j++)
{
  rows[col[j]]=rows[col[j]]+val[j];
}

int newdangles=0;
for(int j=0;j<Nodes;j++)
{
  if (rows[j] != 1.0){
    newdangles+=1;
  printf("index= %d sums to %f \n",j,rows[j]);
}}
int *nDangles=(int*)calloc((newdangles),sizeof(nDangles)); //rows
int drr=0;
for(int j=0;j<Nodes;j++)
{
  if (rows[j] != 1.0){
    nDangles[drr]=j;
    printf("%d node: %d \n",drr,nDangles[drr] );
    drr=drr+1;
}}*/
