/* vim: set filetype=cpp.doxygen : */

#include <gba.h>
#include "Background.h"

#include "toolbox.h"
#define CBB_0  0
#define SBB_0 28

#define CROSS_TX 15
#define CROSS_TY 10


//********************************************************************
/**
 *
 *      @param bg_number the number of the background to add.
 */

static void addBackgroundPallet(int bg_number, u16* pallet)
{

}

//*******************************************************************
/**
 *
 */

static void addBackgoundTiles(int bg_number, u8* tiles)
{

}

//********************************************************************
/**
 *   Load a background map that is out of order, 
 *     (needs to be arranged in 4 screen block segments)
 *
 *   @param tiles memory containing BG tiles 
 *   @param tiles_len length in bytes of all total tiles
 *   @param map Index of which tile to place where
 *   @param map_len length in bytes of all map pieces
 *   @param palette color pallet for all backgrounds
 *   @param palette_len length in bytes for the pallet to load
 */

void Background::loadMapRearange(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number)
{

  // initialize a background
  REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_32x32 |BG_4BPP;
  REG_BG0HOFS= 0;
  REG_BG0VOFS= 0;

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

  //memcpy(&se_mem[SBB_0][0], tile_map, TEST_MAP_SIZE*sizeof(u16));
  //memcpy(&se_mem[SBB_0][0], brinMap, brinMapLen);
  //memcpy(&se_mem[SBB_0][0], map, map_len);

  //    for(ii=0; ii<4; ii++)
  //                for(jj=0; jj<32*32; jj++)
  //                            *pse++= SE_PALBANK(ii) ;
  //| 0;

}


//********************************************************************
/**
 *   Load a background map that is inorder, (does not need to be rearranged
 *   into 4 blocks memory transfer.
 *
 *   @param tiles memory containing BG tiles 
 *   @param tiles_len length in bytes of all total tiles
 *   @param map Index of which tile to place where
 *   @param map_len length in bytes of all map pieces
 *   @param palette color pallet for all backgrounds
 *   @param palette_len length in bytes for the pallet to load
 */

