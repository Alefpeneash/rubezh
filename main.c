#include <stdio.h>
#include "cmake-build-debug/RoughNode.c"

int main() {
    RoughList list = { .root = NULL };
    insert(&list, 1, 2);



    return 0;
}