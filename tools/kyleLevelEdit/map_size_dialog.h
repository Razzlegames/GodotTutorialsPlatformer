/* vim: set filetype=cpp.doxygen : */
#ifndef MAP_SIZE_DIALOG_H
#define MAP_SIZE_DIALOG_H 

void init_map_size_dialog();
void error_dialog(const char* str);
gboolean cancel_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event );
gboolean commit_map_size_event( GtkWidget *widget, 
    GdkEventConfigure *event );

gboolean show_map_size_dialog_event( GtkWidget *widget, 
    GdkEventConfigure *event );

#endif /* MAP_SIZE_DIALOG_H */
