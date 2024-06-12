#include <stdint.h>
#include <string.h>

int compute(const char *lhs, const char *rhs);

int main(int argc, char **argv){
    
    printf("%d\n", compute("GAGCCTACTAACGGGAT", "CATCGTAATGACGGCCT"));
    printf("%d\n", compute("A", "A"));

    return 0;
}

int compute(const char *lhs, const char *rhs){
    int retVal = 0;
    int lhsLen = strlen(lhs);
    int rhsLen = strlen(rhs);
    char tmpL;
    char tmpR;

    if(!lhs || !rhs)
        return -1;

    // Check for equal length
    if(lhsLen == rhsLen){
        // compute the hamming distance
        while(lhsLen){
            tmpL = *lhs;
            tmpR = *rhs;

            if(tmpL != tmpR)
                retVal++;
            lhs++;
            rhs++;
            lhsLen--;
        }
    }

    return retVal;
}