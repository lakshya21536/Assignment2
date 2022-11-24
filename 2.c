#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <errno.h>
#define SYS_kernel_2d_memcpy 451

int main(int argc, char **argv)
{
	float matrix1[2][2] = {{1,2},{3,4}};
	float matrix2[2][2];

	printf("Making system call with matrix1 and matrix2\n");

	long res = syscall(SYS_kernel_2d_memcpy, (float *)matrix1, (float *)matrix2);

	printf("System call returned %ld.\n", res);
	perror("Console Output");

	printf("Matrix 2: - After system call\n");

	for(int i = 0; i<2 ; i++){
		for(int j = 0; j<2 ; j++){
			printf("%lf ", matrix2[i][j]);
		}
		printf("\n");
	}
	return res;
}
