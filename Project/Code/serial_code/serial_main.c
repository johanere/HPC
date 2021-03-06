#include "functions.h"

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);

void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                        int image_height, int image_width,
                        int num_components, int quality);


int main(int argc, char *argv[])
{
int m, n, c, iters;
float kappa;
image u, u_bar;
unsigned char *image_chars;
char *input_jpeg_filename, *output_jpeg_filename;

if (argc < 4)
{
  printf("Bad Usage: - provide as CL args: kappa, iters, input_jpeg_filename, output_jpeg_filename  \n");
  exit(1);
}

/* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename */
iters=atoi(argv[1]);
kappa=atof(argv[2]);
input_jpeg_filename=argv[3]; //"../figure/mona_lisa_noisy.jpg";
output_jpeg_filename=argv[4]; //"testout3.jpg";


import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

allocate_image(&u, m, n);
allocate_image (&u_bar, m, n);

convert_jpeg_to_image (image_chars, &u);
iso_diffusion_denoising (&u, &u_bar, kappa, iters);

convert_image_to_jpeg (&u_bar, image_chars); //CHANGE TO u_bar!

export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
deallocate_image (&u);
deallocate_image (&u_bar);
return 0;
}
