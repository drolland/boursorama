#include <gtk/gtk.h>

#include "GtkBoursoramaApp.h"
#include "GtkBoursoramaAppWindow.h"


struct _GtkBoursoramaApp
{
  GtkApplication parent;
};


struct _GtkBoursoramaAppClass
{
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(GtkBoursoramaApp, gtk_boursorama_app, GTK_TYPE_APPLICATION);

static void
gtk_boursorama_app_init (GtkBoursoramaApp *app)
{
}

static void
gtk_boursorama_app_activate (GApplication *app)
{
  GtkBoursoramaAppWindow *win;

  win = gtk_boursorama_app_window_new (GTK_BOURSORAMA_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
gtk_boursorama_app_open (GApplication  *app,
                  GFile        **files,
                  gint           n_files,
                  const gchar   *hint)
{
  GList *windows;
  GtkBoursoramaAppWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = GTK_BOURSORAMA_APP_WINDOW (windows->data);
  else
    win = gtk_boursorama_app_window_new (GTK_BOURSORAMA_APP (app));

  for (i = 0; i < n_files; i++)
    gtk_boursorama_app_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void
gtk_boursorama_app_class_init (GtkBoursoramaAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = gtk_boursorama_app_activate;
  G_APPLICATION_CLASS (class)->open = gtk_boursorama_app_open;
}

GtkBoursoramaApp *
gtk_boursorama_app_new (void)
{
  return g_object_new (GTK_BOURSORAMA_TYPE_APP,
                       "application-id", "org.gtk.exampleapp",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