void Background::loadMap(const unsigned int* tiles, 
    int tiles_len, const unsigned short* map, int map_len,
    const unsigned short* palette, int palette_len, int bg_number)
{

  // initialize a background
  REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_32x32 |BG_4BPP;
  REG_BG0HOFS= 0;
  REG_BG0VOFS= 0;

  // Load the tiles: 
  memcpy(&tile_mem[0][0], tiles, tiles_len);

  //HALF_SBB* tiles = (HALF_SBB*)tile_rows;
  //    for(int i = 0; 
  //        i < TEST_MAP_HEIGHT/TEST_MAP_WIDTH; i++)
  //    {
  //
  //        tile_mem[CBB_0][i]= tiles[i];
  //
  //        //        if(i == 4)
  //        //        {
  //        //
  //        //            //u32* tile_t = (u32*)&(tile_mem[CBB_0][i]);
  //        //            u32* tile_t = (u32*)&(tiles[i]);
  //        //            Debug::printSetup();	     
  //        //
  //        //            iprintf("\x1b[1;0H Tile %d:",i );
  //        //            iprintf("\x1b[2;0H 0x%08x", tile_t[0]);
  //        //            iprintf("\x1b[3;0H 0x%08x", tile_t[1]);
  //        //            iprintf("\x1b[4;0H 0x%08x", tile_t[2]);
  //        //            iprintf("\x1b[5;0H 0x%08x", tile_t[3]);
  //        //            iprintf("\x1b[6;0H 0x%08x", tile_t[4]);
  //        //            iprintf("\x1b[7;0H 0x%08x", tile_t[5]);
  //        //            iprintf("\x1b[8;0H 0x%08x", tile_t[6]);
  //        //            iprintf("\x1b[9;0H 0x%08x", tile_t[7]);
  //        //
  //        //            iprintf("\x1b[10;0H Prev Tile Address 0x%08x:",&tile_mem[CBB_0][i-1] );
  //        //            iprintf("\x1b[11;0H Tile Address 0x%08x:",&tile_mem[CBB_0][i] );
  //        //            iprintf("\x1b[12;0H BG0_map Address 0x%08x:",bg0_map);
  //        //            while(1);
  //        //        }
  //
  //    }

  //  // create a palette
  //  for(int i = 0; i  < 256; i++)
  //  {
  //
  //    // Convert Gimp colors from 8bit to 4bit (255 to 31 max)
  //    //   Equivalent to the following, but using more efficient shifts
  //    //        // Red
  //    //        int color0 = (int)(test_map_pallet[i][0]*(32.0/256.0);
  //    //        // Green
  //    //        int color1 = (int)(test_map_pallet[i][1]*(32.0/256.0);
  //    //        // Blue 
  //    //        int color2 = (int)(test_map_pallet[i][2]*(32.0/256.0);
  //    int color0 = test_map_pallet[i][0] >> 3;
  //    int color1 = test_map_pallet[i][1] >> 3;
  //    int color2 = test_map_pallet[i][2] >> 3;
  //
  //    pal_bg_bank[0][i]= RGB15(color0, color1,color2);
  //
  //  }

  memcpy(&(pal_bg_bank[0][0]), palette, palette_len);

  //    // create a palette
  //    pal_bg_bank[0][0]= RGB15((int)(31/2),  0,  0);
  //    pal_bg_bank[0][1]= RGB15(31,  0,  0);
  //    pal_bg_bank[0][2]= RGB15( 0, 31,  0);
  //    pal_bg_bank[0][3]= RGB15( 0,  0, 31);
  //    pal_bg_bank[0][4]= RGB15(16, 16, 16);

  //  // Create a map: four contingent blocks of 
  //  //   0x0000, 0x1000, 0x2000, 0x3000.
  //  //SCR_ENTRY *pse = bg0_map;
  //  u16 tile_map[TEST_MAP_SIZE];
  //
  //  for(int i = 0; i < TEST_MAP_SIZE; i++)
  //  {
  //
  //    //pse[i] = ((u16)TEST_MAP[i] ) | SE_PALBANK(0) ;
  //    tile_map[i] = ((u16)TEST_MAP[i] ) | SE_PALBANK(0) ;
  //
  //    if(i & 0x0001)
  //    {
  //
  //      //*pse |= SE_VFLIP;
  //      //*pse |= SE_HFLIP;
  //
  //    }
  //
  //    //        if(TEST_MAP[i] > 1)
  //    //        {
  //    //
  //    //            Debug::printSetup();	     
  //    //
  //    //            iprintf("\x1b[1;0H Tile was %d:",TEST_MAP[i] );
  //    //
  //    //
  //    //        }
  //
  //  }

  //     HALF_SBB* src = (HALF_SBB*)tile_map;
  //     HALF_SBB* dst0 = (HALF_SBB*)se_mem[SBB_0+0];
  //     HALF_SBB* dst1 = (HALF_SBB*)se_mem[SBB_0+1];
  //     HALF_SBB* dst2 = (HALF_SBB*)se_mem[SBB_0+2];
  //     HALF_SBB* dst3 = (HALF_SBB*)se_mem[SBB_0+3];
  //
  //     // For each row copy to the appropriate SBB
  //     for(int i = 0; i < 32; i++)
  //     {
  //
  //         *(dst0++) = *(src++); 
  //         *(dst0++) = *(src++); 
  //
  //         *(dst1++) = *(src++); 
  //         *(dst1++) = *(src++); 
  //
  //     }
  //
  //     // For each row copy to the appropriate SBB
  //     for(int i = 0; i < 32; i++)
  //     {
  //
  //
  //         *(dst2++) = *(src++); 
  //         *(dst2++) = *(src++); 
  //
  //         *(dst3++) = *(src++); 
  //         *(dst3++) = *(src++); 
  //
  //
  //     }


  //memcpy(&se_mem[SBB_0][0], tile_map, TEST_MAP_SIZE*sizeof(u16));
  //memcpy(&se_mem[SBB_0][0], brinMap, brinMapLen);
  memcpy(&se_mem[SBB_0][0], map, map_len);

  //    for(ii=0; ii<4; ii++)
  //                for(jj=0; jj<32*32; jj++)
  //                            *pse++= SE_PALBANK(ii) ;
  //| 0;

}

