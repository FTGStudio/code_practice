#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

bool is_armstrong_number(int candidate);

int main(int argc, char **argv)
{

    is_armstrong_number(123);
    return 0;
}

bool is_armstrong_number(int candidate){
    int digits[255];
    int mod;
    int num = candidate;
    int i = 0;
    int sum = 0;
    int power = 1;
    if(!candidate)
        return false;
    
    // // collect the digits
    while(num > 0){
        digits[i] = num % 10;
        num = num / 10;
        i++;
    }

    for(int k=0; k<i; k++){
        for(int m=0; m<i; m++){
            power = power * digits[k];
        }
        sum += power;
        power = 1;
    }

    printf("%d\n", sum);
    if(sum != candidate)
        return false;

    return true;
}