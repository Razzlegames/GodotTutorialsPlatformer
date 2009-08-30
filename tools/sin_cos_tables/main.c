/**
 *  Builds a precomputed sine and cos table with each index representing a degree,  1 = 1 degree
 *    Meant to be run on a Desktop computer, for precomputations
 */

#include <stdio.h>
#include <math.h>

const char* FILE_NAME  = "sine_cos_table.c";

int main(void)
{

  FILE* file;
  file = fopen(FILE_NAME,"w");
  fprintf(file, 
      "//**************************************************************************\n");
  fprintf(file,"/**\n");
  fprintf(file, "* This file was auto produced by sine_cos_tables by Kyle Luce");
  fprintf(file, "\n*\n*\n*  These are trig results stored as fixed point 8.8 notation \n");
  fprintf(file, "* (assuming 16bit ints e.g. for embedded systems)\n");
  fprintf(file, "\n*/\n");
  fprintf(file, 
      "//**************************************************************************\n");

  //---------------------------------------------------------------------
  //   Figure out sin tables
  //---------------------------------------------------------------------
  fprintf(file, "\n\n");
  fprintf(file,
      "//---------------------------------------------------------------------\n");
  fprintf(file, "//    Fixed point Sin values 0 to 359 degrees\n");
  fprintf(file,
      "//---------------------------------------------------------------------\n");
  fprintf(file, "const signed int sin_table[] = \n{");

  int i;
  int a = 0;
  for(i = 0; i < 360; i++)
  {

    double result = sin( ((double)i)*(M_PI)/180);

    if(i < 359)
    {

      fprintf(file,"%d,",(signed int)(result*256));

    }
    else
    {

      fprintf(file,"%d", (signed int)(result*256));

    }
    if(a /10 == 1)
    {

      fprintf(file,"\n");
      a = 0;

    }
    a++;

  }

  fprintf(file,"};\n\n");
  //---------------------------------------------------------------------
  // Figure out cos tables
  //---------------------------------------------------------------------
  fprintf(file, "\n\n");
  fprintf(file,
      "//---------------------------------------------------------------------\n");
  fprintf(file, "//    Fixed point Cos values 0 to 359 degrees\n");
  fprintf(file,
      "//---------------------------------------------------------------------\n");
  fprintf(file, "const signed int cos_table[] = \n{");

  a = 0;
  for(i = 0; i < 360; i++)
  {
    double result = cos( ((double)i)*(M_PI)/180);

    if(i < 359)
    {

      fprintf(file,"%d,",(signed int)(result*256));

    }
    else
    {

      fprintf(file,"%d", (signed int)(result*256));

    }

    if(a /10 == 1)
    {

      fprintf(file,"\n");
      a = 0;

    }

    a++;

  }
  fprintf(file,"};\n\n");

  fclose(file);

  printf("----------------------------------------------------------\n");
  printf("Reading in file results for: %s\n",FILE_NAME);
  printf("----------------------------------------------------------\n");
  file = fopen(FILE_NAME, "r");

  // Display the file results
  char current = fgetc(file);
  while(current != EOF)
  {

    putchar(current);
    current = fgetc(file);
  }

  return 0;

}
