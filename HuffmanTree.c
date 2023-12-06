// Daniel Lee
// This file is for the implementation of the Huffman module
// The program can decode, encode and make a huffman tree
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"
#include "File.h"
#include "huffman.h"

// Helper Functions
static struct huffmanTree *createTreeHelperFunc(struct item *itemArray);
static int compare(const void *v1, const void *v2);
static struct huffmanTree *mergedTree(struct huffmanTree *treeOne,
                                      struct huffmanTree *treeTwo);
char *encoder(struct huffmanTree *tree, char *inputFilename,
              char *encodedString);

// Task 1
void decode(struct huffmanTree *tree, char *encoding, char *outputFilename) {
    // Encoding is the file with integers that need to be decoded
    File decodedFile = FileOpenToWrite(outputFilename);
    struct huffmanTree *current = tree;
    int index = 0;

    while (encoding[index] != '\0') {
        // If the code has 0 go left, 1 go right
        if (encoding[index] == '0') {
            current = current->left;
        } else if (encoding[index] == '1') {
            current = current->right;
        }
        // When it reaches leaf node
        if (current->left == NULL && current->right == NULL) {
            FileWrite(decodedFile, current->token);
            current = tree;
        }
        index++;
    }
    // Writes string to file
    FileClose(decodedFile);
}

// Task 3
struct huffmanTree *createHuffmanTree(char *inputFilename) {
    File huffmanFile = FileOpenToRead(inputFilename);
    // Making new Counter
    Counter newCounter = CounterNew();
    char *stringforToken = malloc(sizeof(char) * MAX_TOKEN_LEN);
    while (FileReadToken(huffmanFile, stringforToken)) {
        // Making nodes
        CounterAdd(newCounter, stringforToken);
    }
    int numItems = 0;
    struct item *itemArray = CounterItems(newCounter, &numItems);
    // Freeing the malloc'd string
    free(stringforToken);
    // Freeing the counter
    CounterFree(newCounter);
    // Making array of tree structs
    struct huffmanTree **tree = malloc(sizeof(struct huffmanTree *) * numItems);
    // Adding itemArray into huffmanTree Tree
    int index = 0;
    while (index < numItems) {
        tree[index] = createTreeHelperFunc(&itemArray[index]);
        index++;
    }
    // Merging Trees
    // Sorting the tree by qsort with lowest freq
    while (numItems > 1) {
        // Sort it every loop
        qsort(tree, numItems, sizeof(struct huffmanTree *), compare);
        struct huffmanTree *mergingTree = mergedTree(tree[0], tree[1]);
        for (int j = 1; j + 1 < numItems; j++) {
            tree[j] = tree[j + 1];
        }
        numItems--;
        tree[0] = mergingTree;
    }
    // free itemArray by freeing token each
    for (int i = 0; i < numItems - 1; i++) {
        free(itemArray[i].token);
    }
    free(itemArray);
    // input tree[0] into struct huffmanTree *finalTree;
    struct huffmanTree *finalTree = tree[0];
    // Free tree itself
    free(tree);
    FileClose(huffmanFile);
    return finalTree;
}
// createHuffmanTree:HelperFunc - Qsort helper func
// USED FROM WEBSITE https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs
static int compare(const void *v1, const void *v2) {
    const struct huffmanTree *p1 = *(struct huffmanTree **)v1;
    const struct huffmanTree *p2 = *(struct huffmanTree **)v2;
    if (p1->freq > p2->freq)
        return (1);
    else if (p1->freq < p2->freq)
        return (-1);
    else
        return (0);
}
// createHuffmanTree:HelperFunc - Create an empty tree
static struct huffmanTree *createTreeHelperFunc(struct item *itemArray) {
    struct huffmanTree *newTree = malloc(sizeof(struct huffmanTree));
    newTree->token = strdup(itemArray->token);
    free(itemArray->token);
    newTree->freq = itemArray->freq;
    newTree->left = NULL;
    newTree->right = NULL;
    return newTree;
}
// createHuffmanTree:HelperFunc - func to merge two trees into one
static struct huffmanTree *mergedTree(struct huffmanTree *treeOne,
                                      struct huffmanTree *treeTwo) {
    struct huffmanTree *newTree = malloc(sizeof(struct huffmanTree));
    newTree->token = NULL;
    newTree->freq = treeOne->freq + treeTwo->freq;
    newTree->left = treeOne;
    newTree->right = treeTwo;
    return newTree;
}
// Task 4
char *encode(struct huffmanTree *tree, char *inputFilename) {
    // File encodedFile = FileOpenToRead(inputFilename);
    // char *array = NULL;
    // while (inputFilename != '\0') {
    //  encoder(tree, inputFilename, array);
    // }
    // FileWrite(File file, char *str);
    // FileClose(encodedFile);
    return NULL;
}
char *encoder(struct huffmanTree *tree, char *inputFilename,
              char *encodedString) {
    // Base Case
    // if (tree == NULL) {
    //  return NULL;
    // }
    // if (strcmp(inputFilename[index], tree->token)) {
    //  index++;
    // }
    // // Using Recursion
    // inputFilename->left = encoder(tree->left, inputFilename, encodedString);
    // inputFilename->right = encoder(tree->right, inputFilename, encodedString);
    return NULL;
}
