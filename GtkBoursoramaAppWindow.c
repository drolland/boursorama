#include <gtk/gtk.h>

#include "GtkBoursoramaApp.h"
#include "GtkBoursoramaAppWindow.h"
#include "GtkColoredCellRenderer.h"


struct _GtkBoursoramaAppWindow
{
  GtkApplicationWindow parent;
};


struct _GtkBoursoramaAppWindowClass
{
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(GtkBoursoramaAppWindow, gtk_boursorama_app_window, GTK_TYPE_APPLICATION_WINDOW);



enum
{
   TITLE_COLUMN,
   AUTHOR_COLUMN,
   CHECKED_COLUMN,
   N_COLUMNS
};

static void gtk_boursorama_app_window_init(GtkBoursoramaAppWindow *app){
    printf("App window init\n");
    
   GtkListStore *store;
   GtkWidget *tree;
   GtkTreeViewColumn *column;
   GtkColoredCellRenderer *colored_renderer;
   GtkCellRenderer *renderer;

   /* Create a model.  We are using the store model for now, though we
    * could use any other GtkTreeModel */
   store = gtk_list_store_new (N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_FLOAT,
                               G_TYPE_BOOLEAN);

   /* custom function to fill the model with data */
    GtkTreeIter   iter;

    gtk_list_store_append (store, &iter);  /* Acquire an iterator */

    gtk_list_store_set (store, &iter,
                    TITLE_COLUMN, "The Principle of Reason",
                    AUTHOR_COLUMN, 1.4f,
                    CHECKED_COLUMN, FALSE,
                    -1);

    gtk_list_store_append (store, &iter);  /* Acquire an iterator */

    gtk_list_store_set (store, &iter,
                    TITLE_COLUMN, "The Principle of Vice",
                    AUTHOR_COLUMN, 6.0f,
                    CHECKED_COLUMN, TRUE,
                    -1);
    
   /* Create a view */
   tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

   /* The view now holds a reference.  We can get rid of our own
    * reference */
   g_object_unref (G_OBJECT (store));

   /* Create a cell render and arbitrarily make it red for demonstration
    * purposes */
   colored_renderer = gtk_colored_cell_renderer_new ();
   g_object_set (G_OBJECT (renderer),
                 "foreground", "green",
                 NULL);

   /* Create a column, associating the "text" attribute of the
    * cell_renderer to the first column of the model */
   column = gtk_tree_view_column_new_with_attributes ("Author", GTK_CELL_RENDERER(colored_renderer),
                                                      "text", AUTHOR_COLUMN,
                                                      NULL);

   
   /* Add the column to the view. */
   gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

   /* Second column.. title of the book. */
   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes ("Title",
                                                      renderer,
                                                      "text", TITLE_COLUMN,
                                                      NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

   /* Last column.. whether a book is checked out. */
   renderer = gtk_cell_renderer_toggle_new ();
   column = gtk_tree_view_column_new_with_attributes ("Checked out",
                                                      renderer,
                                                      "active", CHECKED_COLUMN,
                                                      NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
   
   gtk_container_add(GTK_CONTAINER(app),GTK_WIDGET(tree));
   
   gtk_widget_set_visible(GTK_WIDGET(tree),TRUE);
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
