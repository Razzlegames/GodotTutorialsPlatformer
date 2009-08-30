/* vim: set filetype=cpp.doxygen : */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdarg.h>

#include <FreeImage.h>
#include "ImageHandling.h"
#include "map_edit_window.h"

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

void error_dialog(const char* str)
{

  GtkWidget* dlg;

  dlg= 
    gtk_message_dialog_new (
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE,
        str
        );

  // Destroy the popup when the user cancels or closes the window
  g_signal_connect_swapped(dlg, "response", G_CALLBACK(gtk_widget_destroy), dlg);

  gtk_widget_show( dlg );

  return;

}


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
 * Create a new map
 */

extern "C" gboolean cancel_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event )
{

  gtk_widget_hide (map_size_window);       
  return TRUE;

}


//****************************************************************     
/**
 * Commit map changes from map change dialog window
 *
 */

extern "C" gboolean commit_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event )
{

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

  //  int i;
  //  for(i = 0; i < 30; i++)
  //  {
  //
  //    image1 = gtk_image_new_from_file("ball_green.bmp");
  //
  //  }

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

