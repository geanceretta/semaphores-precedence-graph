#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *mutex_a, *mutex_b, *semaphore_c;

//TODO generic process receiving a struct as parameter, containing process_name and a list of semaphores to wait and to post

void* process_a(void* unused){
    printf("Starting process A\n");
    //sleep((rand()%4)+1);
    printf("Stopping process A\n");
    sem_post(mutex_a);
    pthread_exit(NULL);
}

void* process_b(void* unused){
    printf("Starting process B\n");
    //sleep((rand()%4)+1);
    printf("Stopping process B\n");
    sem_post(mutex_b);
    pthread_exit(NULL);
}

void* process_c(void* unused){
    sem_wait(mutex_a);
    sem_wait(mutex_b);
    printf("Starting process C\n");
    //sleep((rand()%4)+1);
    printf("Stopping process C\n");
    sem_post(semaphore_c);
    sem_post(semaphore_c);
    pthread_exit(NULL);
}

void* process_d(void* unused){
    sem_wait(semaphore_c);
    printf("Starting process D\n");
    //sleep((rand()%4)+1);
    printf("Stopping process D\n");
    pthread_exit(NULL);
}

void* process_e(void* unused){
    sem_wait(semaphore_c);
    printf("Starting process E\n");
    //sleep((rand()%4)+1);
    printf("Stopping process E\n");
    pthread_exit(NULL);
}


int main (void){
    // Semaphores initialization
    mutex_a = sem_open("/mutex_a", O_CREAT, 0644, 0);
    mutex_b = sem_open("/mutex_b", O_CREAT, 0644, 0);
    semaphore_c = sem_open("/semaphore_c", O_CREAT, 0644, 0);

    // Threads creation
    pthread_t thread_a, thread_b, thread_c, thread_d, thread_e;    
    pthread_create(&thread_a,NULL,process_a,NULL);
    pthread_create(&thread_b,NULL,process_b,NULL);
    pthread_create(&thread_c,NULL,process_c,NULL);
    pthread_create(&thread_d,NULL,process_d,NULL);
    pthread_create(&thread_e,NULL,process_e,NULL);

    // Wait all threads to finish
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    pthread_join(thread_d, NULL);
    pthread_join(thread_e, NULL);
    
    // Close named semaphores
    sem_close(mutex_a);
    sem_close(mutex_b);
    sem_close(semaphore_c);
    
    // Unlink named semaphores
    sem_unlink("/mutex_a");
    sem_unlink("/mutex_b");
    sem_unlink("/semaphore");
}
