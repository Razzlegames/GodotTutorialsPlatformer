
//{{BLOCK(puzzle_bezel)

//======================================================================
//
//	puzzle_bezel, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 512 + 2048 = 2592
//
//	Time-stamp: 2009-06-14, 15:06:06
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://user.chem.tue.nl/jakvijn )
//
//======================================================================

#ifndef __PUZZLE_BEZEL__
#define __PUZZLE_BEZEL__

#define puzzle_bezelPalLen 32
extern const unsigned short puzzle_bezelPal[16];

#define puzzle_bezelTilesLen 512
extern const unsigned int puzzle_bezelTiles[128];

#define puzzle_bezelMapLen 2048
extern const unsigned short puzzle_bezelMap[1024];

#endif // __PUZZLE_BEZEL__

//}}BLOCK(puzzle_bezel)
