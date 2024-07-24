#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>  //ntohl 함수 


uint32_t openAndntohl(const char * filename);
void add_nbo(const char *file1, const char *file2);

int main(int argc, char *argv[]){

    const char *filename1 = argv[1];
    const char *filename2 = argv[2];
        
    if (argc != 3){ //인자 3개 아니면 예외처리
        fprintf(stderr, "error %s", argv[0]);   
        return EXIT_FAILURE;
    }
    add_nbo(filename1, filename2);

    return EXIT_SUCCESS;
    
}

void add_nbo(const char *file1, const char *file2){ // 두 파일의 합을 계산

    uint32_t sum1 = openAndntohl(file1);
    uint32_t sum2 = openAndntohl(file2);
    uint32_t total_sum = sum1 + sum2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", sum1,sum1,sum2, sum2 ,total_sum, total_sum);
}

uint32_t openAndRead(const char * filename){
    FILE *file;
    uint32_t value;

    // 파일 열기
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }

    if (fread(&value, sizeof(uint32_t), 1, file) == 1) { //파일 4바이트씩 한번 열어오면 -> value
        return value;
    }else{
        value = 0; 
    }
    fclose(file);

    return value;
}

uint32_t openAndntohl(const char * filename){ //network byte order -> host byte order
    FILE *file;
    uint32_t value;
    uint32_t sum = 0;

    file = fopen(filename, "rb");

    if(file == NULL){
        perror("cannot open file");   //cpp에서는 error 안쓰고 perror 씀
        exit(EXIT_FAILURE);
    }

    if (fread(&value, sizeof(uint32_t),1, file) ==1){
        value = ntohl(value);
        sum += value;
    }else {
        value = 0; 
    }

    fclose(file);

    return value;
}