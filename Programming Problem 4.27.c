/*Books Reference: Operating System Concepts 10th Edition – Silberschatz
Chapter:04, Programming problems 4.27-
Write a multithreaded program that generates the Fibonacci sequence.
ID:1705031
NAME:JANNATUNNAHER
*/

#include <stdio.h>
#include<unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_t t1;
pthread_t t2;
int fibo[1000];
int top=-1;

void *CAll(void *nn){
    int f1 = 0, f2 = 1, temp= 0;
    fibo[0]=f1;
    fibo[1]=f2;
    top=1;
    int i=0;


    while(i<=*(int*)nn)
    {
        temp= f1 + f2;
        top++;
        fibo[top]=temp;
        f1 = f2;
        f2 = temp;
        i++;
    }
}

void *print(void *nn){
  pthread_join(t2,NULL);

  for(int i=0; i<=*(int*)nn; i++)
{
    printf("%d ",fibo[i]);
  }
}

int main()
{
    int n;
    printf("Enter Number\n");

    scanf("%d",&n);
    printf("The Fibonacci Sequence is: \n");
    pthread_create(&t1,NULL,print,(void*)&n);
    pthread_create(&t2,NULL,CAll,(void*)&n);

    pthread_join(t1, NULL);
}
