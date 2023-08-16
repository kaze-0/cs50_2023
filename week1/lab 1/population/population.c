#include <cs50.h>
#include <stdio.h>

int main(void){

    int n = 0;
    int end_n = 0;

    while(true){
        n = get_int("Start size: ");
        if(n > 8) break;
        // TODO: Prompt for start size
    }

    while(true){
        end_n = get_int("End size: ");
        if(end_n >= n) break;
        // TODO: Prompt for end size
    }

    int years = 0;
    for(int i = 0; n < end_n; i++){
        n = n + n/3 - n/4;
        years = i + 1;
    }
    // TODO: Calculate number of years until we reach threshold

    printf("Years: %d\n", years);
    // TODO: Print number of years
}
