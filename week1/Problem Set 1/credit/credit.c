#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long num = get_long("Number: ");
    int a[16];
    int len = 0;

    // get every single number
    memset(a, -1, 16 * sizeof(int));
    long tmp = num;
    for (int i = 0; tmp != 0; i++)
    {
        a[i] = tmp % 10;
        tmp = tmp / 10;
        len = i + 1;
        // printf("len:%d\n",len);
    }

    int sum1 = 0;
    for (int i = 1; i < len; i += 2)
    {
        sum1 += a[i] * 2 / 10 + a[i] * 2 % 10;
    }
    int sum2 = sum1;
    for (int i = 0; i < len; i += 2)
    {
        sum2 += a[i];
    }
    if (sum2 % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // AMEX 34/37 15
    if (len == 15 && (((int) (num / (1e13))) == 34 || ((int) (num / (1e13))) == 37))
        printf("AMEX\n");

    // MASTERCARD 51~55 16
    else if (len == 16 && (((int) (num / (1e14))) <= 55 && ((int) (num / (1e14))) >= 51))
        printf("MASTERCARD\n");

    // VISA 4 13/16
    else if ((len == 13 && ((int) (num / (1e12))) == 4) || (len == 16 && ((int) (num / (1e15))) == 4))
        printf("VISA\n");

    else
        printf("INVALID\n");

    return 0;
}