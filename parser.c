#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "action.h"
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
    for(int i = 0; i< strlen(str);i++)
        if ( str[i] == '.') str[i] =',';
    return atof(str);
}

gboolean parse_boursorama_action(Action* action, char* html) {

    assert(action != NULL);

    if (action->name != NULL) free(action->name);

    int offset = 0;

    
    
    advance_after(&offset, "<a itemprop=\"name\" title=\"", html);
    int start = offset;
    advance_after(&offset, "\"", html);
    int stop = offset - 1;

    action->name = strndup(html + start, stop - start);

    //printf("Action name : %s - ", action->name);
    
    advance_after(&offset,"<b>Cours</b>",html);
    advance_after(&offset,"<span class=\"cotation\">",html);
    start = offset;
    advance_after(&offset, " ", html);
    stop = offset - 1;
    
    char* cours_str = strndup(html + start, stop - start);
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
    
    char* variation_str = strndup(html + start, stop - start);
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

    action->name = strndup(html + start, stop - start);

    //printf("Action name : %s - ", action->name);
    
    if ( advance_after(&offset,"<td class=\"b12-tab-int b12-tab-bold\">Cours</td>",html) == FALSE ) return FALSE;
    if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
    start = offset;
    if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
    stop = offset - 1;
    
    char* cours_str = strndup(html + start, stop - start);
    action->cours = string_to_double(cours_str);
    free(cours_str);
    
    advance_after(&offset,"<td class=\"b12-tab-int b12-tab-bold\">Variation %</td>",html);
    if ( advance_after(&offset,">",html) == FALSE ) return FALSE;
    start = offset;
    if ( advance_after(&offset, "</td>", html) == FALSE ) return FALSE;
    stop = offset-1;
    
    char* variation_str = strndup(html + start, stop - start);
    action->variation = string_to_double(variation_str);
    //printf("variation %lf %\n",action->variation);
    free(variation_str);
    
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

    return url_list;
}




