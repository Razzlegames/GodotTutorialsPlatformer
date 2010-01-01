/* vim: set filetype=cpp.doxygen : */

#include <gtk/gtk.h>
#include <FreeImage.h>
#include "ImageHandling.h"
#include "map_edit_window.h"

extern "C"
{
#include "map_edit_window.h"
}
#include "map_size_dialog.h"
#include "error_dialogs.h"

/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;
const int DEFAULT_PIXMAP_WIDTH = 600;
const int DEFAULT_PIXMAP_HEIGHT = 600;

GtkBuilder* builder;
GtkWidget* window;
GtkWidget* tile_window;
extern MapEditWindow map_edit_window;
GtkWidget* map_size_window;
GtkWidget* tile_vbox;
GtkWidget* map_tile_table;

GdkPixbuf** map_tiles_pix;
GtkWidget* image1 ;

/// Map data, tile index only
unsigned short* tile_index_data = NULL;

//****************************************************************     
/* Draw a rectangle on the screen */

static void draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{

  GdkRectangle update_rect;

  update_rect.x = x - 1;
  update_rect.y = y - 1;
  update_rect.width = 2;
  update_rect.height = 2;
  gdk_draw_rectangle (pixmap,
      widget->style->black_gc,
      TRUE,
      update_rect.x, update_rect.y,
      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget,                   
      update_rect.x, update_rect.y,
      update_rect.width, update_rect.height);

}

//****************************************************************     

extern "C"  gboolean button_press_event( GtkWidget *widget, GdkEventButton *event )
{

  printf("captured event!\n");
  fflush(stdout);

  if (event->button == 1 && pixmap != NULL)
      draw_brush (widget, event->x, event->y);

  return TRUE;
}

////****************************************************************     
//static gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event )
//{
//
//  int x, y;
//  GdkModifierType state;
//
//  if (event->is_hint)
//      gdk_window_get_pointer (event->window, &x, &y, &state);
//  else
//  {
//    x = event->x;
//    y = event->y;
//    state = (GdkModifierType)event->state;
//  }
//
//  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
//      draw_brush (widget, x, y);
//
//  return TRUE;
//}

//****************************************************************     
/* Redraw the screen from the backing pixmap */

extern "C" gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{

  gdk_draw_drawable(widget->window,
      widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
      pixmap,
      event->area.x, event->area.y,
      event->area.x, event->area.y,
      event->area.width, event->area.height);

  return FALSE;
}

//****************************************************************     
/* Create a new backing pixmap of the appropriate size */

extern "C"  gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event )
{

  printf("captured configure event!\n");
  fflush(stdout);

  //  if (pixmap)
  //      g_object_unref(pixmap);
  //
  //  pixmap = gdk_pixmap_new(widget->window,
  //      widget->allocation.width,
  //      widget->allocation.height,
  //      -1);
  //
  //  gdk_draw_rectangle (pixmap,
  //      widget->style->white_gc,
  //      TRUE,
  //      0, 0,
  //      widget->allocation.width,
  //      widget->allocation.height);

  return TRUE;

}

//****************************************************************     
/* Create a new backing pixmap of the appropriate size */

extern "C"  gboolean realize_drawingarea( GtkWidget *widget, 
    GdkEventConfigure *event )
{

  printf("realize event!\n");
  fflush(stdout);

  if (pixmap)
      g_object_unref(pixmap);

  pixmap = gdk_pixmap_new(widget->window,
      DEFAULT_PIXMAP_WIDTH,
      //widget->allocation.width,
      DEFAULT_PIXMAP_HEIGHT,
      //widget->allocation.height,
      -1);

  gdk_draw_rectangle (pixmap,
      widget->style->white_gc,
      TRUE,
      0, 0,
      DEFAULT_PIXMAP_WIDTH,
      DEFAULT_PIXMAP_HEIGHT);

  return TRUE;

}


//****************************************************************     

extern "C" void on_window_destroy (GtkObject *object, gpointer user_data)
{

  gtk_main_quit();

}

//****************************************************************     

extern "C" void drawingarea1_button_press_event_cb(GtkWidget* widget, 
    GdkEventButton* event)
{

  printf("captured event!\n");
  fflush(stdout);

}


//****************************************************************     

gboolean image_press_cb(GtkWidget* event_box, GdkEventButton* event,
    gpointer data)
{

  g_print("Retardo button pushed...\n");

}

//****************************************************************     

int main (int argc, char *argv[])
{

  // Initialize the free image library for converting images, etc
  FreeImage_Initialise();

  gtk_init (&argc, &argv);

  // Create the GUI from the glade file
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "levelEditorGUI.glade", NULL);

  // Create a reference to all needed widgets (from names in glade file)
  window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
  tile_window = GTK_WIDGET (gtk_builder_get_object (builder, "tile_window"));

  setupMapWindow();

  map_size_window = GTK_WIDGET (gtk_builder_get_object (builder, "map_size_window"));
  map_tile_table = GTK_WIDGET (gtk_builder_get_object (builder, "map_tile_table"));
  tile_vbox = 
    GTK_WIDGET (gtk_builder_get_object (builder, "tile_vbox"));

  init_map_size_dialog();

  //GtkWidget* image1;

  int i;
  for(i = 0; i < 30; i++)
  {

    GtkWidget* event_box = gtk_event_box_new();

    if(i % 2)
        image1 = gtk_image_new_from_file("ball_green.bmp");
    else
        image1 = gtk_image_new_from_file("ball_yellow.bmp");

    gtk_container_add(GTK_CONTAINER(event_box), image1);
    g_signal_connect(G_OBJECT(event_box), "button_press_event", 
      G_CALLBACK(image_press_cb), image1);

    gtk_container_add(GTK_CONTAINER(tile_vbox), event_box);
    //gtk_container_add(GTK_CONTAINER(tile_vbox), image1);
    gtk_widget_show (image1);       
    gtk_widget_show (event_box);       

  }

  gtk_builder_connect_signals (builder, NULL);          
  g_object_unref (G_OBJECT (builder));

  //gtk_drawing_area_size(drawingarea1, 600, 600);

  gtk_widget_show (window);       
  gtk_widget_show (tile_window);       
  gtk_widget_show (tile_vbox);       
  gtk_widget_show (map_edit_window.window);       

  gtk_main();

  FreeImage_DeInitialise();

  return 0;

}


