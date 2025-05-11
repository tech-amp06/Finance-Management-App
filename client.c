#include <stdio.h>
#include "graphing.c"

int main() {
    int expenses[] = {20000, 15000, 24000, 70000, 40000, 60000, 20000, -1};
    
    plot(expenses, 3);
    
    return 0;
}