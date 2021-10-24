/*Books Reference: Operating System Concepts 10th Edition – Silberschatz
Chapter:04, Programming Problems 4.24-
Calculating pi using Monte Carlo methods
ID: 1705031
NAME: JANNATUNNAHER
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int i=0;
int pointNo=0;
int totalCirclePoint=0;

void *count(void *x)
{
    for (i=0; i <pointNo; i++)
    {
        double x = (double)rand()/RAND_MAX;
        double y = (double)rand()/RAND_MAX;

        if (((x*x) + (y*y))<=1)
        {
            totalCirclePoint++;
        }
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t thread;

    do
	{
        printf("Enter total point no\n");
        scanf("%d",&pointNo);
	}while (pointNo<= 0);

    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);

    double p = 4.0*totalCirclePoint;
    double pi = p/pointNo;
    printf("The required value of pi for no of %d points is: %f \n", pointNo, pi);
    return 0;
}
