#include <stdlib.h>
#include <stdio.h>
#include "SuffixTree.h"
#include <string.h>
#include "Index.h"
#define max_letters 27
#define limit 100

Tree createRoot(void) {
    Tree root = (Tree)malloc(sizeof(Node));
    for (int i = 0; i < max_letters; i++) {
        root->children[i] = NULL;
    }
    return root;
}

Tree createNode(char value) {
    Tree node = (Tree)malloc(sizeof(Node));
    for (int i = 0; i < max_letters; i++) {
        node->children[i] = NULL;
    }
    node->text = (char *)malloc(limit * sizeof(char));
    node->text[0] = value;
    return node;
}

Tree insertNode(Tree root, char value) {
    if (!root) {
        return NULL;
    }
    int idx = getIndex(value);
    Tree node = createNode(value);
    root->children[idx] = node;
    return root;
}

Tree createSuffixTree(Tree root, char *word) {
    if (!root) {
        return NULL;
    }
    int word_len = strlen(word);
    char *word_mod = (char *)malloc((word_len + 1) * sizeof(char));
    strcpy(word_mod, word);
    strcat(word_mod, "$");
    int i = 0;
    int crt_idx = word_len;
    Tree iter = root;
    while (i <= (word_len + 1)) {
        for (int j = 0; j < i + 1; j++) {
            int sp_index = getIndex(word_mod[crt_idx + j]);
            if (iter->children[sp_index] != NULL) {
                iter = iter->children[sp_index];
            } else {
                iter = insertNode(iter, word_mod[crt_idx + j]);
                iter = iter->children[sp_index];
            }   
        }
        crt_idx--;
        iter = root;
        i++;
    }
    free(word_mod);
    return root;

} 

int childrenAreNULL(Tree root) {
    for (int i = 0; i < max_letters; i++) {
        if (root->children[i]) {
            return 0;
        }
    }
    return 1;
}

void printLevel(Tree root, int level, FILE* file) {
    if (root == NULL) {
        return;
    }
    if (level == 0) {
        fprintf(file, "%s ", root->text);
        return;
    }
    for (int i = 0; i < max_letters; i++) {
        printLevel(root->children[i], level - 1, file);
    }
}
int max(int *v, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

int height(Tree root) {
    if (root == NULL || childrenAreNULL(root)) {
        return 0;
    }
    int *heights  = (int *)calloc(max_letters, sizeof(int));
    for (int i = 0; i < max_letters; i++) {
        heights[i] = height(root->children[i]);
    }
    int maximum;
    maximum = max(heights, max_letters);
    free(heights);
    return maximum + 1;
}

void printLevelOrder(Tree root, FILE *file) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i, file);
        fprintf(file, "\n");
    }
}

void numberOfLeaves(Tree root, int *acc) {
    if (!root) {
        return;
    }
    if (root->children[0] != NULL) {
        (*acc)++;
    }
    for (int i = 1; i < max_letters; i++) {
        numberOfLeaves(root->children[i], acc);
    }
}

void numberOfKDimSuffix(Tree root, int *acc, int k) {
    if (!root) {
        return;
    }
    if (k == 0 && root->children[0] != NULL) {
        (*acc)++;
    }
    for (int i = 1; i < max_letters; i++) {
        numberOfKDimSuffix(root->children[i], acc, k - 1);
    }
}

void maxNumberOfChildren(Tree root, int *acc) {
    if (!root) {
        return;
    }
    int children = 0;
    for (int i = 0; i < max_letters; i++) {
        if (root->children[i] != NULL) {
            children++;
        }
    }
    if (children > (*acc)) {
        *acc = children;
    }
    for (int i = 0; i < max_letters; i++)
        maxNumberOfChildren(root->children[i], acc);
}

int suffixExists(Tree root, char *suffix) {
    if (!root) {
        return 0;
    }
    char *suffix_mod = (char *)malloc((strlen(suffix) + 1) * sizeof(char));
    strcpy(suffix_mod, suffix);
    strcat(suffix_mod, "$");
    int suffix_len = strlen(suffix_mod);
    int i = 0;
    Tree iter = root;
    while (i < suffix_len) {
        int sp_idx = getIndex(suffix_mod[i]);
        if (!iter->children[sp_idx]) {
            free(suffix_mod);
            return 0;
        }
        iter = iter->children[sp_idx];
        i++;
    }
    free(suffix_mod);
    return 1;
}

int numberOfChildren(Tree node) {
    if (!node) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < max_letters; i++) {
        if (node->children[i] != NULL) {
            count++;
        }
    }
    return count;
}

int getSpecificIndex(Tree root) {
    if (!root) {
        return -1;
    }
    for (int i = 1 ; i < max_letters; i++) {
        if (root->children[i] != NULL) {
            return i;
        }   
    }
    return -1;
}

Tree getChildren(Tree dest, Tree src) {
    if (!dest || !src) {
        return NULL;
    }
    for (int i = 0; i < max_letters; i++) {
        dest->children[i] = src->children[i];
    }
    return dest;
}

void buildCompressedTree(Tree *root) {
    if ((*root) == NULL) {
        return;
    }
    if (numberOfChildren(*root) == 1 && (*root)->children[0] == NULL) {
        Tree iter = *root;
        int i = 0;
        int idx = getSpecificIndex(iter);
        iter = iter->children[idx];
        i++;
        while (numberOfChildren(iter) == 1 && iter->children[0] == NULL) {
            (*root)->text[i] = iter->text[0];
            idx = getSpecificIndex(iter);
            i++;
            Tree aux = iter;
            iter = iter->children[idx];
            free(aux);
            aux = NULL;
        }
        (*root)->text[i] = iter->text[0];
        *root = getChildren(*root, iter);
        free(iter);
        iter = NULL;
    }
    for (int i = 0; i < max_letters; i++) {
        buildCompressedTree(&(*root)->children[i]);
    }
}


