/* vim: set filetype=cpp.doxygen : */

#include <stdio.h>
#include "ImageHandling.h"

/**
 * FreeImage error handler
 * @param fif Format / Plugin responsible for the error
 * @param message Error message
 * */

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
{

  printf("\n*** ");
  if(fif != FIF_UNKNOWN) 
  {
    printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
  }
  printf(message);
  printf(" ***\n");

}

