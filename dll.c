#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    // an element of the doubly-linked list
    int value;
    struct ListElement* next;
    struct ListElement* prev;
};


/*
Function prototypes are given here so that one may easily see which functions exist.
Function definitions are at the bottom, with comments for explanation
*/

// literally just prints a new line, but using this function looks nicer than typing `printf("\n");` every time
void newline(void);

// memory allocation function (for code readability)
struct ListElement* allocateNewListElement(void);

// printing functions
void printListElements(struct ListElement*);

// functinos for adding new list elements
void createListElement(int, struct ListElement**);
void insertAtHead(int, struct ListElement**);
void insertAtIndex(int, int, struct ListElement**);
                                                    // for consistency's sake, I pass a double pointer to all creation and destruction functions
// functions for destroying list elements           // (even if it isn't strictly necessary)
void destroyHeadElement(struct ListElement**);
void destroyLastElement(struct ListElement**);
void destroyIndex(int, struct ListElement**);
void destroyValue(int, struct ListElement**);
void destroyList(struct ListElement**);

// functions for finding list elements
int getFirst(struct ListElement*);
int getLast(struct ListElement*);
int getAtIndex(int, struct ListElement*);

// function to find list length
int getNumElements(struct ListElement*);

// search functions
int searchFor(int, struct ListElement*);
int searchForStartingFrom(int, int, struct ListElement*);

// function for joining two lists
void appendLists(struct ListElement**, struct ListElement**);








int main(void) {
    /*
    This main function creates two doubly linked lists and manipulates them using all functions named above.
    Several print statements are included to verify that the list manipulations are working as intended.
    Expected outputs are included as comments, and can be verified against the actual output of the program.
    */

    struct ListElement* head1 = NULL;
    struct ListElement* head2 = NULL;

    // create arrays with values to use to initialize two doubly linked lists
    // following that, I've coded some manual tests of the functions I wrote
    int array1[] = {10, 11, 12, 13, 20, 21, 22, 23, 13, 17};
    int array2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    for (int i = 0; i < sizeof(array1) / sizeof(int); i++) {
        // create list 1
        createListElement(array1[i], &head1);
    }
    for (int i = 0; i < sizeof(array2) / sizeof(int); i++) { 
        // create list 2
        createListElement(array2[i], &head2);
    }

    printf("List 1: ");
    printListElements(head1); // expecting 10, 11, 12, 13, 20, 21, 22, 23, 13, 17

    printf("List 2: ");
    printListElements(head2); // expecting 0, 1, 2, 3, 4, 5, 6, 7, 8 ,9

    newline();

    int first = getFirst(head1);
    int last = getLast(head1);
    int len = getNumElements(head1);

    printf("Head element of first list is %d at memory address %p.\n", head1->value, head1); // test getFirst:            expecting 10 (plus memory address)
    printf("Last element of first list is is %d.\n", last);                                  // test getLast:             expecting 17
    printf("Length of first list is %d.\n", len);                                            // test getNumElements:      expecting 10

    newline();

    insertAtHead(1, &head1);
    int newLen = getNumElements(head1);

    printf("Head element updated:\n");
    printf("New head element of first list is %d at memory address %p.\n", head1->value, head1);// test insertAtHead: expecting 1 (plus different memory address as before)
    printf("Next element is %d at memory address %p.\n", head1->next->value, head1->next);      // test insertAtHead: expecting 10 (plus same memory address as before)
    printf("Next length of the list is %d.\n", newLen);                                         // test insertAtHead: expecting 11

    newline();

    insertAtIndex(15, 10, &head1);
    insertAtIndex(-1, 1000, &head1); // should do nothing

    printf("New element inserted into list 1:\n");
    printf("List 1: "); printListElements(head1);          // test insertAtIndex:    expecting 1, 10, 11, 12, 13, 20, 21, 22, 23, 13, 15, 17

    newline();

    printf("Index 6 of first list is %d.\n", getAtIndex(6, head1));                                         // test getAtIndex:             expecting 21
    printf("Index 1000 of first list is %d.\n", getAtIndex(1000, head1));                                   // test getAtIndex:             expecting  0
    printf("Value 13 occurs at index %d.\n", searchFor(13, head1));                                         // test searchFor:              expecting  4
    printf("Next occurence of 13 occurs at %d.\n", searchForStartingFrom(13, searchFor(13, head1), head1)); // test searchForStartingFrom:  expecting  9
    printf("Next occurence of 13 occurs at %d.\n", searchForStartingFrom(13, 9, head1));                    // test searchForStartingFrom:  expecting -1

    newline();

    appendLists(&head1, &head2);

    printf("Lists appended, list 1 now contains all list elements.\n");
    printf("Length of list 1 is now %d.\n", getNumElements(head1));     // test appendLists:  expecting 22
    printf("List 1: "); printListElements(head1);                       // test appendLists:  expecting 1 10 11 12 13 20 21 22 23 13 15 17 0 1 2 3 4 5 6 7 8 9
    printf("List 2 now stored at memory address %p.\n", head2);         // text appendLists:  expecting NULL

    newline();

    destroyIndex(5, &head1);     // should destroy element with value 20
    destroyIndex(0, &head1);     // should destroy first element
    destroyIndex(19, &head1);    // should destroy last element
    destroyIndex(1000, &head1);  // should do nothing

    printf("Specific elements of list 1 destroyed.\n");
    printf("List 1: "); printListElements(head1);             // expecting 10 11 12 13 21 22 23 13 15 17 0 1 2 3 4 5 6 7 8

    newline();

    for (int i = 0; i < 8; i++) {destroyLastElement(&head1);} // destroy the last 8 elements
    printf("List 1: "); printListElements(head1);             // expecting 10 11 12 13 21 22 23 13 15 17 0 

    newline();

    destroyHeadElement(&head1);
    newline();
    printf("List 1: "); printListElements(head1); // expecting 11 12 13 21 22 23 13 15 17 0

    newline();

    destroyValue(17, &head1);     // should destroy element with value 17
    destroyValue(100, &head1);    // should do nothing

    newline();

    printf("List 1: "); printListElements(head1);  // expecting 11 12 13 21 22 23 13 15 0

    newline();

    printf("List 1 currently contains %d elememts.\n", getNumElements(head1)); // length of list 1
    destroyList(&head1);                                                       // last line of output should match length of list 1
    printf("Head pointer now points to memory address %p.\n", head1);          // expecting NULL

    return 0;
}








