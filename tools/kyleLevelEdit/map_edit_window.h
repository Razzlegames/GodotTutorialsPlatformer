/* vim: set filetype=cpp.doxygen : */
#ifndef MAP_EDIT_WINDOW_H
#define MAP_EDIT_WINDOW_H 

#include <gtk/gtk.h>

struct MapEditWindow_
{

  /// Actual GTKWindow object
  GtkWidget* window;

  /// Current tile image chosen
  GtkWidget* current_tile_image;

  /// Table that represents the entire map (each cell is a tile)
  GtkWidget* map_tile_table;

};

typedef struct MapEditWindow_ MapEditWindow;

#endif /* MAP_EDIT_WINDOW_H */
