#include "Action.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Action* action_new(){
    Action* act = malloc(sizeof(Action));
    act->name = NULL;
    act->cours = 0;
    act->variation = 0;
    return act;
}



void action_free(Action* act){
    free(act->name);
    free(act);   
}

void action_list_free(GSList* actions_list){
    
    GSList* iter = actions_list;
    
    while(iter != NULL){
        action_free(iter->data);
        iter = g_slist_next(iter);
    }
    
    g_slist_free(actions_list);
}

void action_print(Action* action){
    printf("Action : %s\n", action->name);


    printf("Cours %f  |  Variation %f\n",action->cours,action->variation);
    printf("Carnet d'ordre achat \n");
    for(int i = 0; i < 5;i++){
        printf("Q = %d  -  Prix %f\n",action->achat.quantite[i],action->achat.prix[i]);
    }
    printf("Carnet d'ordre vente \n");
    for(int i = 0; i < 5;i++){
        printf("Q = %d  -  Prix %f\n",action->vente.quantite[i],action->vente.prix[i]);
    }
    printf("STARDUX %f \n",action->stardux);

    printf("Time : %ld\n",action->time);

}

gpointer action_copy(gconstpointer action,gpointer for_signature){
    Action* copy = (Action*)malloc(sizeof(Action));
    memcpy(copy ,action ,sizeof(Action));
    copy->name = strdup(((Action*)action)->name);
    return copy;    
}

void action_list_print(GSList* action_list){
    GSList* iter = action_list;
    while(iter!=NULL){
        action_print(iter->data);
        iter = g_slist_next(iter);
    }
}

GSList* action_list_copy(GSList* action_list){
    return g_slist_copy_deep(action_list,action_copy,NULL);    
}

gint action_name_cmp(gconstpointer a,gconstpointer b){
    return strcmp( ((Action*)a)->name, b);
}

Action* action_list_get_by_name_and_remove(GSList** action_list,char* name){
    
    GSList* result = g_slist_find_custom(*action_list,name,action_name_cmp);
    if ( result == NULL)
        return NULL;
    Action* action = result->data;
    
    GSList* new_action_list = g_slist_delete_link (*action_list,result);
    *action_list = new_action_list;
    
    return action;
    
}