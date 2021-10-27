//Books Reference: Operating System Concepts 10th Edition – Silberschatz
//Chapter:04, PROJECT 02: MULTITREAD SORTING APPLICATIONS
//ID: 1705031
//NAME:JANNATUNNAHER
#include<stdio.h>
#include<pthread.h>

int a[30],a1[15],a2[15],a3[30];
int l1,l2;

void sub1(int a[])
{
 int i,j,temp;
 for(i=0; i<l1; i++)
 {
  for(j=0; j<l1-i-1; j++)
  {
    if(a[j+1]<a[j])
    {
       temp=a[j];
       a[j]=a[j+1];
       a[j+1]=temp;
    }
  }
 }

for(i=0 ;i<l1; i++)
{
  a1[i]= a[i];
}
}


void sub2(int a[])
{
 int i,j,temp;
 for(i=0; i<l2; i++)
 {
  for(j=0; j<l2-i-1; j++)
  {
    if(a[j+1]<a[j])
    {
       temp= a[j];
       a[j]=a[j+1];
       a[j+1]=temp;
    }
  }
 }
for(i=0 ;i<l2;i++)
{
  a2[i]=a[i];
}
}

//mergelist
void mergelist(int a[])
{
 int i,k,j,temp;
 int nn=l1+l2;
 for(i=0; i<l1; i++)
 {
  a[i]=a1[i];
 }
 k=l1;

 for(i=0; i<l2; i++)
 {
  a[k]=a2[i];
 k++;
 }

 for(i=0; i<nn; i++)
 {
  a3[i]=a[i];
 }

 for(i=0; i<nn; i++)
 {
   for(j=0; j<nn-i-1; j++)
   {
	if(a3[j+1]<a3[j])
   	{
     		temp=a3[j];
		a3[j]=a3[j+1];
    		a3[j+1]=temp;
	}
   }
 }
 printf("Merge Sort using multithread: \n");
 for(i=0; i<nn; i++)
 {
   printf("%d \t",a3[i]);
 }
}

void main()
{
 int n,i,j=0,k=0;
 pthread_t th1,th2,th3;
 printf("Enter size of array: ");
 scanf("%d",&n);

 for(i=0; i<n; i++)
 {
 scanf("%d",&a[i]);
 }
 for(i=0; i<n; i++)
 {
 printf("a[%d]= %d\n",i,a[i]);
 }

for(i=0; i<n/2; i++)
{
 a1[j]=a[i];
j++;
}

l1= j;
for(i=n/2; i<n; i++)
{
 a2[k]=a[i];
 k++;
}

l2=k;

pthread_create(&th1,NULL,sub1,&a1);
pthread_create(&th2,NULL,sub2,&a2);
pthread_create(&th3,NULL,mergelist,&a3);
pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
}
