#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Action.h"
#include "download.h"
#include <assert.h>
#include <glib-2.0/glib/gerror.h>

gboolean advance_after(int* offset, char* string, char* html) {
    char* ptr = string;
    while (1) {
        if ( html[*offset] == '\0' ) return FALSE;
        if (html[*offset] == *ptr) {
            ptr++;
            if (*ptr == '\0') {
                (*offset)++;
                break;
            }
        } else {
            ptr = string;
        }
        (*offset)++;
    }
    return TRUE;
}


double string_to_double(char* str){
    int len = strlen(str);
    for(int i = 0; i< len;i++)
        if ( str[i] == '.') str[i] =',';
    return atof(str);
}

char* lesechos_strip_ordre_quantite_string(char* str){
    char* buff = malloc(sizeof(char) * strlen(str) );
    char* ret = buff;
    char* iter = str;
    while(*iter != '\0'){
        if ( *iter != ' ' && *iter !='\t' && *iter != '\n' && *iter != '\r' && *iter != -96){
            *ret = *iter;
            ret++;
        }
        iter++;
    }
    *ret = '\0';
    return buff;
}

gboolean parse_boursorama_action(Action* action, char* html) {

    assert(action != NULL);

    if (action->name != NULL) free(action->name);

    int offset = 0;

    
    
    advance_after(&offset, "<a itemprop=\"name\" title=\"", html);
    int start = offset;
    advance_after(&offset, "\"", html);
    int stop = offset - 1;

    action->name = g_strndup(html + start, stop - start);

    //printf("Action name : %s - ", action->name);
    
    advance_after(&offset,"<b>Cours</b>",html);
    advance_after(&offset,"<span class=\"cotation\">",html);
    start = offset;
    advance_after(&offset, " ", html);
    stop = offset - 1;
    
    char* cours_str = g_strndup(html + start, stop - start);
    action->cours = string_to_double(cours_str);
    //printf("cours euronext %s EUR - ",cours_str);
    //printf("cours euronext %f EUR - ",action->cours);
    free(cours_str);
    
    advance_after(&offset,"Variation",html);
    advance_after(&offset,"<span id",html);
    advance_after(&offset,"\">",html);
    start = offset;
    advance_after(&offset,"%",html);
    stop = offset-1;
    
    char* variation_str = g_strndup(html + start, stop - start);
    action->variation = string_to_double(variation_str);
    //printf("variation %lf %\n",action->variation);
    free(variation_str);


    
    /*
        advance_after(&offset,">Achat",html);
        advance_after(&offset,"<td",html);
        advance_after(&offset,"<td",html);
    
        advance_after(&offset,">",html);
        advance_after(&offset,">",html);
    
        advance_after(&offset,"<",html);
        int stop = offset - 1;

    
        char* quantite_ordre = 
        printf("quantite ordres %d\n",atoi(quantite_ordre));
        free(quantite_ordre);

     */
}

