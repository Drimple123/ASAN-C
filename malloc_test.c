#define __riscv 1
#include <stdio.h>
#include "malloc.h"
#include "rocc.h"
#include "encoding.h"
//#include "sys/mman.h"

int main(void)
{      
    int cycle;
    //申请了一块shadow memory
    char *p0;
    p0 = NULL;
    p0 = (char *)shadow_malloc(134217744);//128M+16个字节
    if(p0 == NULL){
        printf("没成功\n");
    }
    else{
        printf("%x\n",p0);
    }
    ROCC_INSTRUCTION_S(0, p0, 6);
    
    //printf("size of int = %d\n", sizeof(int)); 

    

    int *p1;
    p1 = NULL;
    p1 = (int *)malloc(sizeof(int)*8);//sizeof(int)=4
    printf("%x\n",p1);

    for(int i=0; i<8; i++){
        *(p1 + i) = i;
    }
    for(int i=1; i<=5; i++){
        printf("%d ", *(p1 + i));
    }
    
    free(p1);
    p1 = NULL;

    //把shadow memory free掉
    shadow_free(p0);
    p0 = NULL;
    cycle = read_csr(0xb00);
    printf("cycle:%d\n", cycle);
    return 0;
}

int __main(void)
{
    while(1){}
    return 0;
}