// function definitions

void newline(void) {printf("\n");}

struct ListElement* allocateNewListElement(void) {
    /*
    Just to make things slightly more explicit in the functions to follow,
    I have defined this function to simply create a new memory allocation
    for the doubly linked list.

    Returns a pointer to the new memory allocation.
    */
    return (struct ListElement*) malloc(sizeof(struct ListElement));
}

void printListElements(struct ListElement* head) {
    struct ListElement* current = head;
    while (current != NULL) {
        printf("%d ", current -> value);
        current = (*current).next;
    }
    newline();
}

void createListElement(int entry, struct ListElement** head_ptr) {
    /*
    Adds a new element to the end of the list. If the list doesn't yet exist, then
    this creates the first element in the list.

    head_ptr is a pointer to the pointer to the first element of the list. This is
    important, as if the list doesn't exist yet then we need to change the value of 
    the head pointer from NULL to the appropriate memory address.
    */

    struct ListElement* current = *head_ptr; // a pointer to the current list element
    struct ListElement* previous = NULL;     // a pointer to the previous list element
    struct ListElement* new; // this will point to our new list element
    new = allocateNewListElement();

    if (current == NULL) {
        /*
        If the pointer to the head of the list is NULL, then the list doesn't exist yet.
        NULL is recorded in current, so if current is NULL then we set *head_ptr to new 
        and update all the values at *head_ptr.
        */
        *head_ptr = new;
        (**head_ptr).value = entry;
        (**head_ptr).next = NULL;
        (**head_ptr).prev = NULL;

    } else {

        while (current != NULL) {
            // go to the end of the list so that `previous` points at the last element
            previous = current;
            current = (*current).next;
        }

        /* 
        Setting values:
         - the value at the new pointer is the integer entry passed to the function
         - the pointer to the next element is NULL
         - the pointer to the previous element is stored in `previous`

         - the previous element's "next" pointer is updated to be the new memory location
        */
        new -> value = entry;
        new -> next = NULL;
        new -> prev = previous;

        previous -> next = new;
    }
}

void insertAtHead(int entry, struct ListElement** head_ptr) {
    /*
    Creates a new list element `entry` as the head element. Since the head element will change, 
    the head pointer will need to be updated, so this function requires &head to be passed.
    */
    struct ListElement* new;
    new = allocateNewListElement();

    (*new).value = entry;
    (*new).next = *head_ptr;
    (*new).prev = NULL;

    // old head element needs it's "previous" pointer to be changed
    (**head_ptr).prev = new;

    // update the head pointer to the new head element
    *head_ptr = new;
}

