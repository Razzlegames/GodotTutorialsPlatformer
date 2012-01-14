
//{{BLOCK(gimp_grid)

//======================================================================
//
//	gimp_grid, 512x512@4, 
//	+ palette 16 entries, not compressed
//	+ 63 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 2016 + 8192 = 10240
//
//	Time-stamp: 2010-01-02, 09:58:02
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://user.chem.tue.nl/jakvijn )
//
//======================================================================

#ifndef __GIMP_GRID__
#define __GIMP_GRID__

#define gimp_gridPalLen 32
extern const unsigned short gimp_gridPal[16];

#define gimp_gridTilesLen 2016
extern const unsigned int gimp_gridTiles[504];

#define gimp_gridMapLen 8192
extern const unsigned short gimp_gridMap[4096];

#endif // __GIMP_GRID__

//}}BLOCK(gimp_grid)
