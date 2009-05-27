/* vim: set filetype=cpp.doxygen : */
#ifndef BACKGROUND_H
#define BACKGROUND_H 

//
// vector<Gummy*> gummy_vector;
// Main devkitArm Headers
#include <stdlib.h>
#include <string.h>
#include <gba.h>
#include <gba_sprites.h>
#include <toolbox.h>


/**
 *  Information (pallet, tiles, tile_map) the hardware needs
 *    to display a proper background
 */

class Background
{

void loadMap(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number);

void loadMapRearange(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number);

};


#endif /* BACKGROUND_H */
