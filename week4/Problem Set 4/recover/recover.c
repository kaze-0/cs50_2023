#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int sig_check(uint8_t *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    char *infile = argv[1];
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int jpgctr = 0;
    FILE *output = NULL; //初始化output
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE) //每 512B 为一个循环
    {
        //读取buffer前三个字节 判断0xff 0xd8 0xff
        //读取第四个字节 判断第一位1110
        if (sig_check(buffer)) //若是 创建新jpg文件 sprint 命名###.jpg
        {

            if (output != NULL) fclose(output);

            char name[16] = {0};
            if (jpgctr / 10 == 0)
            {
                sprintf(name, "00%i.jpg", jpgctr);
            } else {
                sprintf(name, "0%i.jpg", jpgctr);
            }
            output = fopen(name, "w");
            if (output == NULL)
            {
                fclose(input);
                printf("Could not create %s.\n", name);
                return 1;
            }
            jpgctr ++;

        }
        if (output != NULL) fwrite(buffer, 1, BLOCK_SIZE, output);        //写入buffer数据到目前文件中
    }
    fclose(input);
    if (output != NULL) fclose(output);
    return 0;
}

int sig_check(uint8_t *buffer)
{

    if ((buffer[0] == 0xff)&&(buffer[1] == 0xd8)&&(buffer[2] == 0xff))
    {
        if ((buffer[3] & 0b11110000) == 0b11100000)//按位与运算 仅1&1=1
        // 亦可 n >> 4 右移四位
        return 1;
    }
    return 0;
}