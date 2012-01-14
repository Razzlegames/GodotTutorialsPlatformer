
//{{BLOCK(test_map2)

//======================================================================
//
//	test_map2, 512x512@4, 
//	+ palette 16 entries, not compressed
//	+ 71 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 2272 + 8192 = 10496
//
//	Time-stamp: 2009-03-25, 08:38:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_MAP2_H
#define GRIT_TEST_MAP2_H

#define test_map2TilesLen 2272
extern const unsigned int test_map2Tiles[568];

#define test_map2MapLen 8192
extern const unsigned short test_map2Map[4096];

#define test_map2PalLen 32
extern const unsigned short test_map2Pal[16];

#endif // GRIT_TEST_MAP2_H

//}}BLOCK(test_map2)
