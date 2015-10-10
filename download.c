#include <string.h>
#include <stdlib.h>
#include "download.h"
#include "curl/curl.h"
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

int http_parallel_get_multi(GSList** response_list, GSList* url_list) {

    assert(*response_list == NULL);
    assert(url_list != NULL);

    int nb_urls = g_slist_length(url_list);

    CURL** curl_handle = malloc(sizeof (CURL*) * nb_urls);
    CURLM *multi_handle = curl_multi_init();
    
    
    for (int i = 0; i < nb_urls; i++) {
        ResponseBuffer* response = (ResponseBuffer*) malloc(sizeof (ResponseBuffer));
        response->offset = 0;
        *response_list = g_slist_append(*response_list, response);
        curl_handle[i] = curl_easy_init();
        curl_easy_setopt(curl_handle[i], CURLOPT_URL, g_slist_nth_data(url_list, i));
        curl_easy_setopt(curl_handle[i], CURLOPT_WRITEFUNCTION, write_callback_func);
        curl_easy_setopt(curl_handle[i], CURLOPT_WRITEDATA, response);
        curl_multi_add_handle(multi_handle, curl_handle[i]);
    }


    CURLcode result; // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
    
    int still_running; /* keep number of running handles */

    curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);

    /* we start some action by calling perform right away */
    curl_multi_perform(multi_handle, &still_running);

    do {
        struct timeval timeout;
        int rc; /* select() return code */
        CURLMcode mc; /* curl_multi_fdset() return code */

        fd_set fdread;
        fd_set fdwrite;
        fd_set fdexcep;
        int maxfd = -1;

        long curl_timeo = -1;

        FD_ZERO(&fdread);
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdexcep);

        /* set a suitable timeout to play around with */
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        curl_multi_timeout(multi_handle, &curl_timeo);
        if (curl_timeo >= 0) {
            timeout.tv_sec = curl_timeo / 1000;
            if (timeout.tv_sec > 1)
                timeout.tv_sec = 1;
            else
                timeout.tv_usec = (curl_timeo % 1000) * 1000;
        }

        /* get file descriptors from the transfers */
        mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

        if (mc != CURLM_OK) {
            fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
            break;
        }

        /* On success the value of maxfd is guaranteed to be >= -1. We call
           select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
           no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
           to sleep 100ms, which is the minimum suggested value in the
           curl_multi_fdset() doc. */

        if (maxfd == -1) {
#ifdef _WIN32
            Sleep(100);
            rc = 0;
#else
            /* Portable sleep for platforms other than Windows. */
            struct timeval wait = {0, 100 * 1000}; /* 100ms */
            rc = select(0, NULL, NULL, NULL, &wait);
#endif
        } else {
            /* Note that on some platforms 'timeout' may be modified by select().
               If you need access to the original value save a copy beforehand. */
            rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
        }

        switch (rc) {
            case -1:
                /* select error */
                break;
            case 0:
            default:
                /* timeout or readable/writable sockets */
                curl_multi_perform(multi_handle, &still_running);
                break;
        }
    } while (still_running);

    curl_multi_cleanup(multi_handle);

    for (int i = 0; i < nb_urls; i++)
        curl_easy_cleanup(curl_handle[i]);

    return 0;

}

void http_get_task (gpointer data,gpointer user_data){
    CURL* curl_handle=(CURL*)data;
    CURLcode code = curl_easy_perform(curl_handle);
    int* count = (int*)user_data;
    *count += 1;
}

int http_parallel_get(GSList** response_list, GSList* url_list) {

    assert(*response_list == NULL);
    assert(url_list != NULL);

    int nb_urls = g_slist_length(url_list);
   

    CURL** curl_handle = malloc(sizeof (CURL*) * nb_urls);
   
    
    int nb_task_completed = 0;
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


    CURLcode result; // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
    
    int still_running; /* keep number of running handles */

    while(nb_task_completed < nb_urls)
        usleep(100 * 1000); // 100 ms
        
        
        
    for (int i = 0; i < nb_urls; i++)
        curl_easy_cleanup(curl_handle[i]);
    
    free(curl_handle);
    g_thread_pool_free(thread_pool,TRUE,FALSE);

    return 0;

}
