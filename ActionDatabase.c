#include "ActionDatabase.h"
#include "Action.h"
#include <stdlib.h>
#include <glib-2.0/glib.h>


typedef struct _action_database {
   GHashTable*  hash_table;
   GMutex mutex;
} ActionDatabase;

ActionDatabase* g_action_database = NULL;

ActionDatabase* action_database_get(){
    if ( g_action_database == NULL){
        g_action_database = malloc(sizeof(ActionDatabase));
        g_action_database->hash_table = g_hash_table_new(g_str_hash,g_str_equal);
        g_mutex_init(&(g_action_database->mutex));
    }
    return g_action_database;    
}

void action_database_insert(ActionDatabase* database,Action* action){
    GSList* list = g_hash_table_lookup(database->hash_table,action->name);
    list = g_slist_insert_before(list,list,action);
    GSList* cut = g_slist_nth(list,8000);
    if ( cut!= NULL && cut->next != NULL){
        GSList* after_cut = g_slist_next(cut);
        action_list_free(after_cut);
        cut->next = NULL;        
    }
    
    g_hash_table_replace(database->hash_table,action->name,list);
}

void action_database_insert_many(ActionDatabase* database,GSList* action_list){
    g_mutex_lock(&(database->mutex));
    GSList* iter= action_list;
    while(iter != NULL){
        action_database_insert(database,iter->data);
        iter = g_slist_next(iter);
    }    
    g_mutex_unlock(&(database->mutex));
}


GSList* action_database_lookup(ActionDatabase* database,char* name){
    g_mutex_lock(&(database->mutex));
    GSList* result = g_hash_table_lookup(database->hash_table,name);
    g_mutex_unlock(&(database->mutex));
    return result;
}