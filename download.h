#pragma once
#include <glib-2.0/glib.h>

typedef struct s_response_buffer {
    char buffer[1000000];
    int offset;
} ResponseBuffer;

int http_get(ResponseBuffer** response, char* url);
int http_parallel_get(GSList** response_list, GSList* url_list);
int http_parallel_get_multi(GSList** response_list, GSList* url_list);