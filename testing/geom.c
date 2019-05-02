#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void swaparrays(void** p1, void** p2)
 {
void* tmp;
tmp = *p1;
*p1 = *p2;
*p2 = tmp;
}


typedef struct
{
  float** image_data; /* a 2D array of floats */
  int m; /* # pixels in vertical-direction */
  int n; /* # pixels in horizontal-direction */
}
image;


int main()
{

image u, u_bar;
int m=5;
int n=3;

u.m=m;
u_bar.m=m;

u.n=n;
u_bar.n=n;

u.image_data = (float**) malloc(m * sizeof(float*));
u_bar.image_data = (float**) malloc(m * sizeof(float*));

for(int i = 0; i < m; i++)
{
  u.image_data[i] = (float*) malloc(n * sizeof(float));
  u_bar.image_data[i] = (float*) malloc(n * sizeof(float));
}
printf("u  ubar\n" );
for (int i = 0; i < u.m; i++) {
  for (int j = 0; j < u.n; j++) {
    u.image_data[i][j] = 2;
    u_bar.image_data[i][j] = 1;
    printf("%f %f \n", u.image_data[i][j],u_bar.image_data[i][j]);
  }
}
printf("swap! \n" );
swaparrays((void*)&u, (void*)&u_bar);
printf("u  ubar\n" );
for (int i = 0; i < u.m; i++) {
  for (int j = 0; j < u.n; j++) {
    printf("%f %f \n", u.image_data[i][j],u_bar.image_data[i][j]);
  }
}


}
