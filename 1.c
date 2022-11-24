#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
long long int t1,t2,t3;
static void* countA(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i = 0;
	for(; i<pow(2,32) ; i++)
	{
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long int x = pow(10,9)*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
	printf("elapsed time FIFO = %llu seconds\n",x);
	t1=x;
	return NULL;
}

static void* countB(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i = 0;
	for(; i<pow(2,32) ; i++)
	{
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long int x = pow(10,9)*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
	printf("elapsed time RR= %llu seconds\n",x);
	t2=x;
	return NULL;
}

static void* countC(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i =0;
	for(; i<pow(2,32) ; i++)
	{
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long int x = pow(10,9)*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
	printf("elapsed time OTHER = %llu seconds\n",x);
	t3=x;
	return NULL;
}
		

int main(int argc, char *argv[]){
int p=1;
for(int i=0;i<6;i++){
FILE *f;
f=fopen("histogram.data","a");
pthread_t thr1, thr2, thr3;
pthread_attr_t attr1, attr2, attr3;
int s;

s = pthread_attr_init(&attr1);
s = pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
s = pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
struct sched_param schedParam1;
schedParam1.sched_priority = p;
s = pthread_attr_setschedparam(&attr1, &schedParam1);
s = pthread_create(&thr1, &attr1, &countA, NULL);

s = pthread_attr_init(&attr2);
s = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
s = pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
struct sched_param schedParam2;
schedParam2.sched_priority = p;
s = pthread_attr_setschedparam(&attr2, &schedParam2);
s = pthread_create(&thr2, &attr2, &countB, NULL);

s = pthread_attr_init(&attr3);
s = pthread_attr_setschedpolicy(&attr3, SCHED_OTHER);
s = pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
struct sched_param schedParam3;
schedParam3.sched_priority = 0;
s = pthread_attr_setschedparam(&attr3, &schedParam3);
s = pthread_create(&thr3, &attr3, &countC, NULL);

pthread_join(thr1,NULL);
pthread_join(thr2,NULL);
pthread_join(thr3,NULL);
fprintf(f,"%d %llu %llu %llu\n",p,t1,t2,t3);
p=p+8;
fclose(f);
}
return 0;

}
