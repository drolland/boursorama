#include <gtk/gtk.h>

#include "GtkBoursoramaApp.h"
#include "GtkBoursoramaAppWindow.h"


struct _GtkBoursoramaAppWindow
{
  GtkApplicationWindow parent;
};


struct _GtkBoursoramaAppWindowClass
{
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(GtkBoursoramaAppWindow, gtk_boursorama_app_window, GTK_TYPE_APPLICATION_WINDOW);



static void gtk_boursorama_app_window_init(GtkBoursoramaAppWindow *app){
    printf("App window init\n");
}


static void
gtk_boursorama_app_window_class_init (GtkBoursoramaAppWindowClass *class)
{
}


GtkBoursoramaAppWindow * gtk_boursorama_app_window_new (GtkBoursoramaApp *app)
{
  return g_object_new (GTK_BOURSORAMA_TYPE_APP_WINDOW, "application", app, NULL);
}

void
gtk_boursorama_app_window_open (GtkBoursoramaAppWindow *win,
                         GFile            *file)
{
}
