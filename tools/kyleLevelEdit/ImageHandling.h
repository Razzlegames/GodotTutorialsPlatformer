/* vim: set filetype=cpp.doxygen : */
#ifndef IMAGEHANDLING_H
#define IMAGEHANDLING_H 

#include <FreeImage.h>

/**
 * FreeImage error handler
 * @param fif Format / Plugin responsible for the error
 * @param message Error message
 * */
void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message);


#endif /* IMAGEHANDLING_H */
