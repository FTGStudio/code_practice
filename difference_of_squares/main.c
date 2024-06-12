#include <stdint.h>
#include <stdio.h>

unsigned int sum_of_squares(unsigned int number);
unsigned int square_of_sum(unsigned int number);
unsigned int difference_of_squares(unsigned int number);

int main(int argc, char **argv){

    // printf("%ul", square_of_sum(1));
    printf("%ul", square_of_sum(5));
    return 0;
}

unsigned int sum_of_squares(unsigned int number){
    unsigned int sum = 0;
    for(int i=1; i<=number; i++){
        sum += (i*i);
    }

    return sum;
}
unsigned int square_of_sum(unsigned int number){
    unsigned int square = 0;

    for(int i=1; i<number; i++){
        square += i;
    }
    
    return square*square;
}
unsigned int difference_of_squares(unsigned int number){
    unsigned int difference = 0;
    unsigned int square = 0;
    unsigned int sum = 0;

    square = square_of_sum(number);
    sum = sum_of_squares(number);
    difference = square - sum;

    return difference;
}