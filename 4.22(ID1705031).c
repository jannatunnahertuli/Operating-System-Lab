/* Books Reference: Operating System Concepts 10th Edition – Silberschatz
Chapter:04, Programming problem 4.22-
Multithreaded program that calculates various statistical values
for a list of numbers.Such as average, maximum, minimum.
ID: 1705031
NAME:JANNATUNNAHER
*/
#include<stdio.h>
#include<pthread.h>

int arr[5000],n,mini,maxi;
float avg;


void *thread_mini()
{
	int temp=arr[0];
	for(int i=1;i<n;i++)
		{
			if(temp>arr[i])
			{
			temp=arr[i];
			}
		}
    mini=temp;
	printf("The Minimum value is: %d\n",mini);

}
void *thread_avg()
{
	float sum=0;
	printf("Enter number of elements in array: ");
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
	    printf("%d  number: ",i+1);
		scanf("%d",&arr[i]);
	}
	for(int i=0; i<n; i++)
    {
		sum=sum+arr[i];
    }
	avg=sum/n;
	printf("The average value is: %.2f\n",avg);
}

void *thread_maxi()
{
	int t=arr[0];
	for(int i=1 ;i<n; i++)
		{
			if(t<arr[i])
			{
			t=arr[i];
			}
		}
    maxi=t;
	printf("The Maximum value is: %d",maxi);
}

int main()
{
    int n,i;
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
	n=pthread_create(&th1,NULL,&thread_avg,NULL);
	pthread_join(th1,NULL);
	n=pthread_create(&th2,NULL,&thread_mini,NULL);
    pthread_join(th2,NULL);
	n=pthread_create(&th3,NULL,&thread_maxi,NULL);
    pthread_join(th3,NULL);
}
