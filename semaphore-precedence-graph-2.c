#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *sem_a, *sem_d, *sem_e, *sem_h;
int h, j, u, x, y, z;

//TODO generic process receiving a struct as parameter, containing process_name and a list of semaphores to wait and to post

void* process_1(void* unused){
    printf("P1: begin A\n");
	x = 1;
	y = 1;
	z = 2;
	sem_post(sem_a); //for B
	sem_post(sem_a); //for G
    printf("E\n");
	y = y+2;
	sem_post(sem_e); //for D
	sem_post(sem_e); //for H
	sem_wait(sem_d);
	sem_wait(sem_h);
	printf("F\n");
	u = h+j/3;
	printf("end P1\n");
    pthread_exit(NULL);
}

void* process_2(void* unused){
	sem_wait(sem_a);
	printf("P2: begin B\n");
	x = x*2;
    printf("C\n");
	x = x+1;
	sem_wait(sem_e);
	printf("D\n");
	h = y+x;
	printf("end P2\n");
	sem_post(sem_d);
    pthread_exit(NULL);
}

void* process_3(void* unused){
    sem_wait(sem_a);
    printf("P3: begin G\n");
	z = z/2;
	sem_wait(sem_e);
    printf("H\n");
	j = z+y-4;
	printf("end P3\n");
    sem_post(sem_h);
    pthread_exit(NULL);
}

int main (void){
	h = j = u = x = y = z = 0;
	
    // Semaphores initialization
    sem_a = sem_open("/sem_a", O_CREAT, 0644, 0);
	sem_d = sem_open("/sem_d", O_CREAT, 0644, 0);
	sem_e = sem_open("/sem_e", O_CREAT, 0644, 0);
	sem_h = sem_open("/sem_h", O_CREAT, 0644, 0);
	
    // Threads creation
    pthread_t thread_1, thread_2, thread_3;
    pthread_create(&thread_1,NULL,process_1,NULL);
    pthread_create(&thread_2,NULL,process_2,NULL);
    pthread_create(&thread_3,NULL,process_3,NULL);
	
    // Wait all threads to finish
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
	
    // Close named semaphores
    sem_close(sem_a);
    sem_close(sem_d);
    sem_close(sem_e);
	sem_close(sem_h);
    
    // Unlink named semaphores
    sem_unlink("/sem_a");
    sem_unlink("/sem_d");
    sem_unlink("/sem_e");
	sem_unlink("/sem_h");
	
	printf("Result: u=%d\n", u);
}