void insertAtIndex(int entry, int index, struct ListElement** head_ptr) {
    /*
    Inserts a new list element at the specified index. If index is out of bounds, no new
    element is inserted.

    If index is 0, the new element needs to be inserted at the head of the list, so the
    previously defined function needs to be called, so this function also requires &head
    to be passed.
    */
    struct ListElement* current = *head_ptr;
    struct ListElement* new;
    new = allocateNewListElement();

    if       (index == 0)                             {insertAtHead(entry, head_ptr);}
    else if  (index == getNumElements(*head_ptr))     {createListElement(entry, head_ptr);}
    else if  (index > getNumElements(*head_ptr))      {printf("insertAtIndex: index %d out of range --- no new element created.\n", index);} // error handling
    else {
        for (int i = 0; i < index; i++) {current = (*current).next;} // move `current` to the correct index

        (*(*current).prev).next = new; // updates the previous element to link forward to the new element

        new -> value = entry;           // new list element
        new -> next = current;          // new element links forward to the current element
        new -> prev = (*current).prev;  // new element links backward to the previous element

        (*current).prev = new;         // updates the current element to link backward to the new element
    }        
}


/*
Destruction functions:

Every time a block of memory is freed, I include a print statement specifying the memory address that gets freed
in order to ensure the correct number of memory blocks are freed. However many elements are destroyed, there 
should be a matching number of lines on stdout saying "[Freeing heap memory at memory address x]"
*/
void destroyHeadElement(struct ListElement** head_ptr) {
    /*
    Destroys the first element of the list corresponding to *head_ptr
    */

    struct ListElement* temp_head = *head_ptr; // temporary pointer to hold memory address of element to be destroyed
    printf("Destroying head list element:\n");
    printf("Head element %d is located at memory address %p\n", temp_head -> value, temp_head);

    (*(*temp_head).next).prev = NULL; // remove reference to head element from second element
    *head_ptr = temp_head -> next;    // dereference double pointer, reassign pointer to head element to point to second element

    printf("Head element reassigned, new head element %d is at memory address %p.\n", (**head_ptr).value, *head_ptr);
    printf("[Freeing heap memory at %p]\n", temp_head); 
    free(temp_head);                  // free memory at previous head element memory address
}

void destroyLastElement(struct ListElement** head_ptr) {
    /*
    Destroys the last element of the list corresponding to *head_ptr 
    */

    struct ListElement* temp_current = *head_ptr;
    struct ListElement* temp_next = temp_current -> next;
    struct ListElement* temp_prev;

    while (temp_next != NULL) { // loops until temp_current is the last list element
        temp_prev    = temp_current;
        temp_current = temp_next;
        temp_next    = temp_current -> next;
    }

    (*temp_prev).next = NULL;

    printf("Destroying last list element:\n");
    printf("[Freeing heap memory at %p]\n", temp_current);
    free(temp_current);
    newline();
}

void destroyIndex(int index, struct ListElement** head_ptr) {
    /*
    Destroys the element at the given index. If the given index is out of range, does nothing.
    */

    struct ListElement* temp_current = *head_ptr;           // temporary pointer to the current list element  (initially head)
    struct ListElement* temp_prev = temp_current -> prev;   // temporary pointer to the previous list element (initially NULL)
    struct ListElement* temp_next = temp_current -> next;   // temporary pointer to the next list element

    if      (index == 0)                              {destroyHeadElement(head_ptr);} // index 0, destroy head element
    else if (index == getNumElements(*head_ptr) - 1)  {destroyLastElement(head_ptr);} // index of last element, destroy last element
    else if (index >= getNumElements(*head_ptr))      {printf("destroyIndex: index %d out of range --- no element destroyed\n", index);} // error handling
    else { 
        for (int i = 0; i < index; i++) {
            // moves temp_current to point at the element at `index`, temp_next and temp_prev similar
            temp_prev    = temp_current;
            temp_current = temp_next;
            temp_next    = temp_current -> next;
        }
        (*temp_prev).next = temp_next;
        (*temp_next).prev = temp_prev;

        printf("Destroying list element at index %d:\n", index);
        printf("[Freeing heap memory at %p]\n", temp_current);
        free(temp_current);
    }
    newline();
}

void destroyValue(int value, struct ListElement** head_ptr) {
    /*
    Destroys the first occurence of `value` in the list.
    */

    int index = searchFor(value, *head_ptr); // gets the index corresponding to the first occurence of `value`
    printf("Destroying first instance of %d...\n", value);

    if (index == -1) {printf("%d not present in list, no action taken.\n", value);}  // make sure `value` actually exists in list
    else {
        printf("Value %d present at index %d.\n", value, index);
        destroyIndex(index, head_ptr);                                               // destroys the list element
    }
}

