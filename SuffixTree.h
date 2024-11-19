#ifndef SUFFIXTREE_H_INCLUDED
#define SUFFIXTREE_H_INCLUDED

typedef struct node {
    char* text;
    struct node *children[27];   
} Node , *Tree;

Tree createRoot(void);
Tree createNode(char value);
Tree insertNode(Tree root, char value);
Tree createSuffixTree(Tree root, char *word);
void printLevelOrder(Tree root, FILE *file);
void numberOfLeaves(Tree root, int *acc);
void numberOfKDimSuffix(Tree root, int *acc, int k);
void maxNumberOfChildren(Tree root, int *acc);
int suffixExists(Tree root, char *suffix);
void buildCompressedTree(Tree *root);

#endif //TRAIN_H_INCLUDED