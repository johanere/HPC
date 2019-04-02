#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define getName(var)  #var

void swap(int *a, int *b);
void quicksort(int arr[], int l, int r);
void printArray(int arr[], int size);

int main()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int n1,n2, Nodes,Edges, tot_link=0;;
    char p, buffer[100];;

    int *inbound, *outbound, *selflink, *row_ptr, *col;
    float *val;

    //open file
    fp = fopen("WGtest.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //skip first two lines
    fgets(buffer, 100, fp);
    fgets(buffer, 100, fp);

    // read number of Nodes and Edges from line three
    fscanf(fp,"%*s %*s %d  %*s %d ",&Nodes,&Edges);

    // allocate heap mem for arrays to hold counting data
    inbound=(int*)calloc(Nodes,sizeof(int));
    outbound=(int*)calloc(Nodes,sizeof(int));
    selflink=(int*)calloc(Nodes,sizeof(int));

    //initial file read
    while (fscanf(fp,"%d %d",&n1,&n2)==2)
    {
      if (n1==n2) {printf("blaG\n"); selflink[n1]+=1; } //check for and count self linking
      else {inbound[n1]+=1; outbound[n2]+=1; tot_link+=1;} //count number of links to and from each node
    }


    // allocate heap mem for matrix vectors
    row_ptr=(int*)malloc(Nodes*sizeof(int));
    val=(float*)calloc(tot_link,sizeof(int));
    col=(int*)calloc(tot_link,sizeof(int));

    //set val and col to control values
    for (int i=0;i<tot_link;i++)
    {
      col[i]=-1;
    }

    //calculate row pointer
    row_ptr[0]=0;
    for (int i=1;i<Nodes;i++)
    {
      row_ptr[i]=row_ptr[i-1]+inbound[i-1];
    }


    //rewind file reading and skip first three lines
    rewind(fp);
    for (int i=0;i<3;i++)
    {
      fgets(buffer, 100, fp);
    }



    int min_index, max_index,nodes_in_row,j;
    //re-read file


    while (fscanf(fp,"%d %d",&n1,&n2)==2)
    {
      if (n1==n2) {;}
      else
      {
        j=0;
        min_index=row_ptr[n1];
        while(col[min_index+j] != -1)
        {
          j+=1;}
        if(j>inbound[n1]){printf("Warning: Faulty behaviour in column count! \n");}
        col[min_index+j]=n2;
      } //count number of links to and from each node
    }


    for(int i=0;i<Nodes;i++)
    {
      if(inbound[i]>1) //only sort if more than one inbound link
      {
        min_index=row_ptr[i];
        max_index=min_index+inbound[i]-1;
        quicksort(col,min_index,max_index);
      }
    }

    for (int i=0;i<tot_link;i++)
    {
      val[i]=1.0/(outbound[col[i]]);
      printf("%f\n",val[i] );
    }

    printArray(col,tot_link);


    // free heap mem
    free(inbound);
    free(outbound);
    free(selflink);
    free(row_ptr);
    free(val);
    free(col);
}


// Function to swap two pointers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size)
{
    printf("%s: ", getName(arr));
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

//quicksort algo on array from element m to n
void quicksort(int arr[], int l, int r)
{
    // skip Base case
    if (l >= r)
    {
        return;
    }

    // Choose pivot to be the last element in the subarray
    int pivot = arr[r];

    // Index indicating the "split" between elements smaller than pivot and
    // elements greater than pivot
    int cnt = l;

    // Traverse through array from l to r
    for (int i = l; i <= r; i++)
    {
        // If an element less than or equal to the pivot is found...
        if (arr[i] <= pivot)
        {
            // Then swap arr[cnt] and arr[i] so that the smaller element arr[i]
            // is to the left of all elements greater than pivot
            swap(&arr[cnt], &arr[i]);

            // Make sure to increment cnt so we can keep track of what to swap
            // arr[i] with
            cnt++;
        }
    }

    // NOTE: cnt is currently at one plus the pivot's index
    // (Hence, the cnt-2 when recursively sorting the left side of pivot)
    quicksort(arr, l, cnt-2); // Recursively sort the left side of pivot
    quicksort(arr, cnt, r);   // Recursively sort the right side of pivot
}
