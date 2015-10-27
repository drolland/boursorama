#pragma once 
#include <gtk/gtk.h>

struct _GtkBoursoramaActionWindow
{
  GtkWindow parent;
  
};


struct _GtkBoursoramaActionWindowClass
{
  GtkWindowClass parent_class;
  
};

#define GTK_BOURSORAMA_TYPE_ACTION_WINDOW gtk_boursorama_action_window_get_type ()
G_DECLARE_FINAL_TYPE(GtkBoursoramaActionWindow, gtk_boursorama_action_window, GTK_BOURSORAMA, ACTION_WINDOW, GtkWindow)

       
        
GtkBoursoramaActionWindow * gtk_boursorama_action_window_new(char* action_name);
