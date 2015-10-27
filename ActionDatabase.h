#pragma once
#include "Action.h"

typedef struct _action_database ActionDatabase;



        
ActionDatabase* action_database_get();        

/* WARNING NO MUTEX LOCK*/
void action_database_insert(ActionDatabase* database,Action* action);

void action_database_insert_many(ActionDatabase* database,GSList* action_list);

GSList* action_database_lookup(ActionDatabase* database,char* action);