#include "functions.h"

void swaparrays(void** p1, void** p2) //function to swap pointers of arrays
{
  void* tmp;
  tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
} //end of swaparrays function

void allocate_image(image *u, int m, int n)
{
  u->m = m; // assign number of vertical elements in image
  u->n = n; // assign number of horizontal elements in image
  //allocate matrix
  u->image_data = (float**) malloc(m * sizeof(float*));
  for(int i = 0; i < m; i++)
  {
    u->image_data[i] = (float*) malloc(n * sizeof(float));
  }
} //end of allocate_image function

void deallocate_image(image *u)
{
  for(int i=0;i<u->m;i++)
    free(u->image_data[i]); //deallocate rows
  free(u->image_data); //deallocate columns
}//end of deallocate_image function

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
  for (int i = 0; i < u->m; i++) //iterate rows
  {
    for (int j = 0; j < u->n; j++) //iterate columns
    {
      u->image_data[i][j] = (float) image_chars[u->n*i+j]; //assign color value from image_chars to image_data
    }
  }
}//end of convert_jpeg_to_image function


void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
  for (int i = 0; i < u->m; i++) //iterate rows
  {
    for (int j = 0; j < u->n; j++) //iterate columns
    {
      image_chars[u->n*i+j] = u->image_data[i][j]+(u->image_data[i][j])*0; //assigns color value from image_data to image_chars
    }
  }
}//end of convert_image_to_jpeg function


void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters)
{
  //boundary pixels horizontal
  for (int i = 0; i < u->n; i++) //iterate rows
  {
    u_bar->image_data[0][i]=u->image_data[0][i];
    u_bar->image_data[u->m-1][i]=u->image_data[u->m-1][i];
  }

  //boundary pixels vertical
  for (int i = 0; i < u->m; i++) //iterate rows
  {
    u_bar->image_data[i][0]=u->image_data[i][0];
    u_bar->image_data[i][u->n-1]=u->image_data[i][u->n-1];
  }


  for (int itr=0; itr <= iters; itr++)
  {
    for (int i = 1; i < u->m-2; i++) //iterate rows
    {
      for (int j = 1; j < u->n-2; j++) //iterate columns
      { //calculate new u_bar
        u_bar->image_data[i][j]=u->image_data[i][j]+kappa*( u->image_data[i-1][j] + u->image_data[i][j-1]
          - 4*u->image_data[i][j] +u->image_data[i+1][j] +u->image_data[i][j+1] );
      }
    }
  //swap such that the new values are old values for the next iteration
  swaparrays((void*)&u, (void*)&u_bar);
  }
  //swap to make sure u_bar is the newest version after all iterations are completed
  swaparrays((void*)&u, (void*)&u_bar);

}//end of iso_diffusion_denoising function
