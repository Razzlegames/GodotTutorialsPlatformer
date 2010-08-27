/* vim: set filetype=cpp.doxygen : */

#include "map_edit_window.h"


extern GtkBuilder* builder;
MapEditWindow map_edit_window;


void setupMapWindow()
{

  map_edit_window.window = GTK_WIDGET (gtk_builder_get_object (builder, "map_edit_window"));

  map_edit_window.current_tile_image = 
    GTK_WIDGET (gtk_builder_get_object (builder, "current_tile_image"));

  map_edit_window.map_tile_table = 
    GTK_WIDGET (gtk_builder_get_object (builder, "map_tile_table"));

}


