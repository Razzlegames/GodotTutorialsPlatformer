/* vim: set filetype=cpp.doxygen : */

#include <gba.h>
#include "Background.h"
#include "Debug.h"

#include "toolbox.h"
#define CBB_0  0
#define SBB_0 16
#define SBB_1 SBB_0 + 4
#define SBB_2 SBB_1 + 4

#define CROSS_TX 15
#define CROSS_TY 10

int current_sbb = SBB_0;

unsigned int* current_tiles_cbb[4] = {
(unsigned int*)&tile_mem[0][0],
(unsigned int*)&tile_mem[1][0],
(unsigned int*)&tile_mem[2][0],
(unsigned int*)&tile_mem[3][0] };

//current_tiles_cbb[0] = (unsigned int*)&tile_mem[0][0];
//current_tiles_cbb[1] = (unsigned int*)&tile_mem[1][0];
//current_tiles_cbb[2] = (unsigned int*)&tile_mem[2][0];
//current_tiles_cbb[3] = (unsigned int*)&tile_mem[3][0];

//  define current_tiles_cbb(num)
//  current_tiles_cbb#num

//********************************************************************
/**
 *   Calc the offset to be added to the SBB index.  Call this after 
 *     adding a Map to memory.
 *
 */

int SBB_OFFSET( int size_code)
{

  if(size_code == BG_REG_64x64)
  {

    return 4 ;

  }

  if(size_code == BG_REG_32x32)
  {

    return 1 ;

  }

  if(size_code == BG_REG_32x64 ||
      size_code == BG_REG_64x32)
  {

    return 2 ;

  }

  Debug::printSetup();
  iprintf("\x1b Background size_code error: %d",
     size_code);

  return 0;

}

//********************************************************************
/**
 *
 *      @param bg_number the number of the background to add.
 */

void Background::addBackgroundPallet(const unsigned short* palette, 
    int palette_len, int palette_number)
{

  memcpy(&(pal_bg_bank[palette_number][0]), palette, palette_len);

}

//*******************************************************************
/**
 *
 */

void Background::addBackgoundTiles(const unsigned int* tiles, int tiles_len,
    int cbb)
{

  // Load the tiles: 
  memcpy(current_tiles_cbb[cbb], tiles, tiles_len);
  //memcpy(&tile_mem[0][0], tiles, tiles_len);

  // Update the place holder of where to add more tiles for ccb0
  current_tiles_cbb[cbb] += tiles_len;

}

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
  BGCTRL[bg_number]= BG_CBB(0) | BG_SBB(current_sbb) | 
    size_mode |BG_4BPP |
    (BG_PRIORITY(priority) & BG_PRIO_MASK) | color_mode;

  setOffset(0,0);

  //  // Load the tiles: 
  //  memcpy(&tile_mem[0][0], tiles, tiles_len);

  //memcpy(&(pal_bg_bank[0][0]), palette, palette_len);
  addBackgroundPallet(palette, palette_len, bg_number);


  // Place the tile map in 4 separate SBB
  //   [0][1]
  //   [2][3]
  //
  //   Each SBB is 32 tiles long in this case since
  //     BG is 64X64 (tiles)
  HALF_SBB* src = (HALF_SBB*)map;
  HALF_SBB* dst0 = (HALF_SBB*)se_mem[current_sbb+0];
  HALF_SBB* dst1 = (HALF_SBB*)se_mem[current_sbb+1];
  HALF_SBB* dst2 = (HALF_SBB*)se_mem[current_sbb+2];
  HALF_SBB* dst3 = (HALF_SBB*)se_mem[current_sbb+3];

  // For each row copy to the appropriate SBB
  //    (32 rows)
  for(int i = 0; i < 32; i++)
  {

    *(dst0++) = *(src++); 
    *(dst0++) = *(src++); 

    if(size_mode != BG_REG_32x32)
    {

      *(dst1++) = *(src++); 
      *(dst1++) = *(src++); 

    }

  }

  // Only copy to SBB 2 and 3 if you have a 64x64 map 
  //   on your hands ...  
  //   [0][1]
  //   [2][3]
  if(size_mode == BG_REG_64x64)
  {

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

  this->bg_number = bg_number;
  current_sbb += SBB_OFFSET( size_mode);

}

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
  BGCTRL[bg_number]= BG_CBB(0) | BG_SBB(current_sbb) | 
    size_mode |BG_4BPP |
    (BG_PRIORITY(priority) & BG_PRIO_MASK) | color_mode;

  // Make the map scroll start at the origin
  setOffset(0,0);

  // Load the tiles: 
  //memcpy(&tile_mem[bg_number][0], tiles, tiles_len);

  if(color_mode == BG_16_COLOR)
  {

    //memcpy(&(pal_bg_bank[bg_number][0]), palette, palette_len);
    addBackgroundPallet(palette, palette_len, 0);

  }
  else
  {

    // In 256 color background, the pallet will always start at 0.
    addBackgroundPallet(palette, palette_len, 0);

  }

  memcpy(&se_mem[current_sbb][0], map, map_len);

  //  Debug::printSetup();
  //  iprintf("\x1b[0;0H current_tiles_cbb0: %08x",
  //      current_tiles_cbb0);
  //  iprintf("\x1b[1;0H current_tiles_cbb1: %08x",
  //      current_tiles_cbb1);
  //  iprintf("\x1b[2;0H current_tiles_cbb2: %08x",
  //      current_tiles_cbb2);
  //  iprintf("\x1b[3;0H current_tiles_cbb3: %08x",
  //      current_tiles_cbb(3));


  this->bg_number = bg_number;

  current_sbb += SBB_OFFSET(size_mode);

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

