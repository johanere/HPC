#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int count;
    char p;

    fp = fopen("WGtest.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char buffer[100];

    //skip first two lines
    fgets(buffer, 100, fp);
    fgets(buffer, 100, fp);
    int Nodes,Edges;

    // read Nodes and Edges from line three
    fscanf(fp,"%*s %*s %d  %*s %d ",&Nodes,&Edges);
    printf("%d %d \n", Nodes, Edges);

    int n1,n2;
    while(fscanf(fp,"%d %d",&n1,&n2) =)
    {
    printf("%d %d\n", n1,n2);
    }



}
/*

    count=0;
    while(count<4){
    read = getline(&line, &len, fp);
      count++;
    }

    read = getline(&line, &len, fp);


    fclose(fp);
    if (line)
        free(line);
    return 0;
}

/* hyperlink matrix

[

*/





/*
int main(int argc, char *argv[])
{
  FILE *fptr;

   char c;


   // Open file
   fptr = fopen("WGtest.txt", "r");
   if (fptr == NULL)
   {
       printf("Cannot open file \n");
       exit(0);
   }

   // Read contents from file
   c = fgetc(fptr);
   while (c != EOF)
   {
       printf ("%c", c);
       c = fgetc(fptr);
   }
   printf ("\n");
   fclose(fptr);
   return 0;
}
*/
/*
txt->hyperlinkmatrix as CRS
*/

/*
p.87
val=[-4,2,2,8,8,-5,10,-5,10,-6]
col_idx=[1,2,1,3,2,4,5,3,3,5]
row_ptr=[1,3,5,8,9]
*/
