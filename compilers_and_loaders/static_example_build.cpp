// to compile this as a static binary, use the -static flag. 
// gcc -static main.cpp -o staticBuild 
// This is not supported by clang on Mac OS X, so best to try this out on Linux. 

#include <stdio.h> 

int main() 
{
    printf("hello world\n"); 
    return 0; 
}
