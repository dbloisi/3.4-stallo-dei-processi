/*
* Corso di Sistemi Operativi
* Corso di Laurea in Scienze e Tecnologie Informatiche
* Universita' della Basilicata
* 
* docente: Domenico D. Bloisi
* domenico.bloisi@unibas.it
*
* **This code is provided without any warranty about its
* usability. It is for educational purposes and should
* be regarded as such.**
*
* mutex-deadlock.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void *do_work_one(void *param)
{
  pthread_mutex_lock(&first_mutex); 
  pthread_mutex_lock(&second_mutex);
  printf("doing work one\n");
  pthread_mutex_unlock(&second_mutex);
  pthread_mutex_unlock(&first_mutex);
  pthread_exit(0);
} 

void *do_work_two(void *param)
{  
  pthread_mutex_lock(&second_mutex);
  pthread_mutex_lock(&first_mutex); 
  printf("doing work two\n");  
  pthread_mutex_unlock(&first_mutex);
  pthread_mutex_unlock(&second_mutex);
  pthread_exit(0);
} 

int main()
{
  pthread_t thread_one, thread_two;

  pthread_mutex_init(&first_mutex, NULL);
  pthread_mutex_init(&second_mutex, NULL);

  if(pthread_create(&thread_one, NULL, do_work_one, NULL) < 0)
  {
      printf("errore creazione thread_one\n");
      exit(1);
  }
  
  if(pthread_create(&thread_two, NULL, do_work_two, NULL) < 0)
  {
      printf("errore creazione thread_two\n");
      exit(1);
  }  
  
  pthread_join (thread_one, NULL);
  pthread_join (thread_two, NULL);
  return 0;
}

