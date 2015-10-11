#pragma once 
#include <gtk/gtk.h>

#define GTK_COLORED_CELL_RENDERER_TYPE gtk_colored_cell_renderer_get_type ()
G_DECLARE_DERIVABLE_TYPE (GtkColoredCellRenderer, gtk_colored_cell_renderer, GTK, COLORED_CELL_RENDERER, GtkCellRendererText)
        
GtkColoredCellRenderer * gtk_colored_cell_renderer_new (void);

