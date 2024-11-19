#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cerinte.h"
#include "SuffixTree.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "--build") == 0) {
        processTree(argv[2], argv[3]);
    }
    if (strcmp(argv[1], "--properties") == 0) {
        int K = atoi(argv[2]);
        calculateTreeProperties(argv[3], argv[4], K);
    }
    if (strcmp(argv[1], "--check") == 0) {
        checkSuffixExistance(argv[2], argv[3]);
    }
    if (strcmp(argv[1], "--compress") == 0) {
        compressTree(argv[2], argv[3]);
    }

    return 0;
}