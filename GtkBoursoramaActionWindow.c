#include <gtk/gtk.h>
#include <gtk-3.0/gtk/gtkwindow.h>
#include <gtk-3.0/gtk/gtktypes.h>
#include <gtk-3.0/gdk/gdkevents.h>
#include <glib-2.0/glib/gtypes.h>
#include <glib-2.0/gobject/gsignal.h>
#include <glib-2.0/gobject/gclosure.h>
#include <gtk-3.0/gtk/gtkwidget.h>
#include <glib-2.0/glib/gslist.h>
#include <string.h>
#include <cairo/cairo.h>
#include <glib-2.0/glib/gmain.h>
#include "GtkBoursoramaActionWindow.h"
#include "ActionDatabase.h"

G_DEFINE_TYPE(GtkBoursoramaActionWindow, gtk_boursorama_action_window, GTK_TYPE_WINDOW);

GSList* action_window_opened_list = NULL;


double color = 0;

gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);
  
  int text_up_y = height / 10;
  int text_down_y = height * 9 / 10;
  
  cairo_set_line_width(cr,2);
  cairo_set_source_rgb(cr,0,0,0);
  cairo_move_to(cr,0,height/2);
  cairo_line_to(cr,width,height/2);
  cairo_stroke (cr);
  
  cairo_set_line_width(cr,1);
  cairo_move_to(cr,0,text_up_y);
  cairo_line_to(cr,width,text_up_y);
  cairo_move_to(cr,0,text_down_y);
  cairo_line_to(cr,width,text_down_y);
  cairo_stroke(cr);
  
  cairo_set_font_size(cr,30);
  
  cairo_move_to(cr,0,text_up_y);
  cairo_select_font_face(cr,"cairo :monospace",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL); 
  cairo_text_path(cr,"+ 5M €");
  
  cairo_text_extents_t text_extent;
  cairo_text_extents(cr,"- 5M €",&text_extent);
  cairo_move_to(cr,0,text_down_y - text_extent.y_bearing);
  cairo_text_path(cr,"- 5M €");
  
  cairo_fill (cr);
  
  gint64 time_now = g_get_real_time();
  const char* action_name = gtk_window_get_title(GTK_WINDOW(data));
  ActionDatabase* database = action_database_get();
  GSList* action_list = action_database_lookup(database,(char*)action_name);
  
  GSList* iter = action_list;
  gint64 last_time = time_now;
  gint64 last_value = 0;
  double factor_x = (double)width / 60000000.0f / 60.0f;
  double factor_y = ((double)height * 4.0f / 10.0f) / 5000000.0f;
  cairo_set_source_rgb(cr,1,0,0);
  while(iter != NULL){
      Action* action = iter->data;
      gint64 total_time_in_us = 60000000 * 1;
      total_time_in_us *= 60;
      if ( action->time - time_now > total_time_in_us){
          break;
      }
      //printf("Pixel x = %f, y = %f",)
      if ( action->stardux > 0){
          cairo_set_source_rgb(cr,0,0.7,0.3);
      }
      else
          cairo_set_source_rgb(cr,0.7,0,0.3);
      cairo_move_to(cr,width - (time_now - last_time) * factor_x,height/2 - action->stardux * factor_y);
      cairo_line_to(cr,width - (time_now - action->time) * factor_x,height/2 - action->stardux * factor_y);
      cairo_line_to(cr,width - (time_now - action->time) * factor_x,height/2);
      cairo_line_to(cr,width - (time_now - last_time) * factor_x,height/2);
      cairo_close_path(cr);
      cairo_fill(cr);
      
      last_time = action->time;
      iter = g_slist_next(iter);
  }
  
   
 return FALSE;
}

static void
gtk_boursorama_action_window_init (GtkBoursoramaActionWindow *window)
{
  GtkWidget *drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (drawing_area, 400, 400);
  g_signal_connect (G_OBJECT (drawing_area), "draw",
                    G_CALLBACK (draw_callback), window);
  gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(drawing_area));
  gtk_widget_set_visible(GTK_WIDGET(drawing_area),TRUE);
}

gboolean gtk_boursorama_action_window_update(gpointer data) {
       
    GSList* iter = action_window_opened_list;
    
    while ( iter != NULL){
        GtkBoursoramaActionWindow* action_window = iter->data;
        //printf("iter : %s\n",gtk_window_get_title(GTK_WINDOW(action_window)));
        gtk_widget_queue_draw((GTK_WIDGET(action_window)));
        iter = g_slist_next(iter);
    }
    
    color += 0.01;
    if ( color > 1.0f) color = 0.0f;
    
    return TRUE;

}

static void
gtk_boursorama_action_window_class_init (GtkBoursoramaActionWindowClass *window_class)
{
    g_timeout_add(1000, gtk_boursorama_action_window_update, NULL);
    
    
}


void gtk_boursorama_action_window_on_delete(GtkWidget* widget, GdkEvent* event, gpointer userdata){
    const char* action_name = gtk_window_get_title(GTK_WINDOW(widget));
    printf("Delete : %s\n",action_name);
    action_window_opened_list = g_slist_remove(action_window_opened_list,widget);
    gtk_widget_destroy(GTK_WIDGET(widget));
    
}

gint action_window_cmp(gconstpointer a,gconstpointer b){
    const char* title = gtk_window_get_title(GTK_WINDOW(a));
    return strcmp( title, b);
}

GtkBoursoramaActionWindow * gtk_boursorama_action_window_new (char* action_name)
{
  GSList* w = g_slist_find_custom(action_window_opened_list,action_name,action_window_cmp);
  GtkBoursoramaActionWindow* window = NULL;
  if ( w != NULL){
      window = w->data;
  }
  else {
  window = g_object_new (GTK_BOURSORAMA_TYPE_ACTION_WINDOW,NULL);
  gtk_window_set_title(GTK_WINDOW(window),action_name);
  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_boursorama_action_window_on_delete),NULL);
  action_window_opened_list = g_slist_append(action_window_opened_list,window);
  }
  return window;
}


