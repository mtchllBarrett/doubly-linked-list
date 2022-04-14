#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    // an element of the doubly-linked list
    int value;
    struct ListElement* next;
    struct ListElement* prev;
};

struct ListElement* allocateNewListElement(void);

void createListElement(int, struct ListElement**);
void insertAtHead(int, struct ListElement**);
void insertAtIndex(int, int, struct ListElement**);

int getFirst(struct ListElement*);
int getLast(struct ListElement*);
int getAtIndex(int, struct ListElement*);
int getNumElements(struct ListElement*);

struct ListElement* allocateNewListElement(void) {
    /*
    Just to make things slightly more explicit in the functions to follow,
    I have defined this function to simply create a new memory allocation
    for the doubly linked list.

    Integers occupy 4 bytes and pointers occupy 8, so in total a ListElement
    struct requires 20 bytes of memory, which I've just hardcoded directly
    into the malloc call.

    Returns a pointer to the new memory allocation.
    */
    return (struct ListElement*) malloc(20);
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
    Inserts a new list element at the specified index. If index is out of bounds, this
    function probably breaks, so it is recommend to not do that. (This is something I
    would have spent more time fixing if I had unlimited time to work on this)

    If index is 0, the new element needs to be inserted at the head of the list, so the
    previously defined function needs to be called, so this function also requires &head
    to be passed.
    */
    struct ListElement* current = *head_ptr;
    struct ListElement* new;
    new = allocateNewListElement();

    if (index == 0) { insertAtHead(entry, head_ptr); }
    else {
        for (int i = 0; i < index; i++) {current = (*current).next;} // move `current` to the correct index

        (*(*current).prev).next = new; // updates the previous element to link forward to the new element

        new -> value = entry;           // new list element
        new -> next = current;          // new element links forward to the current element
        new -> prev = (*current).prev;  // new element links backward to the previous element

        (*current).prev = new;         // updates the current element to link backward to the new element
    }        
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

    if (index + 1 > getNumElements(head)) {
        printf("getAtIndex: index out of range --- returned last element instead.\n");
        return getLast(head);
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

int main(void) {

    struct ListElement* head = NULL;

    createListElement(21, &head);
    createListElement(13, &head);
    createListElement(9, &head);

    int first = getFirst(head);
    int last = getLast(head);
    int len = getNumElements(head);

    printf("Head element is %d at memory address %p.\n", head->value, head);
    printf("Last element is %d.\n", last);
    printf("Length of the list is %d.\n", len);

    insertAtHead(250, &head);
    int newLen = getNumElements(head);
    printf("Head element updated:\n");
    printf("Head element is %d at memory address %p.\n", head->value, head);
    printf("Next element is %d at memory address %p.\n", head->next->value, head->next);
    printf("Next length of the list is %d.\n", newLen);

    printf("3rd element is %d.\n", getAtIndex(2, head));

    return 0;
}