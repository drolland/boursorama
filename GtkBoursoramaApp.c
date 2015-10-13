#include <gtk/gtk.h>
#include "parser.h"
#include "download.h"

#include "GtkBoursoramaApp.h"
#include "GtkBoursoramaAppWindow.h"


struct _GtkBoursoramaApp
{
  GtkApplication parent;
  GtkBoursoramaAppWindow *win;
  GSList* action_list;
  GMutex mutex_action_list;
  GtkListStore* list_store_action_list;
};


struct _GtkBoursoramaAppClass
{
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(GtkBoursoramaApp, gtk_boursorama_app, GTK_TYPE_APPLICATION);

gboolean gtk_boursorama_app_update_gui(gpointer data);


gpointer app_logic_thread_func(gpointer data){
    
    int count = 0;
    GtkBoursoramaApp* app = data;
    GtkBoursoramaAppWindow* win = app->win;
    
    while(1){
    GSList* url_list = NULL;
    GSList* response_list = NULL;
    
    url_list = parse_boursorame_conf("boursorama.conf");  
    http_parallel_get(&response_list,url_list);
    
    g_mutex_lock(&(app->mutex_action_list));
    action_list_free(app->action_list);
    app->action_list = NULL;
    app->action_list = parse_boursorama_action_multi(response_list);
    g_mutex_unlock(&(app->mutex_action_list));
        
    g_slist_free_full(url_list,g_free);
    g_slist_free_full(response_list,g_free);
      
    count++;
    printf("Done %d loops\n",count);
    
    g_idle_add(gtk_boursorama_app_update_gui,app);
        
    }
    
    
}

static void
gtk_boursorama_app_init (GtkBoursoramaApp *app)
{
    g_mutex_init(&(app->mutex_action_list));
    app->action_list = NULL;
    app->list_store_action_list = gtk_list_store_new (N_COLUMNS,G_TYPE_STRING,G_TYPE_DOUBLE,G_TYPE_DOUBLE);
   
    
}

static void
gtk_boursorama_app_activate (GApplication *application)
{
  GtkBoursoramaApp* app = (GtkBoursoramaApp*)application;
  app->win = gtk_boursorama_app_window_new (GTK_BOURSORAMA_APP (app));
  app->win->tree_model_sort = gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(app->list_store_action_list));
  gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(app->win->tree_model_sort),ACTION_NAME,GTK_SORT_ASCENDING);
  gtk_tree_view_set_model(app->win->tree,GTK_TREE_MODEL(app->win->tree_model_sort));
  gtk_window_present (GTK_WINDOW (app->win));
  
  g_thread_new("http thread",app_logic_thread_func,app);
  
}

static void
gtk_boursorama_app_open (GApplication  *app,
                  GFile        **files,
                  gint           n_files,
                  const gchar   *hint)
{
  GList *windows;
  GtkBoursoramaAppWindow *win = ((GtkBoursoramaApp*)app)->win;
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
                       "application-id", "org.gtk.stardux",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}


gboolean gtk_boursorama_app_update_gui(gpointer data){
    
    GtkBoursoramaApp* app = data;
    
    g_mutex_lock(&(app->mutex_action_list));
    if ( app->action_list == NULL) return FALSE;
    GSList* action_list = action_list_copy(app->action_list);
    printf("Action list length = %d\n",g_slist_length(action_list));
    g_mutex_unlock(&(app->mutex_action_list));
    
    
    int iter_is_valid = FALSE;
    
    
    char* row_name;
    
/*
    GtkTreeModel* model = gtk_tree_view_get_model(GTK_TREE_VIEW(app->win->tree));
    
    g_object_ref(model);
    
    gtk_tree_view_set_model(app->win->tree,NULL);
*/

    int count = 0;
    
    GtkTreeIter   iter;
    iter_is_valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->list_store_action_list),&iter);
    while(iter_is_valid){
        
        gtk_tree_model_get(GTK_TREE_MODEL(app->list_store_action_list),&iter,ACTION_NAME,&row_name,-1);
        
        
        Action* action = action_list_get_by_name_and_remove(&action_list,row_name);
        
        printf("Found iter for %s\n",action->name);

        
        gtk_list_store_set (app->list_store_action_list, &iter,
                ACTION_NAME, action->name,
                ACTION_COURS,action->cours,
                ACTION_VARIATION,action->variation,
                    -1);
        
        iter_is_valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(app->list_store_action_list),&iter);
        count++;
        
        g_free(row_name);
    }
    printf("updated %d rows\n",count);
    
    GSList* action_list_iter = action_list;
    
    while ( action_list_iter != NULL){
        
        gtk_list_store_append(app->list_store_action_list, &iter);
        gtk_list_store_set (app->list_store_action_list, &iter,
                ACTION_NAME, ((Action*)action_list_iter->data)->name,
                ACTION_COURS,((Action*)action_list_iter->data)->cours,
                ACTION_VARIATION,((Action*)action_list_iter->data)->variation,
                    -1);
        
        printf("Creating new row for %s\n",((Action*)action_list_iter->data)->name);
        action_list_iter = g_slist_next(action_list_iter);
    }
    
    
/*
    gtk_tree_view_set_model(app->win->tree,model);
    
    g_object_unref(model);
*/
    
    action_list_free(action_list);
    printf("GUI updated\n");
    return FALSE;
}
