#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <memory.h>
#include <time.h>

#define NR_my_syscall 549
#define NR_mm_syscall 548

int main(int argc, char **argv)
{
    int ret = 0;
    srand(time(NULL));

    ret = syscall(NR_my_syscall);
	if (ret != 0) {
		fprintf(stderr, "ERR[%d]: syscall %d is failed\n", ret, NR_my_syscall);
		return -1;
	}
    fprintf(stderr, "------------ Before memory allocation ------------\n");
    ret = syscall(NR_mm_syscall);
	if (ret != 0) {
		fprintf(stderr, "ERR[%d]: syscall %d is failed\n", ret, NR_my_syscall);
		return -1;
	}

    int *temp1 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp1[i] = rand() % 100 + 1;
    }
    int* temp2 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp2[i] = rand() % 100 + 1;
    }
    int* temp3 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp3[i] = temp1[i] + temp2[i];
    }
    int* temp4 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp4[i] = temp2[i] + temp3[i];
    }
    int* temp5 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp5[i] = temp3[i] + temp4[i];
    }
    int* temp6 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp6[i] = temp5[i] + temp5[i];
    }
    int* temp7 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp7[i] = temp5[i] + temp6[i];
    }
    int* temp8 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp8[i] = temp6[i] + temp7[i];
    }
    int* temp9 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp9[i] = temp7[i] + temp8[i];
    }
    int* temp10 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp10[i] = temp8[i] + temp9[i];
    }
    int* temp11 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp11[i] = temp9[i] + temp10[i];
    }
    int* temp12 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp12[i] = temp10[i] + temp11[i];
    }
    int* temp13 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp13[i] = temp11[i] + temp12[i];
    }
    int* temp14 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp14[i] = temp12[i] + temp13[i];
    }
    int* temp15 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp15[i] = temp13[i] + temp14[i];
    }
    int* temp16 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp16[i] = temp14[i] + temp15[i];
    }
    int* temp17 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp17[i] = temp15[i] + temp16[i];
    }
    int* temp18 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp18[i] = temp16[i] + temp17[i];
    }
    int* temp19 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp19[i] = temp17[i] + temp18[i];
    }
    int* temp20 = (int*)malloc(sizeof(int) * 5000000);
    for (int i = 0; i < 5000000; i++) {
        temp20[i] = temp18[i] + temp19[i];
    }

    fprintf(stderr, "------------ After memory allocation ------------\n");
    ret = syscall(NR_mm_syscall);
	if (ret != 0) {
		fprintf(stderr, "ERR[%d]: syscall %d is failed\n", ret, NR_my_syscall);
		return -1;
	}

    free(temp1); free(temp2); free(temp3); free(temp4); free(temp5);
    free(temp6); free(temp7); free(temp8); free(temp9); free(temp10);
    free(temp11); free(temp12); free(temp13); free(temp14); free(temp15);
    free(temp16); free(temp17); free(temp18); free(temp19); free(temp20);

	return 0;
} 