gboolean parse_lesechos_action(Action *action ,char* html){
    
    assert(action != NULL);

    if (action->name != NULL) free(action->name);

    int offset = 0;

    if ( advance_after(&offset, "<title>Cours action ", html) == FALSE ) return FALSE;
    int start = offset;
    if ( advance_after(&offset, " ", html) == FALSE ) return FALSE;
    int stop = offset - 1;

    action->name = g_strndup(html + start, stop - start);

    //printf("Action name : %s - ", action->name);
    
    if ( advance_after(&offset,"<td class=\"b12-tab-int b12-tab-bold\">Cours</td>",html) == FALSE ) return FALSE;
    if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
    start = offset;
    if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
    stop = offset - 1;
    
    char* cours_str = g_strndup(html + start, stop - start);
    action->cours = string_to_double(cours_str);
    free(cours_str);
    
    advance_after(&offset,"<td class=\"b12-tab-int b12-tab-bold\">Variation %</td>",html);
    if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
    start = offset;
    if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
    stop = offset-1;
    
    char* variation_str = g_strndup(html + start, stop - start);
    action->variation = string_to_double(variation_str);
    //printf("variation %lf %\n",action->variation);
    free(variation_str);
    
     offset = 0;
    for(int i = 0; i < 5; i++){
   
        if ( advance_after(&offset,"<tr data-item=\"ordreachat\"",html) == FALSE ) return FALSE;
        
        if ( advance_after(&offset,"<td data-field=\"quantity\"",html) == FALSE ) return FALSE;
        if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
        start = offset;
        if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
        stop = offset-1;
        char* buff = g_strndup(html + start, stop - start);
        char* striped = lesechos_strip_ordre_quantite_string(buff);
/*
        printf("striped:%s\n",striped);
        int j = 0;
        while( striped[j] != '\0'){
            printf("striped[%d] = %d\n",j,striped[j]);
            j++;
        }
*/
        action->achat.quantite[i] = string_to_double(striped);
        free(striped);
        free(buff);
        if ( advance_after(&offset,"<td data-field=\"price\"",html) == FALSE ) return FALSE;
        if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
        start = offset;
        if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
        stop = offset-1;
        buff = g_strndup(html + start, stop - start);
        action->achat.prix[i] = string_to_double(buff);
        free(buff);
    }
     
     for(int i = 0; i < 5; i++){
   
        if ( advance_after(&offset,"<tr data-item=\"ordrevente\"",html) == FALSE ) return FALSE;
        
        if ( advance_after(&offset,"<td data-field=\"price\"",html) == FALSE ) return FALSE;
        if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
        start = offset;
        if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
        stop = offset-1;
        char* buff = g_strndup(html + start, stop - start);
        action->vente.prix[i] = string_to_double(buff);
        free(buff);
        
        if ( advance_after(&offset,"<td data-field=\"quantity\"",html) == FALSE ) return FALSE;
        if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
        start = offset;
        if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
        stop = offset-1;
        buff = g_strndup(html + start, stop - start);
        char* striped = lesechos_strip_ordre_quantite_string(buff);
/*
        printf("striped:%s\n",striped);
        int j = 0;
        while( striped[j] != '\0'){
            printf("striped[%d] = %d\n",j,striped[j]);
            j++;
        }
*/
        action->vente.quantite[i] = string_to_double(striped);
        free(striped);
        free(buff);
        
    }
     
     /* Compute stardux */
     double stardux = 0;
     for(int i = 0;i < 5;i++){
         stardux += action->achat.quantite[i] * action->achat.prix[i] - action->vente.quantite[i] * action->vente.prix[i];
    }
    
    action->stardux = stardux;
    action->time = g_get_real_time();
    //action_print(action);
    
    return TRUE;
}

GSList* parse_boursorama_action_multi(GSList* response_list){
    
    GSList* current = response_list;
    GSList* action_list = NULL; 
    while ( current != NULL ){
        Action* act = action_new();
        gboolean success = parse_boursorama_action(act,((ResponseBuffer*)current->data)->buffer);
        if ( success == TRUE)
        action_list = g_slist_append(action_list,act); 
        else
            action_free(act);
        current = current->next;
    } 
    
    return action_list;
}

GSList* parse_lesechos_action_multi(GSList* response_list){
    
    GSList* current = response_list;
    GSList* action_list = NULL; 
    while ( current != NULL ){
        Action* act = action_new();
        gboolean success = parse_lesechos_action(act,((ResponseBuffer*)current->data)->buffer);
        if ( success == TRUE)
        action_list = g_slist_append(action_list,act); 
        else
            action_free(act);
        current = current->next;
    } 
    
    return action_list;
}

GSList* parse_boursorame_conf(char* file) {


    GError* error = NULL;
    GIOChannel* channel = g_io_channel_new_file(file, "r", &error);

    if (error) {
        printf("Error : parse_boursorama_conf -> %s\n", error->message);
    }

    GSList* url_list = NULL;
    char* buffer;
    while (g_io_channel_read_line(channel, &buffer, NULL, NULL, &error) != G_IO_STATUS_EOF) {
        char** splited = g_strsplit_set(buffer, " \n", 6);
        int url_key_present = FALSE;
        int i = 0;
        while (splited[i] != NULL) {
            if ( strlen(splited[i]) > 0) {
                char* url = strdup(splited[i]);
                url_list = g_slist_append(url_list, url);
                //printf("%s\n", url);
            }
            i++;
        }
        g_free(buffer);
        g_strfreev(splited);
    }
    
    g_io_channel_shutdown(channel,TRUE,NULL);
    g_io_channel_unref(channel);

    return url_list;
}




