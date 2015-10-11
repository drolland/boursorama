#pragma once 
#include <gtk/gtk.h>

#define GTK_BOURSORAMA_TYPE_APP gtk_boursorama_app_get_type ()
G_DECLARE_FINAL_TYPE (GtkBoursoramaApp, gtk_boursorama_app, GTK_BOURSORAMA, APP, GtkApplicationWindow)
        
GtkBoursoramaApp * gtk_boursorama_app_new (void);
