/*
*
*
*
*Author: Y_MORRIS 25044847
*
* The program impllements  an algorithm for lossless data compression.
* Lossless data compression is achieved by constructin a huffman tree,
* based on the frequencies of the characters in the string that is 
* passed. 
* The program calculates the frequencies of the chars, and forms the
* tree. The MinHeap data structure is created and maintains a set of
* elements for the binary tree. Nodes with the lowest frequencies are 
* processed first, repeatedly extracted from the MinHeap, combined to
* form new nodes and inserted back into the MinHeap.
*
*           Root
*          /    \
*       left    right
*       /  \    /  \
*      A   B   C    D 
*
* When assigning Huffman codes, the buildHuffmanTree, printCodes and
* HuffmanCodes functions are implemented. The binary codes (0 - left, 
* 1- right) are assigned depending the path  taken to reach each leaf
* node.
*
* 
*
*/


#ifdef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

/* 
* MinheapNode represents a node in the huffman tree 
* data, and frequency and pointers pointing to the left
* and right children of the tree.
*/
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

/* 
* STruct used to build the Huffman tree 
* current size and maximum capacity of the heap
* the array of pointers to MinHeapNode
*/
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};




/* Function prototypes */

/* creates a new node for the given data and frequency */
struct MinHeapNode* newNode(char data, unsigned freq);

/* Create a new MinHeap with the given capacity */
struct MinHeap* createMinHeap(unsigned capacity);

/* Swaps to minHeapNode pointers */
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);

/* Maintains the minHeap property of the tree */
void minHeapify(struct MinHeap* minHeap, int idx);

/* Checks if the MinHeap has only one element */
int isSizeOne(struct MinHeap* minHeap);

/* Extracs the minimum node from the MinHeap */
struct MinHeapNode* extractMin(struct MinHeap* minHeap);

/* Inserts a new MinHeapNode into the MinHeap */
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);

/* Builds the minHeap from an array of nodes */
void buildMinHeap(struct MinHeap* minHeap);

/* Prints the contents of the array */
void printArr(int arr[], int n);

/* Checks if a node is a leaf node */
int isLeaf(struct MinHeapNode* root);

/* Creates and builds a MinHeap from given data and frequencies */
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);

/* Builds the huffman Tree from given data and frequencies 
* characters are taken in as ionput and returns the root of the Huffman tree*/
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);

/* Prints Huffman Codes for each character,  traversing the Huffman tree
* and generating Huffman codes for the characters. The root of the tree,
* array  to store the codes and the size are the function arguements */
void printCodes(struct MinHeapNode* root, int arr[], int top);

/* Generates Huffman Codes for the given data and frequencies.
* Takes characters, frequencies and size as arguments and internally calls 
* buildHuffmanTree and printCodes to form the binary codes*/
void HuffmanCodes(char data[], int freq[], int size);


#endif /* HUFFMAN_H */
