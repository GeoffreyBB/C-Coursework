#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>

typedef struct Contact{
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next;
} Contact;

void menu(Contact* phonebook[26], Contact *head);
void addContact(Contact *phonebook[26], char* first, char* last, char* phone, Contact *head);
int checkContactName(Contact *phonebook[26], char* first, char* last);
int checkContactNumber(Contact *phonebook[26], char* phone);
void deleteContact(Contact *phonebook[26], char* first, char* last, Contact *head);
int findContactNumber(Contact *phonebook[26], char* phone);
int findContactName(Contact *phonebook[26], char* first, char* last, int delete);
void updateContact(Contact *phonebook[26], char* first, char* last, char* phone);
void printList(Contact *phonebook[26]);

int main() {
    Contact* phonebook[26];
    struct Contact *head = NULL;
    //Clearing the phonebook, needs to happen only once at the start.
    //don't know if it is clearing the whole phonebook

    for(int i = 0; i < 26; i++){
        phonebook[i] = NULL;
    }
    menu(phonebook, head);

    return 0;
}

void menu(Contact* phonebook[26], Contact *head){
    printf("Welcome to the phone book manager!\nChoose an option:\n1. Add a new contact to the phone book.\n"
           "2. Delete a contact from the phone book.\n"
           "3. Find a contact in the phone book by phone number.\n4. Find a contact in the phone book by name.\n"
           "5. Update phone number for a contact.\n6. Print phone book.\n7. Exit.\n");

    char first[11], last[11], phone[11];
    int delete;

    int userOption;
    scanf("%d", &userOption);
    switch (userOption) {
        case 1:
            printf("Enter a contact details (<first name> <last name> <phone number>):\n");
            scanf("%s%s%s", first, last, phone);
            addContact(phonebook, first, last, phone, head);
            printf("The contact has been added successfully!\n");
            menu(phonebook, head);
            break;

        case 2:
            printf("Enter a contact name (<first name> <last name>): ");
            char check;
            delete = 1;
            scanf("%s %s", first, last);
            printf("Are you sure? (y/n) ");
            scanf("%s", &check);
            if(check == 'y'){
                int validDelete;
                validDelete = findContactName(phonebook, first, last, delete);
                if (validDelete == 0){
                    printf("The deletion of the contact has failed.\n");
                    break;
                }else{
                    deleteContact(phonebook, first, last, head);
                }
                printf("The contact has been deleted successfully!\n");
            }else{
                printf("The deletion of the contact has been canceled.\n");
            }
            menu(phonebook, head);
            break;

        case 3:
            printf("Enter a phone number: ");
            scanf("%s", phone);
            findContactNumber(phonebook, phone);
            menu(phonebook, head);
            break;

        case 4:
            printf("Enter a contact name (<first name> <last name>): ");
            scanf("%s %s", first, last);
            int valid;
            delete = 0;
            valid = findContactName(phonebook, first, last, delete);
            if(valid == 0){
                printf("No contact with a name %s %s was found in the phonebook\n", first, last);
            }else{
                break;
            }
            menu(phonebook, head);
            break;

        case 5:
            printf("Enter a contact name (<first name> <last name>): ");
            int validN, validP;
            delete = 0;
            scanf("%s %s", first, last);
            validN = findContactName(phonebook, first, last, delete);
            if(validN == 1){
                printf("Enter a new phone number: ");
                scanf("%s", phone);
                validP = checkContactNumber(phonebook, phone);
                if(validP == 1){
                    updateContact(phonebook, first, last, phone);
                }else{
                    printf("The update of the contact has failed, since the phone number %s already exists\n", phone);
                    break;
                }
            }else{
                break;
            }
            menu(phonebook, head);
            break;

        case 6:
            printList(phonebook);
            menu(phonebook, head);
            break;

        case 7:
            printf("Bye!\n");
            fflush(stdin);
            break;

        default:
            printf("Wrong option, try again:\n");
            main();

    }
}

