#include <string.h>
#include <stdlib.h>
#include "download.h"
//#include "curl/curl.h"
#include <curl/curl.h>
#include <glib-2.0/glib.h>
#include <assert.h>
#include <unistd.h>

/* the function to invoke as the data recieved */
size_t static write_callback_func(void *buffer,
        size_t size,
        size_t nmemb,
        void *userp) {
    ResponseBuffer *response_ptr = (ResponseBuffer*) userp;
    strncpy(response_ptr->buffer + response_ptr->offset, buffer, size * nmemb);
    response_ptr->offset += size * nmemb;
    return ((size_t) (size * nmemb));
}

int http_get(ResponseBuffer** response, char* url) {

    *response = (ResponseBuffer*) malloc(sizeof (ResponseBuffer));
    (*response)->offset = 0;

    CURL * myHandle;
    CURLcode result; // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
    myHandle = curl_easy_init();

    // Notice the lack of major error checking, for brevity
    curl_easy_setopt(myHandle, CURLOPT_URL, url);
    /* setting a callback function to return the data */
    curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, write_callback_func);

    /* passing the pointer to the response as the callback parameter */
    curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, *response);

    result = curl_easy_perform(myHandle);

    curl_easy_cleanup(myHandle);
}

GMutex count_mutex;

void http_get_task (gpointer data,gpointer user_data){
    CURL* curl_handle=(CURL*)data;
    CURLcode code = curl_easy_perform(curl_handle);
    int* count = (int*)user_data;
    g_mutex_lock(&count_mutex);
    *count += 1;
    g_mutex_unlock(&count_mutex);
}

int http_parallel_get(GSList** response_list, GSList* url_list) {

    assert(*response_list == NULL);
    assert(url_list != NULL);

    int nb_urls = g_slist_length(url_list);
   
    CURL** curl_handle = malloc(sizeof (CURL*) * nb_urls);
   
    int nb_task_completed = 0;
    g_mutex_init(&count_mutex);
    
    GError* error = NULL;
    GThreadPool* thread_pool = g_thread_pool_new(&http_get_task,&nb_task_completed,10,TRUE,&error);
    
    for (int i = 0; i < nb_urls; i++) {
        ResponseBuffer* response = (ResponseBuffer*) malloc(sizeof (ResponseBuffer));
        response->offset = 0;
        *response_list = g_slist_append(*response_list, response);
        curl_handle[i] = curl_easy_init();
        curl_easy_setopt(curl_handle[i], CURLOPT_URL, g_slist_nth_data(url_list, i));
        curl_easy_setopt(curl_handle[i], CURLOPT_WRITEFUNCTION, write_callback_func);
        curl_easy_setopt(curl_handle[i], CURLOPT_WRITEDATA, response);
        g_thread_pool_push(thread_pool,curl_handle[i],NULL);
    }

    while(nb_task_completed < nb_urls)
        g_usleep(200 * 1000); // 100 ms
                
    for (int i = 0; i < nb_urls; i++)
        curl_easy_cleanup(curl_handle[i]);
    
    free(curl_handle);
    g_thread_pool_free(thread_pool,TRUE,FALSE);

    return 0;

}




