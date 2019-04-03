#define getName(var)  #var
#include "functions.h"

void read_to_crs(const char *filename,int **pp1, int**pp2, float **pp3, int **pp4, int *Nodes,int *tot_link,int *number_dangling)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int n1,n2, Edges, min_index, max_index,nodes_in_row,j;
    char p, buffer[100];;

    int *inbound, *outbound, *selflink, *col, *row_ptr, *dangling;
    float *val;

    *tot_link=0;
    *number_dangling=0;
    //opening file
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //skip first two lines
    fgets(buffer, 100, fp);
    fgets(buffer, 100, fp);

    // read number of Nodes (and Edges) and skip line
    fscanf(fp,"%*s %*s %d  %*s %d ",Nodes,&Edges);
    fgets(buffer, 100, fp);

    // allocate mem for arrays to hold data from initial file iteration
    inbound=(int*)calloc(*Nodes,sizeof(int));
    outbound=(int*)calloc(*Nodes,sizeof(int));
    selflink=(int*)calloc(*Nodes,sizeof(int));

    //initial file read
    while (fscanf(fp,"%d %d",&n1,&n2)==2)
    {
      if (n1==n2) {selflink[n1]+=1; } //check for and count self linking
      else {inbound[n1]+=1; outbound[n2]+=1; *tot_link+=1;} //count number of links to and from each node
    }


    // allocate mem for CRS arrays
    row_ptr=(int*)malloc((*Nodes+1)*sizeof(int)); //rows
    val=(float*)calloc(*tot_link,sizeof(float)); //values
    col=(int*)calloc(*tot_link,sizeof(int)); //columns

    //set col values to control value
    for (int i=0;i<*tot_link;i++)
    {
      col[i]=-1;
    }

    //calculate row pointer
    row_ptr[0]=0;
    for (int i=0;i<*Nodes;i++)
    {
      row_ptr[i+1]=row_ptr[i]+inbound[i];
    }

    //rewind file reading and skip first three lines
    rewind(fp);
    for (int i=0;i<4;i++)
    {
      fgets(buffer, 100, fp);
    }



    //re-read file and assign values to colmn array col - not sorted!
    while (fscanf(fp,"%d %d",&n1,&n2)==2)
    {
      if (n1==n2) {;} //no asignment to col if selflink
      else
      {
        j=0;
        min_index=row_ptr[n1]; //find index pertainting to the node beeing linked to
        while(col[min_index+j] != -1) //find free nearest non assigned element in col vec using control value
        {
          j+=1;}
        if(j>inbound[n1]){printf("Warning: Faulty behaviour in column count! \n");} // give watning if element is assigned out of node bounds
        col[min_index+j]=n2;
      }
    }

    //int fclose(FILE *fp);

    //sort col vec
    for(int i=0;i<*Nodes;i++)
    {
      if(inbound[i]>1) //only sort if more than one inbound link
      {
        min_index=row_ptr[i]; //find lower bound element beloning to node i
        max_index=min_index+inbound[i]-1; //find max bound element belonging to node i
        quicksort(col,min_index,max_index); //sort elements belongning to node i using quicksort
      }
    }

    for (int i=0;i<*tot_link;i++)
    {
      if (outbound[col[i]] != 0)
      {
      val[i]=1.0/(outbound[col[i]]); //set value[i] to 1/total number of outgoing links from node
      }
    }
    printf(" \n" );


    //check for dangling pages
    for (int i=0;i<*Nodes;i++)
    {
        if (outbound[i]==0)
      {
        *number_dangling+=1;
      }
    }


    // if there are dangling wepages, initiate and fill array dangling with index of dangling webpages
      dangling=(int*)calloc(*number_dangling,sizeof(int));
      if (*number_dangling>0)
      {
      int d_counter=0;
      for (int i=0;i<*Nodes;i++)
      {
        if (outbound[i]==0)
        {
          dangling[d_counter]=i;
          d_counter++;
        }
      }
    }

    *pp1=col;
    *pp2=row_ptr;
    *pp3=val;
    *pp4=dangling;
    // free allocated mem
    free(inbound);
    free(outbound);
    free(selflink);


}//end of read_to_crs function


void PageRank_iterations(int *col,int *row_ptr, float *val, int *dangling, int *Nodes,int *tot_link, int *number_dangling,float **pp1,float d,float eps)
{
float *pagerank,*newrank;
pagerank=(float*)calloc(*Nodes,sizeof(float)); //array holding page rank of pages
newrank=(float*)calloc(*Nodes,sizeof(float)); //array holding new page rank of pages

float w=0;
float factor;

float n=(float)*Nodes; //normalization constant

if (*number_dangling==0) //no dangling pages meand w is constantly 0, thus the factor used in calc. page rank is simplified
{
  factor=(1-d)/n;
}

for (int i=0;i<*Nodes;i++) //setting pagerank to initial guess using normalization constant n
{
pagerank[i]=1/n;
}


int iterations=0; //iteraitons counter
float maxerr=1.0; //initial error value IOT enter loop
while(maxerr>eps)
{
  iterations+=1;
  maxerr=0; // reset error

  if (*number_dangling>0) //calculate new w in case of danlging threads
  {
    w=0;
    for (int i=0;i<*number_dangling;i++)
    {
      w += pagerank[dangling[i]];
    }
    factor=(1-d+d*w)/n;
  }
#pragma omp parallel
{
  for(int i=0; i<*Nodes;i++) //calculate new pageranks
  {
    for(int j=row_ptr[i];j<row_ptr[i+1];j++)
    {
      newrank[i]=newrank[i]+val[j]*(pagerank[col[j]]);
    }
    newrank[i]=d*newrank[i]+factor;
    if (fabs(newrank[i]-pagerank[i])>maxerr) //test if delta between new and old pagerank of page i is the largest delta
    {
      maxerr=fabs(newrank[i]-pagerank[i]); //update maximum error
    }
  }
  for(int i=0; i<*Nodes;i++)
  {
  pagerank[i]=newrank[i]; //set pagerank to new page rank
  newrank[i]=0; //reset newrank array for next iteration
  }
}
}
//printf("Iterations = %d\n",iterations );

//de-alloc
*pp1=pagerank;
free(newrank);
}//end of PageRank_iterations function


// Function to swap two pointers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
} //end of swap function

//function to print array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
} //end of PrintArray function

//quicksort algo on array from element l to r
void quicksort(int arr[], int l, int r)
{
    // skip Base case
    if (l >= r)
    {
        return;
    }
    int pivot = arr[r]; //choose initial pivot
    int cnt = l; //split index between larger than and smaller than pivot

    for (int i = l; i <= r; i++) //iterate array
    {
        if (arr[i] <= pivot)
        {
            swap(&arr[cnt], &arr[i]); //swap pointers if smaller than pivot
            cnt++;
        }
    }
    quicksort(arr, l, cnt-2); // sort the left side of pivot
    quicksort(arr, cnt, r);   // sort the right side of pivot
}//end of quicksort function
