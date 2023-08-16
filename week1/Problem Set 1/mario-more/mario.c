#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while(true){
        height = get_int("Height: ");
        if(1 <= height && height <= 8) break;
    }
    int r = height;


    for(int i = 0; i < height; i ++){
        r --;

        for(int j = 0; j < r; j ++){
            printf(" ");
        }
        for(int j = 0; j < i + 1; j ++){
            printf("#");
        }
        printf("  ");
        for(int j = 0; j < i + 1; j ++){
            printf("#");
        }
        printf("\n");
    }

}