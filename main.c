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
   
    int count = 0;
    
    
    printf("LibCurl rules!\n");

    g_application_run (G_APPLICATION (gtk_boursorama_app_new ()), argc, argv);
    
    return 0;
}


