/* vim: set filetype=cpp.doxygen : */
#ifndef GAMEMAP_H
#define GAMEMAP_H 

#include <vector>
#include <gtk/gtk.h>

/**
 *  Represents the data parts of a map
 */
class GameMap
{

  public:

    /// Map data, tile index only (should be exactly the same as GBA data)
    unsigned short* tile_index_data;

    /// All the gdkpixbufs one for each tile 
    ///  (used instead of GtkImage since pixbuf is size scalable)
    std::vector<GdkPixbuf*> pixbufs;

};



#endif /* GAMEMAP_H */
