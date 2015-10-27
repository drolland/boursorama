#include <gtk/gtk.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtkwindow.h>
#include "GtkBoursoramaApp.h"
#include "GtkBoursoramaAppWindow.h"
#include "GtkColoredCellRenderer.h"
#include "Action.h"
#include "GtkBoursoramaActionWindow.h"


G_DEFINE_TYPE(GtkBoursoramaAppWindow, gtk_boursorama_app_window, GTK_TYPE_APPLICATION_WINDOW);


void cell_cours_action_format(GtkTreeViewColumn *tree_column,GtkCellRenderer *cell,GtkTreeModel *tree_model,GtkTreeIter *iter,gpointer data){
    
    double float_value;  
    gtk_tree_model_get(tree_model,iter,ACTION_COURS,&float_value,-1);
    char format_string[100];
    sprintf(format_string,"%10.2f €",float_value);
    g_object_set(G_OBJECT(cell),"text",format_string,NULL);

}

void cell_variation_action_format(GtkTreeViewColumn *tree_column,GtkCellRenderer *cell,GtkTreeModel *tree_model,GtkTreeIter *iter,gpointer data){
    
    double float_value;  
    gtk_tree_model_get(tree_model,iter,ACTION_VARIATION,&float_value,-1);
    char format_string[100];
    sprintf(format_string,"%10.2f %%",float_value);
    g_object_set(G_OBJECT(cell),"text",format_string,NULL);
    
    if ( float_value >= 0.0)
        g_object_set(G_OBJECT(cell),"foreground","green",NULL);
    else
        g_object_set(G_OBJECT(cell),"foreground","red",NULL);

}

void cell_stardux_action_format(GtkTreeViewColumn *tree_column,GtkCellRenderer *cell,GtkTreeModel *tree_model,GtkTreeIter *iter,gpointer data){
    
    double float_value;  
    gtk_tree_model_get(tree_model,iter,ACTION_STARDUX,&float_value,-1);
    char format_string[100];
    int int_value = float_value;
    sprintf(format_string,"%d €",int_value);
    g_object_set(G_OBJECT(cell),"text",format_string,NULL);
    
    if ( float_value >= 0.0)
        g_object_set(G_OBJECT(cell),"foreground","green",NULL);
    else
        g_object_set(G_OBJECT(cell),"foreground","red",NULL);

}

gboolean no_row_selection_func(GtkTreeSelection *selection,GtkTreeModel *model,GtkTreePath *path,gboolean path_currently_selected,gpointer data){
    
    GtkTreeIter iter;
    gtk_tree_model_get_iter(model,&iter,path);
    char* str; 
    gtk_tree_model_get(model,&iter,ACTION_NAME,&str,-1);
    
    printf("Row %s selected\n",str);
    g_free(str);
    return FALSE; // False forbid row selection
}

void on_row_activated(GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn *col,gpointer userdata){
    GtkTreeModel *model;
    GtkTreeIter   iter;

    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
       gchar *action_name;

       gtk_tree_model_get(model, &iter, ACTION_NAME, &action_name, -1);

       GtkBoursoramaActionWindow* action_window = gtk_boursorama_action_window_new(action_name);
       gtk_window_present((GTK_WINDOW(action_window)));

       g_free(action_name);
    }
  }


static void gtk_boursorama_app_window_init(GtkBoursoramaAppWindow *app){
       
   
   GtkTreeViewColumn *column;
   GtkCellRenderer *renderer;
   GtkWidget *h_box;
   GtkWidget* scrolled_window;
   
   /* Create a model.  We are using the store model for now, though we
    * could use any other GtkTreeModel */
   
   
   gtk_window_set_title(GTK_WINDOW(app),"STARDUX");

   /* Create a view */
   app->tree = GTK_TREE_VIEW(gtk_tree_view_new ());
   
   
   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes ("Nom Action",renderer,"text", ACTION_NAME,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (app->tree), column);
   gtk_tree_view_column_set_sort_column_id(column,ACTION_NAME);
   
   
   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes ("Cours", renderer,"text", ACTION_COURS,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (app->tree), column);
   gtk_tree_view_column_set_cell_data_func(column,renderer,cell_cours_action_format, NULL,NULL);
   
   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes ("Variation",GTK_CELL_RENDERER(renderer),"text",ACTION_VARIATION,NULL);
   gtk_tree_view_column_set_cell_data_func(column,renderer,cell_variation_action_format, NULL,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (app->tree), column);
   gtk_tree_view_column_set_sort_column_id(column,ACTION_VARIATION);
   
   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes ("STARDUX",GTK_CELL_RENDERER(renderer),"text",ACTION_STARDUX,NULL);
   gtk_tree_view_column_set_cell_data_func(column,renderer,cell_stardux_action_format, NULL,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW (app->tree), column);
   gtk_tree_view_column_set_sort_column_id(column,ACTION_STARDUX);
   
   GtkTreeSelection* tree_selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (app->tree));
   gtk_tree_selection_set_select_function(tree_selection,no_row_selection_func,NULL,NULL);
   g_signal_connect(GTK_WIDGET(app->tree), "row-activated", (GCallback) on_row_activated, NULL);
   gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (app->tree),FALSE);
   
   app->update_label = gtk_label_new("Derniere mise à jour il y a : ");
   
   
   h_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
   gtk_container_add(GTK_CONTAINER(app),GTK_WIDGET(h_box));  
   
   scrolled_window = gtk_scrolled_window_new(NULL,NULL);
   gtk_container_add(GTK_CONTAINER(scrolled_window),GTK_WIDGET(app->tree));
   
   gtk_box_pack_start(GTK_BOX(h_box),GTK_WIDGET(scrolled_window),TRUE,TRUE,0);
   gtk_box_pack_start(GTK_BOX(h_box),GTK_WIDGET(app->update_label),FALSE,FALSE,0);
   
   gtk_widget_set_visible(GTK_WIDGET(h_box),TRUE);
   gtk_widget_set_visible(GTK_WIDGET(scrolled_window),TRUE);
   gtk_widget_set_visible(GTK_WIDGET(app->tree),TRUE);
   gtk_widget_set_visible(GTK_WIDGET(app->update_label),TRUE);
   
    

   
 
}

void gtk_boursorama_app_window_finalize(GObject* object){
    GtkBoursoramaAppWindow* app_window = (GtkBoursoramaAppWindow*) object;
    GObject* o = (GObject*)app_window->tree;
    printf("Tree ref count %d",o->ref_count);
    o = (GObject*)app_window->update_label;
    printf("Label ref count %d",o->ref_count);
    //gtk_widget_destroy(app_window->);
    
    
}


static void
gtk_boursorama_app_window_class_init (GtkBoursoramaAppWindowClass *class)
{
    GObjectClass* object_class = (GObjectClass*) class;
    //object_class->finalize = gtk_boursorama_app_window_finalize;
}





GtkBoursoramaAppWindow * gtk_boursorama_app_window_new (GtkBoursoramaApp *app)
{
  return g_object_new (GTK_BOURSORAMA_TYPE_APP_WINDOW, "application", app, NULL);
}




    
    
   
    
     
 