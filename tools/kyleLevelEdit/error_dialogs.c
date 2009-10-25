/* vim: set filetype=cpp.doxygen : */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdarg.h>
#include "error_dialogs.h"


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
