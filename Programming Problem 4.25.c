/*Books Reference: Operating System Concepts 10th Edition – Silberschatz
Chapter:04, Programming problems 4.25-
Calculate pi using OpenMP to parallelize the generation of points.
ID:1705031
NAME:JANNATUNNAHER
*/
#include <stdio.h>
#include <math.h>
#include <omp.h>

const int totalRec=1000000;

int main() {

float w=1.0/totalRec;
float x,h,pi,area = 0.0;
int i;
for (i= 0; i<totalRec; i++) {
x=i*w;
h=sqrt(1.0 - x*x);
area=area+w*h;
}

pi=4.0*area;

printf("The approximate value of pi is %f\n", pi);

return 0;
}

