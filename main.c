/*
* GROUP #
* MEMBER NAMES:
* SUBMITTED: 
*
*
* Compile instructions: gcc -Wall -Werror -ansi -o main.out main.c -lm
*
* Outline:
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/*Student developed headers/libraries*/

/*
*#include "rsa.h"
*#include "huffman.h"
*/

#define NAME_LENGTH 100
#define MESSAGE_LEN 100
#define REGISTER_MAX 4


/*Struct for the Linked List node*/
typedef struct ListNode {
    char name[NAME_LENGTH];
    unsigned int publickey;
    unsigned int privatekey;
    char message[MESSAGE_LEN +1];
    struct ListNode* next;
} ListNode;

/*Function prototype*/

void MainMenu();
ListNode* allocateMemory();
void createContact(ListNode** head, int* size);
/*void modifyContact(contact_t *contact);
*void removeContact(int *size);
*void encryptMessage();
*void decryptMessage();
*void viewDecrypt();
*void storeFile(contact_t *register, int size, const char *filename);
*/



int main(){
    ListNode* registerList = NULL;
    MainMenu();

    ListNode* current = registerList;

    while (current != NULL){
        ListNode* next = current->next;
        free(current);
        current = next;
    }

    MainMenu();
    return 0;

}


 void MainMenu(){

    ListNode* registerList = NULL;
    int size = 0;

    printf(" ========================================================================\n");
    printf(" :                            INSERT TITLE HERE                         :\n");
    printf(" ========================================================================\n");
    printf("\n"
           " ::                          1 - CREATE CONTACT                        ::\n"
           " ::                          2 - MODIFY CONTACT                        ::\n"
           " ::                          3 - REMOVE CONTACT                        ::\n"
           " ::                          4 - ENCRYPT MESSAGE                       ::\n"
           " ::                          5 - DECRYPT MESSAGE                       ::\n"
           " ::                          6 - STORE CONTACT TO FILE                 ::\n"
           " ::                          7 - EXIT                                  ::\n"
           "\n"
           " ========================================================================\n");

    int selection;

    do {
        if (scanf(" %d", &selection) != 1 || selection < 1 || selection > 7){
            printf("Invalid selection.\n");
            /*Clear input buffer*/
            while (getchar() != '\n');
            continue;
        }
        /*Check if register is full*/
        if (selection == 1 && size == REGISTER_MAX){
            printf("Register is full\n");
            continue;
        }
        switch(selection){
            case 1:
                createContact(&registerList, &size);
                break;
            case 2:
                if (size == 0){
                    printf("Register is empty\n");
                } else {
                   /* modifyContact(&register, &size); */
                }
                break;
            case 3:
                if (size == 0){
                    printf("Register is empty\n");
                } else {
                  /*  removeContact(&size);*/
                }
                break;
            case 4:
            /*Figure out what arguements to take*/
                /*encryptMessage();*/
                break;
            case 5:
            /*Figure out what arguments to take*/
                /*viewDecrypt();*/
                break;
            case 6:
                /*storeFile(register, size, fileName);*/
                break;
            case 7:
                free(registerList);
                return;
        }


    } while (1);

} 


ListNode* allocateMemory(){

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
        
    }
    newNode->next = NULL;
    /*Initalise next pointer*/
    return newNode;

}

void createContact(ListNode** head, int* size){
    ListNode* newNode;
    if (*size >= REGISTER_MAX){
        printf("Register is full\n");
        return;
    }

    newNode = allocateMemory();

    printf("Enter name: ");
    scanf("%s", newNode->name);
    printf("Enter public key: ");
    scanf("%u", &newNode->publickey);
    printf("Enter private key: ");
    scanf("%u", &newNode->privatekey);
    printf("Enter message: ");
    scanf("%s", newNode->message);
    

    /*Intert new node at the beginning of the linked list*/
    newNode->next = *head;
    *head = newNode;

    (*size)++;

    return;
}




