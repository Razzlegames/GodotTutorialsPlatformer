/* vim: set filetype=cpp.doxygen : */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdarg.h>

#include <FreeImage.h>
#include "ImageHandling.h"
#include "map_edit_window.h"
#include "error_dialogs.h"

extern GtkBuilder* builder;
extern GtkWidget* window;
extern GtkWidget* tile_window;

extern MapEditWindow map_edit_window;
extern GtkWidget* map_size_window;
extern GtkWidget* map_tile_table;

extern GdkPixbuf** map_tiles_pix;

GtkWidget* map_height_txt = NULL;
GtkWidget* map_width_txt = NULL;
extern GtkWidget* image1;

#define  ERROR_DIALOG(fmt, ...) { char temp2[0xFF];\
  snprintf(temp2, 0xFF, fmt, ##__VA_ARGS__ ); \
  error_dialog(temp2); }


//****************************************************************     
/**
 */

void init_map_size_dialog()
{

  //  if(map_height_txt)
  //  {
  //
  //    fprintf(stderr, "Error map height txt was not NULL!n");
  //    return;
  //
  //  }
  //
  //  if(map_width_txt)
  //  {
  //
  //    fprintf(stderr, "Error map width txt was not NULL!n");
  //    return;
  //
  //  }

  map_height_txt = GTK_WIDGET (gtk_builder_get_object (builder, "map_height_txt"));
  map_width_txt = GTK_WIDGET (gtk_builder_get_object (builder, "map_width_txt"));

  if(!map_height_txt)
  {

    fprintf(stderr, "Error map height txt was  NULL!\n");
    ERROR_DIALOG("Error map height txt was  NULL!\n");
    return;

  }

  if(!map_width_txt)
  {

    fprintf(stderr, "Error map width txt was  NULL!\n");
    ERROR_DIALOG("Error map width txt was  NULL!\n");
    return;

  }

}

//****************************************************************     
/**
 * When cancel button is hit on dialog
 */

extern "C" gboolean cancel_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event )
{

  gtk_widget_hide (map_size_window);       
  return TRUE;

}


/// Map data, tile index only
extern unsigned short* tile_index_data;

//****************************************************************     
/**
 *   Resize map data based on map size change
 *
 *   @param height height of the map
 *   @param width width of the map
 */
void resize_map_data(int height, int width)
{

  if(tile_index_data)
  {

    tile_index_data = (unsigned short*)realloc(tile_index_data, 
        height*width*sizeof(*tile_index_data));

  }
  else
  {

    tile_index_data = (unsigned short*)malloc(
        height*width*sizeof(*tile_index_data));

  }

}

//****************************************************************     
/**
 * Commit map changes from map change dialog window
 *
 */

extern "C" gboolean commit_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event )
{

  //------------------------------------------------------------
  // Grab the dimensions of the map from the dialog
  //------------------------------------------------------------
  const gchar* width_str = gtk_entry_get_text(GTK_ENTRY(map_width_txt));
  if(width_str == NULL)
  {

    fprintf(stderr, "Error map width text entered was NULL!\n");
    ERROR_DIALOG("Error map width text entered was NULL!\n");
    return 0;

  }

  const gchar* height_str = gtk_entry_get_text(GTK_ENTRY(map_height_txt));
  if(height_str == NULL)
  {

    fprintf(stderr, "Error map height text entered was NULL!\n");
    ERROR_DIALOG("Error map height text entered was NULL!\n");
    return 0;

  }

  //------------------------------------------------------------
  // Convert the dimensions of the map from the dialog
  //------------------------------------------------------------
  int width = atoi(width_str);
  int height = atoi(height_str);
  if(width < 1 || height < 1)
  {

    fprintf(stderr, "Error map dimension was zero! %dx%d\n",
        width, height);
    ERROR_DIALOG("Error map dimension was zero! %dx%d\n",
        width, height);
    return 0;

  }

  printf("Map resized to: %dx%d tiles\n",width, height);
  fflush(stdout);

  gtk_table_resize(GTK_TABLE(map_tile_table), height, width);

  //------------------------------------------------------------
  // Be sure to resize any data associated with the map
  //------------------------------------------------------------
  resize_map_data(height, width);

  // Add some pictures to the table (for testing only)
  GtkWidget* image;
  int i;
  for(i = 0; i < height; i++)
  {

    int a;
    for(a = 0; a < width; a++)
    {

      image = gtk_image_new_from_file("ball_green.bmp");
      gtk_table_attach(GTK_TABLE(map_tile_table), image, a, a+1,
          i, i+1, GTK_FILL, GTK_FILL, 0, 0); 

      gtk_widget_show (image);       

    }

  }

  gtk_widget_hide (map_size_window);       
  return TRUE;

}


//****************************************************************     
/**
 * Create a new map
 */

extern "C" gboolean show_map_size_dialog_event( GtkWidget *widget, 
    GdkEventConfigure *event )
{

  gtk_widget_show (map_size_window);       
  printf("Hey it worked..!\n");
  fflush(stdout);
  return TRUE;

}

