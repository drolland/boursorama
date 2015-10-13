#pragma once
#include "action.h"
#include <glib-2.0/glib.h>

void parse_boursorama_action(Action* action,char* html);
GSList* parse_boursorama_action_multi(GSList* response_list);
GSList* parse_boursorame_conf(char* file);