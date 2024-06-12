#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool isIsogram(char *phrase);

int main(int argc, char **argv)
{
    printf("%d\n", isIsogram("Hello world"));
    printf("%d\n", isIsogram("Yes"));
    return 0;
}

bool isIsogram(char *phrase)
{
    if(!phrase)
        return false;

    uint32_t letter_flags = 0;
    char sub = 'a';

    while(*phrase){
        char letter = *phrase;
        if(letter >= 'a' && letter <= 'z'){
            sub = 'a';
        }
        else if(letter >= 'A' && letter <= 'Z'){
            sub = 'A';
        }
        else
            sub = 'X';


        if(sub != 'X'){
            if((letter_flags & (1 << (letter-sub))) != 0)
                return false;
            else
                letter_flags |= (1 << (letter-sub));
        }
        phrase++;
    }

    printf("%x\n", letter_flags);
    return true;
}