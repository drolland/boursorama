#pragma once
#include <glib-2.0/glib.h>

typedef struct _action {
    char* name;
    double cours;    
    double variation;
} Action ;

Action* action_new();

void action_free(Action* act);

void action_list_free(GSList* actions_list);

GSList* action_list_copy(GSList* action_list);

Action* action_list_get_by_name_and_remove(GSList** action_list,char* name);
