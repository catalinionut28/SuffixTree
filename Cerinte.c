#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SuffixTree.h"
#define LIMIT 100

void processTree(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "rt");
    FILE *output_file = fopen(output_file_name, "wt");
    int number_words;
    fscanf(input_file, "%d", &number_words);
    Tree suffix_tree = createRoot();
    char *word = (char *)malloc(LIMIT * sizeof(char));
    while (number_words >= 0) {
        fgets(word, LIMIT, input_file);
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        suffix_tree = createSuffixTree(suffix_tree, word);  
        number_words--;      
    }
    printLevelOrder(suffix_tree, output_file);
    fclose(input_file);
    fclose(output_file);
    free(word);
}

void calculateTreeProperties(char *input_file_name, char *output_file_name, int K) {
    FILE *input_file = fopen(input_file_name, "rt");
    FILE *output_file = fopen(output_file_name, "wt");
    int number_words;
    fscanf(input_file, "%d", &number_words);
    Tree suffix_tree = createRoot();
    char *word = (char *)malloc(LIMIT * sizeof(char));
    while (number_words >= 0) {
        fgets(word, LIMIT, input_file);
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        suffix_tree = createSuffixTree(suffix_tree, word);  
        number_words--;
    }
    int leaves = 0;
    int KDimSuffix = 0;
    int max_children = 0;
    numberOfLeaves(suffix_tree, &leaves);
    numberOfKDimSuffix(suffix_tree, &KDimSuffix, K);
    maxNumberOfChildren(suffix_tree, &max_children);
    fprintf(output_file, "%d\n", leaves);
    fprintf(output_file, "%d\n", KDimSuffix);
    fprintf(output_file, "%d\n", max_children);
    fclose(input_file);
    fclose(output_file);
    free(word);
}
void checkSuffixExistance(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "rt");
    FILE *output_file = fopen(output_file_name, "wt");
    int number_words, number_suffixes;
    char *word = (char *)malloc(LIMIT * sizeof(char));
    fscanf(input_file, "%d %d", &number_words, &number_suffixes);
    Tree suffix_tree = createRoot();
    while (number_words >= 0) {
        fgets(word, LIMIT, input_file);
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        suffix_tree = createSuffixTree(suffix_tree, word);  
        number_words--;
    }
    while (number_suffixes > 0) {
        fgets(word, LIMIT, input_file);
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        int yes_or_no = suffixExists(suffix_tree, word);
        fprintf(output_file, "%d\n", yes_or_no);
        printf("%d\n", number_suffixes);
        number_suffixes--;
    }
    fclose(input_file);
    fclose(output_file);
    free(word);
}
void compressTree(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "rt");
    FILE *output_file = fopen(output_file_name, "wt");
    int number_words;
    fscanf(input_file, "%d", &number_words);
    Tree suffix_tree = createRoot();
    char *word = (char *)malloc(LIMIT * sizeof(char));
    while (number_words >= 0) {
        fgets(word, LIMIT, input_file);
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        suffix_tree = createSuffixTree(suffix_tree, word);  
        number_words--;      
    }
    buildCompressedTree(&suffix_tree);
    printLevelOrder(suffix_tree, output_file);
    fclose(input_file);
    fclose(output_file);
    free(word);
}