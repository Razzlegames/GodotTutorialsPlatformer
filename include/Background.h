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

typedef TILE HALF_SBB;

/**
 *  Information (pallet, tiles, tile_map) the hardware needs
 *    to display a proper background, and supporting functions to load 
 *    and keep track of these backgrounds.
 */

class Background
{

  public:

    /// The background number on the GBA 
    ///         *0-3 possible in mode 0,
    ///         *0-2 possible in mode 1,
    ///         *2-3 possible in mode 2 (affine)
    int bg_number;

    ///  Background will be Either 256 or 16 color mode
    int mode;

    void setOffset(int x, int y);

    void loadMap(const unsigned int* tiles, 
        int tiles_len, const unsigned short* map, int map_len,
        const unsigned short* palette, int palette_len, int bg_number,
        int priority, int color_mode, int size_mode);

    void loadMapRearange(const unsigned int* tiles, 
        int tiles_len, const unsigned short* map, int map_len,
        const unsigned short* palette, int palette_len, int bg_number,
        int priority, int color_mode, int size_mode);

    inline static void addBackgroundPallet(const unsigned short* palette, int palette_len,
        int palette_number);

    static void addBackgoundTiles(const unsigned int* tiles, int tiles_len,
    int cbb);

};


#endif /* BACKGROUND_H */