void addContact(Contact *phonebook[26], char* first, char* last, char* phone, Contact *head){
    //Heads up: firstName, lastName, and phoneNum are the variables in the struct. While first, last, and phone (the
    //shortened versions) is the user data.
    Contact* newContact = malloc(sizeof(Contact));
    newContact->firstName = strdup(first);
    newContact->lastName = strdup(last);
    newContact->phoneNum = strdup(phone);
    newContact->next = NULL;

    if(head == NULL){
        head = newContact;
    }else{
        struct Contact *current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newContact;
    }

    //just the code change the placing
    int validName, validNumber;
    validName = checkContactName(phonebook, first, last);
    if(validName == 1){
        validNumber =  checkContactNumber(phonebook, phone);
        if(validNumber == 1){
            //valid contact print add to list
            int index = last[0] - 'A';
            if(phonebook[index] == NULL){
                phonebook[index] = newContact;
            }else{
                Contact* current = phonebook[index];
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = newContact;
            }
        }else{
            printf("The addition of the contact has failed, "
                   "since the phone number %s already exists!\n", newContact->phoneNum);
            menu(phonebook, head);
        }
    }else{
        printf("The addition of the contact has failed, "
               "since the contact %s %s already exists!", newContact->firstName, newContact->lastName);
        menu(phonebook, head);
    }

    //free(newContact);
}

int checkContactName(Contact *phonebook[26], char* first, char* last){
// if contact name return 0 it is false and cannot be added to the phonebook
//if 1 it can be

    int found = 0;
    //checking if the phonebook at that specific index is NULL. If not it checks if the contact name already exists.
    for(int i = 0; i < 25; ++i){
        if(!(phonebook[i])){
            continue;
        }else if(!(strcmp(phonebook[i]->firstName, first)) && !(strcmp(phonebook[i]->lastName, last))){
            found = 1;
            break;
        }
    }
    //if the found = T the func returns F indicating the name is not valid.
    if(found == 1){
        return 0;
    }else{
        return 1;
    }

}

int checkContactNumber(Contact *phonebook[26], char* phone){
// if contact number return 0 it is false and cannot be added to the phonebook
//if 1 it can be

    int found = 0;
    //checking if the phonebook at that specific index is NULL. If not it checks if the contact number already exists.
    for(int i = 0; i < 25; ++i){
        if(!(phonebook[i])){
            continue;
        }else if(!(strcmp(phonebook[i]->phoneNum, phone))){
            found = 1;
            break;
        }
    }
    //if the found = T the func returns F indicating the phone number is not valid.
    if(found == 1){
        return 0;
    }else{
        return 1;
    }

}

void deleteContact(Contact *phonebook[26], char* first, char* last, Contact *head){

    int index = last[0]- 'A';

    Contact *temp = malloc(sizeof(Contact));
    temp->firstName = strdup(first);
    temp->lastName = strdup(last);
    temp->phoneNum = NULL;
    temp->next = NULL;

    Contact *current = malloc(sizeof(Contact));
    //needs to be placed at the first contact in the index
    //current = phonebook[index];
    current->firstName = phonebook[index]->firstName;
    current->lastName = phonebook[index]->lastName;
    current->phoneNum = phonebook[index]->phoneNum;
    current->next = phonebook[index]->next;

    Contact *previous = malloc(sizeof(Contact));
    previous->firstName = NULL;
    previous->lastName = NULL;
    previous->phoneNum = NULL;
    previous->next = NULL;
    /*Contact *previous = malloc(sizeof(Contact));
    previous->firstName = NULL;
    previous->lastName = NULL;
    previous->phoneNum = NULL;
    previous->next = current;*/

    while(current->next != NULL){
        if((temp->firstName == current->firstName) && (temp->lastName == current->lastName)){
            break;
        }
        previous = current;
        current = current->next;
    }

    /*while(current->next != NULL){
        if(strcmp(current->firstName, first) == 0 && strcmp(current->lastName, last) == 0){
            break;
        }
        previous = current;
        current = current->next;
    }*/

    if(previous == NULL){ //deleting a contact at the top of the list (previous->next == NULL)
        previous->next = current->next;
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        free(current->next);
        free(current);
    }else if(current->next == NULL){ //deleting a contact at the bottom of the list
        previous->next = NULL;
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        free(current->next);
        free(current);
    }else if(current != NULL){ //deleting a contact in the middle of the list
        previous->next = current->next;
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        free(current->next);
        free(current);
    }

    //may be a problem with same last name different first name. i want to check all of the contacts at that index number.
    //previous[index]->next=current something like this that iterates through the index.
    /*while(strcmp(current->lastName, last) != 0 || (strcmp(current->firstName, first)) != 0){
        if(current != NULL){
            previous = current;
            current = current->next;
        }
    }

    if(current == NULL){
        printf("The deletion of the contact has failed!\n");
    }else{
        previous->next = current->next;
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        //free(current->next);
        free(current);

    }*/

    /*if(previous != NULL){
        previous->next = current->next;
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        //free(current->next);
        free(current);
        found = 1;
    }*/

    /*if(found == 1){
        //this isnt freeing the addresses completely it is still printing bs symbols after its been "deleted"(before shabbas)
        free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);
        free(current);
    }else if(found == 0){
        printf("The deletion of the contact has failed!\n");
    }*/

    /*if(head == NULL){
        return;
    }
    Contact *current = head;
    Contact *previous = NULL;

    while(current != NULL && strcmp(current->firstName, first) == 0 && strcmp(current->lastName, last) == 0){
        previous = current;
        current = current->next;
    }

    if(current == NULL){
        printf("The deletion of the contact has failed!\n");
        return;
    }else{
        if(previous == NULL){
            head = current->next;
        }else{
            previous->next = current->next;
        }
    }

    free(current);*/

    /*for(int i = 0; i < 26; i++){
        Contact *current = head;
        Contact *previous = NULL;
        if(!(phonebook[i])){
            continue;
        }else if(strcmp(phonebook[i]->lastName, last) == 0){
            if(strcmp(phonebook[i]->firstName, first) == 0){
                current = phonebook[i];
                previous = current;
                current = current->next;
                if(previous == NULL){
                    head = current->next;
                }else{
                    previous->next = current->next;
                }
                found = 1;
                break;
            }else{
                continue;
            }
        }
        free(current);
    }*/

    /* if(found == 1){
         printf("The contact has been deleted successfully!\n");
     }else{
         printf("The deletion of the contact has failed!\n");
     }*/

}

