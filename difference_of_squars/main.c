#include <stdint.h>
#include <stdio.h>


uint64_t square(uint8_t index);
uint64_t total(void);

int main(int argc, char **argv){

    // printf("%d\n", square(1));
    // printf("%d\n", square(2));
    
    printf("%lu\n", total());

    return 0;
}

uint64_t square(uint8_t index){
    uint64_t result = 1;
    if(index < 1 || index > 64)
        return 0;
    
    for(int i=1; i<index; i++){
        result *= 2;
    }
    return result;
}


uint64_t total(void){
    uint64_t total = 0;
    for (int s = 1; s <= 64; s++){
        total += square(s);
    }
    return total;
}