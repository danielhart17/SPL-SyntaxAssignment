#include <stdio.h>

int main(int argc, const char * argv[]) {
    char const* const textFile = argv[1];
    FILE* file = fopen(textFile, "r"); // define and open file
    char line[256]; // define variable 'line' with 256
    
    return 0;
}