int findContactNumber(Contact *phonebook[26], char* phone){
    char first[11], last[11];
    int found = 0;
    for(int i = 0; i < 26; i++){
        Contact* current = phonebook[i];
        if(!(phonebook[i])){
            continue;
        }else if(strcmp(phonebook[i]->phoneNum, phone) == 0){
            strcpy(first, current->firstName);
            strcpy(last, current->lastName);
            found = 1;
            break;
        }
        free(current);
    }
    if(found == 0){
        printf("No contact with a phone number %s was found in the phone book\n", phone);
        return 0;
    }else{
        printf("The following contact was found: %s %s %s\n", first, last, phone);
        return 1;
    }
}

int findContactName(Contact *phonebook[26], char* first, char* last, int delete){
    char phone[11];
    int found = 0;
    for(int i = 0; i < 26; i++){
        Contact* current = phonebook[i];
        if(!(phonebook[i])){
            continue;
        }else if(strcmp(phonebook[i]->lastName, last) == 0){
            if(strcmp(phonebook[i]->firstName, first) == 0){
                strcpy(phone, current->phoneNum);
                found = 1;
                break;
            }else{
                continue;
            }
        }
        free(current);
    }
    if(found == 0 && delete == 0){
        printf("No contact with a name %s %s was found in the phonebook\n", first, last);
        return 0;
    }else if(found == 0 && delete == 1){
        return 0;
    }else if(found == 1 && delete == 0){
        printf("The following contact was found: %s %s %s\n", first, last, phone);
        return 1;
    }else if(found == 1 && delete == 1){
        return 1;
    }
}

void updateContact(Contact *phonebook[26], char* first, char* last, char* phone){
    int found = 0;
    for(int i = 0; i < 26; i++){
        Contact* current = phonebook[i];
        if(!(phonebook[i])){
            continue;
        }else if(strcmp(phonebook[i]->lastName, last) == 0){
            if(strcmp(phonebook[i]->firstName, first) == 0){
                strcpy(current->phoneNum, phone);
                found = 1;
                break;
            }else{
                continue;
            }
        }
        free(current);
    }
    if(found == 1){
        printf("The contact has been updated succesfully!\n");
    }
}

void printList(Contact *phonebook[26]){

    for(int i = 0; i < 26; i++){
        Contact* current = phonebook[i];
        while(current != NULL){
            printf("%-10s %-10s %-10s\n", current->firstName, current->lastName, current->phoneNum);
            current = current->next;
        }
        /*free(current->firstName);
        free(current->lastName);
        free(current->phoneNum);*/
        // created an error to print with these three
        free(current);
    }

}
