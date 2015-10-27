#pragma once
#include "Action.h"
#include <glib-2.0/glib.h>


GSList* parse_boursorama_action_multi(GSList* response_list);
GSList* parse_lesechos_action_multi(GSList* response_list);
GSList* parse_boursorame_conf(char* file);