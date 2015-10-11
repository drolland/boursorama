#pragma once 
#include <gtk/gtk.h>

#define GTK_BOURSORAMA_TYPE_APP_WINDOW gtk_boursorama_app_window_get_type ()
G_DECLARE_FINAL_TYPE(GtkBoursoramaAppWindow, gtk_boursorama_app_window, GTK_BOURSORAMA, APP_WINDOW, GtkApplicationWindow)

GtkBoursoramaAppWindow * gtk_boursorama_app_window_new(GtkBoursoramaApp *app);
void gtk_boursorama_app_window_open(GtkBoursoramaAppWindow *win,GFile *file);