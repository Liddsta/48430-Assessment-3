

/*Huffman.c
* 01-05-24
* Y_MORRIS
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

/*MinHeapNode struct to represent node in the Huffman tree*/
struct MinHeapNode {
    char string;
    unsigned freq;
    struct MinHeapNode *left *right;
};

/*MinHeap represents minimum heap structure and is used to build the Huffman
* Tree. Size variable stores current number of elements in the heap.
* capacity represents the maximum number of elements the heap can store
* array is the array of pointers to MinHeapNode structures. array is the
* underlying storage for the heap.
*
* Functions creatMinHeap, insertMinHeap, extractMin, minHeapify and buildMinHeap
* collectively create, insert and extract elecments in the minimum heap data
* to constrcut the huffman tree
*/
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

/*newNode is a helper function, creats MinHeapNode with given char and 
* frequency
*/
struct MinHeapNode* newNode(char string, unsigned freq){
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->string = string;
    temp->freq = freq;
    return temp;
}














/**/

struct MinHeap* createMinHeap(unsigned capacity){
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));   
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

/*Swaps two MinHeapNode pointers.
* Utility function used to swap the positions of two MinHeapNode pointers 
* within a MinHeapNode* array.
* Temporary pointer t holds the value of a,
* assigns the value of b to a 
* assigns the value of t (originally a) to b.
* The two  arguments pointers a and b are passed in and the values are swapped.
* Swapping nodes is essential for ensure the heap remains structured according 
* to the minimum heap property.
*/
void SwapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

/*Maintains the MinHeap property of the tree.
* Ensures that the element at the given idx and descendants satisfy the 
* minHeap property. This states that the value of any parent node must be less
* than or equal to the values of its children nodes.
* The function begins by initialising the smallest variable with current idx.
* idx represents the parent node whose subtree might violate the min-heap
* property
*
*           10
*          /  \
*       20     15
*      / \    /   
*    30  40  25
*
* idx 0:    root,               value 10
* idx 1:    left child,         value 20
* idx 2:    right child,        value 15
* idx 3:    left, left child    value 30
* idx 4:    right,left child    value 40
* idx 5:    left, right child   value 25
*
* minHeapify, when executed will begin with idx 0, calculates left and right indices of the
* child nodes:
* left child idx:   2 * 0 + 1 = 1
* right child idx:  2 * 0 + 2 = 2
* comparing values ofthe parent node, left and right children. If left child value is smaller
* than parent value, update smallest to left childs index.
* If right child value is smaller than current smallest value, update smallest to the right
* child idx. If 'smallest' is not equal to parent idx, swap values of parent and smallest 
* child and recursively call minHeapify on affected child node.
*           10
*          /  \
*       20     15
*      / \    /   
*    30  40  25
*
* root/parent:  10
* left child:   20
* right child:  15
* 15 < 10, update smallest to 2 (idx right child)
*
* swap parent with right child.
*           15
*          /  \
*       20     10
*      / \    /   
*    30  40  25
*
* call minHeapify on affected child (idx 2: value:  10) 
* parent:       10
* left child:   25
* since 25 < 10, update smallest to 5 (idx of left, right child), swap parent (10) with
* child (25).
*
*           15
*          /  \
*       20     25
*      / \    /   
*    30  40  10
*
* At this stage, the min-heap property is restored.
*/


void minHeapify(struct MinHeap* minHeap, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap-> && minHeap->array[left]->freq < minHeap->array[smallest]->freq){
        smallest = left;
    } 
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq){
        smallest = right;
    }
    if (smallest != idx){
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}


/*Checks if the min-heap has only one element*/
int isSizeOne(struct MinHeap* minHeap){
    return (minHeap->size == 1);
}

/*Function extractMin is used to remove the minimum element from a min-heap.
* Function begins by extract5ing the minimum element (root of the min-heap):
* this occurs at struct MinHeapNode* temp = minHeap->array[0];
* the function stores the pointer to the root node in variable: temp.
* The root node is replaced with the last element of the heap array.
* Function decrements the size of the heap by one, because the last element 
* has been removeed at line --minHeap->size;
* MinHeapify is called on the root node to ensure the heap property is restored,
* propagating any violations downwrd in the heap.
* extractMin returns the pointer to the minimum element that wsa extracted.*/
struct MinHeapNode* extractMin(struct MinHeap* minHeap){
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}


/*insertMinHeap inserts a new node into a min-heap while maintaining the min-heap 
* property. 
* size of the min-heap is incremented to accomodate a new node.
* index variable i is intialised to index where the new node is to be added.
* i is initially set to the last index of the min-heap array. This occurs at
* int i = minHeap->size - 1;
* The loop allows heapifying the newly inserted node. The loop continues while the
* parent's frequency is greater than the frequency of the new node (minHeapNode).
* loop is terminiated when i reaches the root of the heap or when the new Nodes
* freqency is greater or equal to its paretns frequency. This is due to the loop 
* condition i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq 
* A new node is inserted once the correct position for the new node is found.
* new node is inserted at index i.
*/
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode){
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1)/ 2;
    }
    minHeap->array[i] = minHeapNode;
}

/* From the array, the min heap is built and ensuring that the entire array 
* satisfies the min-heap where each node's value is less than or equal to the 
* values of its children.
* The starting index is calculated using minHeapify: (n - 1) / 2, for n is 
* the size of the heap minus 1.
* The loop iterates from the last non-leaf node to the root.
* Within the for loop, minHeapify is cqalled for each node to ensure that each
* subtree rooted at these nodes satifies the min-heap property.
* At the end of the loop, 
*/
void buildMinHeap(struct MinHeap* minHeap){
    int n = minHeap->size - 1;
    int i;
    for (i = (n-1) / 2; i >=0; i--){
        minHeapify(minHeap, i );
    }
}

void printArr(int arr[], int n){
    int i;
    for (i = 0; i < n; ++i)
        print("%d", arr[i]);
    printf("/n");
}

int isLeaf(struct MinHeapNode* root){
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char string[], int freq[], int size){
    struct MinHeapNode *left, *right, *topl
    struct MinHeap* minHeap = createAndBuildMinHeap(string, freq, size);
    while (!isSizeOne(minHeap)){
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