void destroyList(struct ListElement** head_ptr) {
    /*
    Destroys an entire doubly linked list, reassigns the head pointer to NULL.
    */

    printf("Destroying entire list:\n");

    struct ListElement* temp_current = *head_ptr;
    struct ListElement* temp_next = temp_current -> next;

    int i = 0; // just for testing purposes

    while (temp_next != NULL) {
        // free the current block of memory
        printf("[Freeing heap memory at %p]\n", temp_current);
        free(temp_current);
        i++;

        // move to the next list element
        temp_current = temp_next;
        temp_next = temp_current -> next;
    }
    // the while loop doesn't run when the next == NULL, which means it doesn't free the last list element
    printf("[Freeing heap memory at %p]\n", temp_current);
    free(temp_current);
    i++;

    printf("Freed %d blocks of memory.\n", i); // i increments every time a block of heap memory is freed,
                                               // so it should match the length of the list prior to destruction
    *head_ptr = NULL;

    newline();
}

int getFirst(struct ListElement* head) {
    // head points to the first list element
    return head -> value;
}

int getLast(struct ListElement* head) {
    // head points to the first list element
    struct ListElement* current = head;
    int last;
    while (current != NULL) {
        // if the next element doesn't exist, we've reached the end
        if ( current -> next == NULL ) { last = current -> value; }
        current = (*current).next;
    }
    return last;
}

int getAtIndex(int index, struct ListElement* head) {
    /*
    If you'd like the value from a specific list index, you can use this. Passing index = 0 will 
    behave the same as getFirst, and passing in the last index or higher will behave the same as getLast.
    */
    struct ListElement* current = head;

    if (index >= getNumElements(head)) {
        printf("getAtIndex: index %d out of range --- returned 0.\n", index); // error handling
        return 0;
    } else { 
        for (int i = 0; i < index; i++) {current = (*current).next;}
        return current -> value;
    }
}

int getNumElements(struct ListElement* head) {
    /*
    Sets a pointer `current` to the head list pointer and
    steps through the list until current is NULL. Increments 
    i by one each time to get the total length of the list.
    */

    int i = 0;
    struct ListElement* current = head;

    while (current != NULL) {
        current = (*current).next; // move to the next list element
        i++;
    }
    return i;
}

int searchFor(int value, struct ListElement* head) {
    /*
    Given `value`, searches the list for the first occurence of value and returns the corresponding index.
    If value does not occur in the list, returns -1.
    */
    struct ListElement* current = head;
    int index = 0;
    while (current != NULL) {
        if (value == current -> value) {return index;}
        current = (*current).next;
        index++;
    }

    return -1;
}

int searchForStartingFrom(int value, int index, struct ListElement* head) {
    /*
    Given `value`, searches the list for the first occurence of value AFTER the specified index.
    This can be used to find occurences of given values after the first, if the index of the first
    occurence is found using searchFor.

    If value does not occur anywhere after index, returns -1.
    */
    struct ListElement* current = head;
    for (int i = 0; i < index; i++) {
        current = (*current).next; // moves current to correct index
    }                              /* the loop condition looks a bit weird, but since current intially points 
                                      at index 0, each loop moves current to index i + 1, so it works out        */

    // we only want to look at indicies AFTER `index`, so we move to the index + 1 list element:
    current = (*current).next;
    index++;

    while (current != NULL) {
        if (value == current -> value) {return index;}
        current = (*current).next;
        index++;
    }

    return -1;
}

void appendLists(struct ListElement** head_ptr_list1, struct ListElement** head_ptr_list2) {
    /* 
    Given pointers to the head elements of two lists, append the lists together in order {list1, list2}.

    Takes double pointer arguments so that the pointer to list 2 can be set to NULL
    (pointer to list 1 passed as double pointer for consistency)
    */
   
    struct ListElement* head_list1 = *head_ptr_list1;
    struct ListElement* head_list2 = *head_ptr_list2;

    struct ListElement* current_list1 = head_list1;
    struct ListElement* last_list1;
    while (current_list1 -> next != NULL) {     // loop until the next element is NULL
        current_list1 = (*current_list1).next;  // final value of current_list1 is a point to the last element of list1
    }
    last_list1 = current_list1; // I prefer to have these redundant variables because I want the variable names to make sense.
                                // It makes the code easier to read

    (*last_list1).next = head_list2;
    (*head_list2).prev = last_list1;

    *head_ptr_list2 = NULL;
}