/* vim: set filetype=cpp.doxygen : */

#include <gba.h>
#include "Background.h"

#include "toolbox.h"
#define CBB_0  0
#define SBB_0 28-4
#define SBB_1 SBB_0 + 4
#define SBB_2 SBB_1 + 4

#define CROSS_TX 15
#define CROSS_TY 10


////********************************************************************
///**
// *
// *      @param bg_number the number of the background to add.
// */
//
//static void addBackgroundPallet(int bg_number, u16* pallet)
//{
//
//}
//
////*******************************************************************
///**
// *
// */
//
//static void addBackgoundTiles(int bg_number, u8* tiles)
//{
//
//}

//********************************************************************
/**
 *   Load a background map that is out of order, 
 *     (needs to be arranged in 4 screen block segments).
 *      Max size a bg map can be is 0x2000 bytes, 
 *      Which is 4 SBB entries, since 1 SBB = 0x800 bytes)
 *
 * Addr:0x6000000   | 0x6004000  | 0x6008000 | 0x600C000
 *   SBB:   0 - 7   | 8-15       | 16-23     | 24-31
 *
 *   @param tiles memory containing BG tiles 
 *   @param tiles_len length in bytes of all total tiles
 *   @param map Index of which tile to place where
 *   @param map_len length in bytes of all map pieces
 *   @param palette color pallet for all backgrounds
 *   @param palette_len length in bytes for the pallet to load
 *   @param priority priority of this backgrounds drawing order
 *   @param color_mode BG_256_COLOR or BG_16_COLOR
 *   @param size_mode The size and mode of the background, 
 *      eg BG_REG_64x64
 */

void Background::loadMapRearange(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number,
    int priority, int color_mode, int size_mode)
{

  // initialize a background
  BGCTRL[bg_number]= BG_CBB(bg_number) | BG_SBB(SBB_0) | 
    size_mode |BG_4BPP |
    (BG_PRIORITY(priority) & BG_PRIO_MASK) | color_mode;

  setOffset(0,0);

  // Load the tiles: 
  memcpy(&tile_mem[0][0], tiles, tiles_len);

  memcpy(&(pal_bg_bank[0][0]), palette, palette_len);


  // Place the tile map in 4 separate SBB
  //   [0][1]
  //   [2][3]
  //
  //   Each SBB is 32 tiles long in this case since
  //     BG is 64X64 (tiles)
  HALF_SBB* src = (HALF_SBB*)map;
  HALF_SBB* dst0 = (HALF_SBB*)se_mem[SBB_0+0];
  HALF_SBB* dst1 = (HALF_SBB*)se_mem[SBB_0+1];
  HALF_SBB* dst2 = (HALF_SBB*)se_mem[SBB_0+2];
  HALF_SBB* dst3 = (HALF_SBB*)se_mem[SBB_0+3];

  // For each row copy to the appropriate SBB
  //    (32 rows)
  for(int i = 0; i < 32; i++)
  {

    *(dst0++) = *(src++); 
    *(dst0++) = *(src++); 

    *(dst1++) = *(src++); 
    *(dst1++) = *(src++); 

  }

  // For each row copy to the appropriate SBB
  //    (32 rows)
  for(int i = 0; i < 32; i++)
  {

    *(dst2++) = *(src++); 
    *(dst2++) = *(src++); 

    *(dst3++) = *(src++); 
    *(dst3++) = *(src++); 

  }

}

//#define BACKGROUND_OFFSET(

//********************************************************************
/**
 *   Load a background map that is inorder, (does not need to 
 *   be rearranged into 4 blocks memory transfer).
 *      Max size a bg map can be is 0x2000 bytes, 
 *      Which is 4 SBB entries, since 1 SBB = 0x800 bytes)
 *
 *Addr: 0x6000000   | 0x6004000  | 0x6008000 | 0x600C000
 *   SBB:   0 - 7   | 8-15       | 16-23     | 24-31
 *
 *   @param tiles memory containing BG tiles 
 *   @param tiles_len length in bytes of all total tiles
 *   @param map Index of which tile to place where
 *   @param map_len length in bytes of all map pieces
 *   @param palette color pallet for all backgrounds
 *   @param palette_len length in bytes for the pallet to load
 *   @param priority priority of this backgrounds drawing order
 *   @param color_mode BG_256_COLOR or BG_16_COLOR
 *   @param size_mode The size and mode of the background, 
 *      eg BG_REG_64x64
 */

void Background::loadMap(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number,
    int priority, int color_mode, int size_mode)
{

  // initialize a background
  BGCTRL[bg_number]= BG_CBB(bg_number) | BG_SBB(SBB_0) | 
    size_mode |BG_4BPP |
    (BG_PRIORITY(priority) & BG_PRIO_MASK) | color_mode;

  setOffset(0,0);

  // Load the tiles: 
  memcpy(&tile_mem[bg_number][0], tiles, tiles_len);

  if(color_mode == BG_16_COLOR)
  {

    memcpy(&(pal_bg_bank[bg_number][0]), palette, palette_len);

  }
  else
  {

    memcpy(&(pal_bg_bank[0][0]), palette, palette_len);
  
  }

  memcpy(&se_mem[SBB_0][0], map, map_len);

  this->bg_number = bg_number;

}

//********************************************************************
/**
 *   Set the background offset (scrolling) for the 
 *   given bg this represents.
 *
 *   @param x x offset
 *   @param y y offset
 */
void Background::setOffset(int x, int y)
{

  BG_OFFSET[bg_number].x = x;
  BG_OFFSET[bg_number].y = y;

}

