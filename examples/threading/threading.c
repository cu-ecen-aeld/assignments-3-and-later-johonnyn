#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

#define MS_TO_US(ms) (ms * 1000)

void* threadfunc(void* thread_param)
{
    struct thread_data* const thread_func_args = (struct thread_data *) thread_param;

    usleep(MS_TO_US(thread_func_args->wait_to_obtain_ms));
    pthread_mutex_lock(thread_func_args->mutex);
    usleep(MS_TO_US(thread_func_args->wait_to_release_ms));
    pthread_mutex_unlock(thread_func_args->mutex);

    usleep(MS_TO_US(thread_func_args->wait_to_obtain_ms));

    thread_func_args->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    struct thread_data* thread_func_args = malloc(sizeof(struct thread_data));
    if (!thread_func_args) {
        ERROR_LOG("Failed to allocate memory for thread_data");
        return false;
    }

    thread_func_args->mutex = mutex;
    thread_func_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_func_args->wait_to_release_ms = wait_to_release_ms;

    if (pthread_create(thread, NULL, threadfunc, thread_func_args) != 0) {
        ERROR_LOG("Failed to create thread");
        free(thread_func_args);
        return false;
    }

    return true;
}

