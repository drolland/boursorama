#include <stdlib.h>
#include "GtkColoredCellRenderer.h"


struct _GtkColoredCellRendererClass {
    GtkCellRendererTextClass parent_class;
    void (*oldrender) (GtkCellRenderer *cell,
            cairo_t *cr,
            GtkWidget *widget,
            const GdkRectangle *background_area,
            const GdkRectangle *cell_area,
            GtkCellRendererState flags);
};

G_DEFINE_TYPE(GtkColoredCellRenderer, gtk_colored_cell_renderer, GTK_TYPE_CELL_RENDERER_TEXT);

static void gtk_colored_cell_renderer_init(GtkColoredCellRenderer *app) {

}

void custom_render (GtkCellRenderer *cell,cairo_t *cr,GtkWidget *widget,const GdkRectangle *background_area,const GdkRectangle *cell_area,GtkCellRendererState flags){
    
    gchar* value;
    g_object_get(G_OBJECT(cell),"text",&value,NULL);
    float float_value = atof(value);
    g_free(value);

    char format_string[100];
    sprintf(format_string,"%10.2f",float_value);
    g_object_set(G_OBJECT(cell),"text",format_string,NULL);

    
    if ( float_value >= 0.0)
        g_object_set(G_OBJECT(cell),"foreground","green",NULL);
    else
        g_object_set(G_OBJECT(cell),"foreground","red",NULL);
    
 
    GtkColoredCellRendererClass* class = (GtkColoredCellRendererClass*)cell->parent_instance.g_type_instance.g_class;
    class->oldrender(cell,cr,widget,background_area,cell_area,flags);
    
}


static void gtk_colored_cell_renderer_class_init(GtkColoredCellRendererClass *class) {
    
    class->oldrender = class->parent_class.parent_class.render;
    class->parent_class.parent_class.render = custom_render;
    
}

GtkColoredCellRenderer * gtk_colored_cell_renderer_new (void)
{
  return g_object_new (GTK_COLORED_CELL_RENDERER_TYPE,NULL);
}