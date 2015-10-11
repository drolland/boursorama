#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "download.h"
#include "GtkBoursoramaApp.h"
#include "parser.h"
#include <glib-2.0/glib.h>

int main(int argc,char** argv)
{
    
    
    
    curl_global_init( CURL_GLOBAL_ALL );

    GSList* url_list = NULL;
    GSList* response_list = NULL;
    char* url = "http://www.boursorama.com/cours.phtml?symbole=1rPEDF";
    
    for(int i = 0; i < 1; i++){
        url_list = g_slist_append(url_list,url);
    }
    
    http_parallel_get(&response_list,url_list);
    
    ResponseBuffer* response = response_list->data;
    parse_ordres_boursorama(response->buffer);
    
    printf("LibCurl rules!\n");

    g_application_run (G_APPLICATION (gtk_boursorama_app_new ()), argc, argv);
    
    return 0;
}


