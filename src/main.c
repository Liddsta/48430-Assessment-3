/*
* GROUP #
* MEMBER NAMES:
* SUBMITTED: 
*
*
* Compile instructions: gcc -Wall -Werror -ansi -o main.out main.c -lm
*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100
#define MAX_CONTACTS 4

/* Structure definition for storing contact details */
typedef struct contact {
    char name[NAME_LENGTH];
    unsigned int publicKey;
    unsigned int privateKey;
    struct contact *next;
} contact_t;

/* Function prototypes */
void printMenu(void);
void addContact(contact_t **head, int *currentSize);
void removeContact(contact_t **head, int *currentSize);
void modifyContact(contact_t *head);
void displayContacts(contact_t *head);
void displayContactsForSelection(contact_t *head, const char *action);
contact_t *getContactByIndex(contact_t *head, int index);
void encryptMessage(contact_t *head);
void decryptMessage(contact_t *head);
void saveToFile(contact_t *head, const char *filename);
void loadFromFile(contact_t **head, int *currentSize, const char *filename);
void freeContacts(contact_t **head);
unsigned int getValidUnsignedInt(const char* prompt);

int main(void) {
    contact_t *head = NULL;
    int currentSize = 0;
    int choice;

    do {
        printMenu();
        printf("➤ Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); /* Clear input buffer */

        switch(choice) {
            case 1:
                addContact(&head, &currentSize);
                break;
            case 2:
                modifyContact(head);
                break;
            case 3:
                removeContact(&head, &currentSize);
                break;
            case 4:
                displayContacts(head);
                break;
            case 5:
                encryptMessage(head);
                break;
            case 6:
                decryptMessage(head);
                break;
            case 7:
                saveToFile(head, "contacts.dat");
                break;
            case 8:
                loadFromFile(&head, &currentSize, "contacts.dat");
                break;
            case 9:
                freeContacts(&head);
                printf("\nExiting program...\n");
                return 0; /* Exit the program */
        }
    } while (1);

    return 0;
}

/* Displays the main menu of the contact management system */
void printMenu(void) {
    printf("\n╒═══════════════════════════════╕\n");
    printf("│    Contact Management System  │\n");
    printf("╞═══════════════════════════════╡\n");
    printf("│ 1. Add contact                │\n");
    printf("│ 2. Modify contact             │\n");
    printf("│ 3. Remove contact             │\n");
    printf("│ 4. View contact list          │\n");
    printf("│ 5. Encrypt message            │\n");
    printf("│ 6. Decrypt message            │\n");
    printf("│ 7. Save contacts to file      │\n");
    printf("│ 8. Load contacts from file    │\n");
    printf("│ 9. Exit the program           │\n");
    printf("╘═══════════════════════════════╛\n");
}

/* Adds a new contact to the linked list */
void addContact(contact_t **head, int *currentSize) {
    if (*currentSize >= MAX_CONTACTS) {
        printf("Maximum number of contacts reached.\n");
        return;
    }

    contact_t *new_contact = malloc(sizeof(contact_t));
    if (new_contact == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter name: ");
    fgets(new_contact->name, NAME_LENGTH, stdin);
    new_contact->name[strcspn(new_contact->name, "\n")] = '\0'; /* Remove newline character from input */

    new_contact->publicKey = getValidUnsignedInt("Enter public key (unsigned integer): ");
    new_contact->privateKey = getValidUnsignedInt("Enter private key (unsigned integer): ");

    new_contact->next = *head; /* Insert new contact at the beginning of the linked list */
    *head = new_contact;
    (*currentSize)++;
    printf("Contact added successfully!\n");
}

/* Removes a contact from the linked list */
void removeContact(contact_t **head, int *currentSize) {
    if (*head == NULL) {
        printf("Contact list is empty\n");
        return;
    }

    displayContactsForSelection(*head, "delete");
    int exitIndex = 1;

    contact_t *temp = *head;
    while (temp != NULL) {
        temp = temp->next;
        exitIndex++;
    }

    printf("%d. Exit to main menu\n", exitIndex);
    int index;
    printf("Enter the index of the contact to remove or '%d' to exit: ", exitIndex);
    scanf("%d", &index);
    while (getchar() != '\n');

    if (index == exitIndex) return;

    if (index == 1) {
        contact_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    } else {
        contact_t *current = *head;
        contact_t *prev = NULL;
        int count = 1;
        while (current != NULL && count < index) {
            prev = current;
            current = current->next;
            count++;
        }
        if (current == NULL) {
            printf("Invalid index\n");
            return;
        }
        prev->next = current->next;
        free(current);
    }
    (*currentSize)--;
    printf("Contact removed successfully\n");
}

/* Modifies an existing contact's details */
void modifyContact(contact_t *head) {
    if (head == NULL) {
        printf("Contact list is empty\n");
        return;
    }

    displayContactsForSelection(head, "modify");
    int exitIndex = 1;

    contact_t *temp = head;
    while (temp != NULL) {
        temp = temp->next;
        exitIndex++;
    }

    printf("%d. Exit to main menu\n", exitIndex);
    int index;
    printf("Enter the index of the contact to modify or '%d' to exit: ", exitIndex);
    scanf("%d", &index);
    while (getchar() != '\n');

    if (index == exitIndex) return;

    contact_t *current = getContactByIndex(head, index);

    if (current == NULL) {
        printf("Invalid index\n");
        return;
    }

    int option;
    printf("Select information to modify:\n"
           "1. Name\n"
           "2. Public Key\n"
           "3. Private Key\n"
           "Enter your choice: ");
    scanf("%d", &option);
    while (getchar() != '\n');

    switch (option) {
        case 1:
            printf("Enter new name: ");
            fgets(current->name, NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = '\0'; /* Remove newline character from input */
            break;
        case 2:
            current->publicKey = getValidUnsignedInt("Enter new public key (unsigned integer): ");
            break;
        case 3:
            current->privateKey = getValidUnsignedInt("Enter new private key (unsigned integer): ");
            break;
    }
    printf("Contact modified successfully\n");
}

/* Helper function to display contacts for selection based on a given action */
void displayContactsForSelection(contact_t *head, const char *action) {
    printf("\n╒═══════════════════════════════╕\n");
    printf("│ Select a contact to %s\n", action);
    printf("╞═══════════════════════════════╡\n");
    displayContacts(head);
    printf("╘═══════════════════════════════╛\n");
}

/* Displays all contacts */
void displayContacts(contact_t *head) {
    int index = 1;
    contact_t *current = head;
    while (current != NULL) {
        printf("│ %d.  %s:\n", index, current->name);
        printf("│     Public Key: %u\n", current->publicKey);
        printf("│     Private Key: %u\n", current->privateKey);
        if (current->next != NULL) {
            printf("│\n"); 
        }
        current = current->next;
        index++;
    }
}

/* Placeholder functions for encryption and decryption */
void encryptMessage(contact_t *head) {
    printf("Message encrypted (placeholder).\n");
}

void decryptMessage(contact_t *head) {
    printf("Message decrypted (placeholder).\n");
}

/* Saves all contacts to a specified file */
void saveToFile(contact_t *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file for writing\n");
        return;
    }

    contact_t *current = head;
    while (current != NULL) {
        fprintf(file, "%s,%u,%u\n", current->name, current->publicKey, current->privateKey);
        current = current->next;
    }
    fclose(file);
    printf("Contacts saved successfully\n");
}

/* Loads contacts from a specified file */
void loadFromFile(contact_t **head, int *currentSize, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file for reading\n");
        return;
    }

    freeContacts(head);
    *currentSize = 0;

    contact_t *current = NULL, *new_contact;
    char line[256];
    while (fgets(line, sizeof(line), file) && *currentSize < MAX_CONTACTS) {
        new_contact = malloc(sizeof(contact_t));
        if (new_contact == NULL) {
            printf("Memory allocation failed\n");
            continue;
        }

        sscanf(line, "%[^,],%u,%u", new_contact->name, &new_contact->publicKey, &new_contact->privateKey);
        new_contact->next = NULL;

        if (current == NULL) {
            *head = new_contact;
        } else {
            current->next = new_contact;
        }
        current = new_contact;
        (*currentSize)++;
    }
    fclose(file);
    printf("Contacts loaded successfully\n");
}

/* Frees all dynamically allocated memory used for contacts */
void freeContacts(contact_t **head) {
    contact_t *current = *head, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/* Ensures valid unsigned integer input */
unsigned int getValidUnsignedInt(const char* prompt) {
    unsigned int input;
    printf("%s", prompt);
    while (scanf("%u", &input) != 1) {
        printf("Invalid input. Please enter an unsigned integer.\n");
        while (getchar() != '\n');
        printf("%s", prompt);
    }
    while (getchar() != '\n');
    return input;
}

/* Retrieves a contact by its index in the linked list */
contact_t *getContactByIndex(contact_t *head, int index) {
    contact_t *current = head;
    int count = 1;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    return current;
}





