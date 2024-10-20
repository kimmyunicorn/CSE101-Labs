/* 
 * File:   List.c
 * Author: kimberlycamanero
 *
 * Created on October 15, 2024, 5:54 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

List newList(void){
    List L = malloc(sizeof(struct ListObj)); //creates memory for my list
    L->cursor = NULL;
    L->front = NULL;
    L->back = NULL;
    L->index = -1;
    L->length = 0;
    return L;
}

Node newNode(int x) {
    Node createdNode = malloc(sizeof(struct NodeObj)); //creates memory for the new node 
    createdNode->data = x;
    createdNode->next = NULL;
    createdNode->prev = NULL;
    return createdNode;
}


void freeList(List* pL){ //free's the memory in the list

    //pL is a pointer to my list
    //check if train exists
    if (pL == NULL || *pL == NULL){ //checking if the pointer is null or if the actual node data is null 
        printf("List is empty\n");
        exit(1);
    }

    //un-latching from inside the train
    Node current = (*pL)->front;
    Node temp;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    //resetting everything back to nothing
    (*pL)->cursor = NULL;
    (*pL)->front = NULL;
    (*pL)->back = NULL;
    (*pL)->index = -1;
    (*pL)->length = 0;

    free(*pL);
    *pL=NULL;
}

void freeNode(Node* ptrNode){ //free's the memory associated w/ the node 
    if(*ptrNode != NULL && ptrNode != NULL){
        free(*ptrNode);
        *ptrNode = NULL;
    }
}


int length(List L){
    if (L == NULL){
        return 0;
    }
    return L->length;
}

int index(List L){
    if (L->cursor == NULL){ //undefined cursor means tht the index has been reset 
        return -1;
    }
    return L->index; //otherwise u would return a valid index 
}

int front(List L) {
    //check if the list itself is null
    if(L == NULL){
        printf("List is NULL\n");
        exit(1);
    }
    //check if the list length is greater than 0
    if(length(L) == 0){
        printf("list doesnt have any data/information\n");
        exit(1);
    }
        return L->front->data;
}

int back(List L) {
    //list doesnt even exist
    if(L == NULL){
        printf("List is NULL\n");
        exit(1);
    }
    //list has no information
    if(length(L) == 0){
        printf("list doesnt have any data/information");
        exit(1);
    }

    return L->back->data;
}

int get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0

    //check if the list is NULL
    if(L == NULL){
        exit(1);
    }
    if(length(L) > 0 && index(L) >= 0) {  //preconditions
        return L->cursor->data;
    }else {
        printf("list doesnt have any data/information\n");
        exit(1);
    }
}

bool equals(List A, List B){// true iff Lists A and B contain the same data, false otherwise

    //special case where both lists are NULL then they are equivalent
    if(A == NULL && B == NULL){
        return true;
    }

    //check if either list is NULL
    if(A == NULL || B == NULL){
        printf("One of the lists is NULL\n");
        return false;
    }

    //compare the lengths of the linked list, cant b the same if not equivalent lengths
    if(length(A) != length(B)){
        return false;
    }

    //preparing to traverse through the lists
    Node currentFirstList = A->front; //head node of the first list
    Node currentSecondList = B->front; //head node of the second list

    while(currentFirstList != NULL && currentSecondList != NULL){
        if(currentFirstList->data != currentSecondList->data){
            return false;
        }else{
            //continue iterating through the lists
            currentFirstList = currentFirstList->next;
            currentSecondList = currentSecondList->next;
        }
    }
     return true;
}


void set(List L, int x){
    if(L == NULL){ //check if the list is NULL
        exit(1);
    }
    if(length(L)>0 && index(L) >= 0){//checking for the pre-conditions
    //is not pointing to NULL
        L->cursor->data = x;
    }
}

void moveFront(List L){
    if(L == NULL){
        exit(1);
    }
    //checking if L is non empty, therefore checking the length of the list
    if(length(L) > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr,"Cursor is NULL\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->back;
//        L->index = length(L)-1;
        L->index = L->length -1;
    }
}

void movePrev(List L){
    //cursor is undefined
    if(L  == NULL){
        fprintf(stderr,"List is NULL\n");
        exit(1);
    }

    //cursor is defined & not @ the front
    if(L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->prev;
        L->index -= 1;
    }else{
        L->cursor = NULL;
//        L->index = -1;
    }
}

void moveNext(List L){
    //cursor is undefined
    if(L == NULL){
        fprintf(stderr,"List is NULL\n");
        exit(1);
    }
    if(L->cursor != NULL && L->cursor != L->back){ //cursor is not null and the cursor is also not @ the back of the list 
        L->cursor = L->cursor->next;
        L->index +=1;
    }else{//cursor is not null and the cursor is @ the back of the list
        L->cursor = NULL;
//        L->index = -1;
    }
}

void clear(List L){ //frees the memory associated w/ the node 
    Node current = L->front;
    Node temp;
    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    //reset everything back
    L->cursor = NULL;
    L->front = NULL;
    L->back = NULL;
    L->index = -1;
    L->length = 0;
}


void prepend(List L, int x){
   //check if the list is not NULL
   if(L == NULL){
       return;
   }

   //create a new node
   Node createdNode = newNode(x);
   if(createdNode == NULL){
       printf("Memory allocation failed\n");
   }
   //if the list is empty, then the new node becomes the head and the tail
   if(length(L) == 0){
       L->front = createdNode;
       L->back = createdNode;
       L->cursor = createdNode;
   }else{//if list is non empty
       createdNode->next = L->front; //new node becomes the front of the list
       L->front->prev = createdNode; //pointer to the previous of old node becomes the new node
       L->front = createdNode;
        //whenever u prepend to a list, the cursor element increases by 1
        if(L->cursor != NULL) {
            L->index +=1;
        }
   }
   L->length+=1;
}


void append(List L, int x) {
    //check if the list is NULL
    if(L == NULL) {
        printf("List is NULL\n");
        exit(1);
    }
    //create a new node
    Node createdNode = newNode(x);
    if(createdNode == NULL) { //check if creating the node was successful
        printf("Memory allocation failed\n");
        exit(1);
    }
    //case that L is empty, appending a node makes it tail n head
    if(length(L) == 0){
        L->front = createdNode;
        L->back = createdNode;
        L->cursor = createdNode;
//        L->length += 1;
    }else { //list is non empty
        createdNode->prev = L->back;
        L->back->next = createdNode;
        L->back = createdNode;
//        createdNode->next = NULL;
//        L->length +=1;
    }
    L->length+=1;
}


void insertBefore(List L, int x) {
    //check if the list is NULL
    if(L == NULL) {
        printf("List is NULL\n");
        exit(1);
    }
    //checking for the preconditions 
    if(length(L) > 0 && index(L)>=0){
        if(L->cursor == L->front){
            prepend(L,x);
        }else{
            //create a new node
            Node createdNode = newNode(x);
            if(createdNode == NULL) { //check if creating the node was successful
                printf("Memory allocation failed\n");
                exit(1);
            }
            //redirect the pointers
            createdNode->prev = L->cursor->prev;
            createdNode->next = L->cursor;
            L->cursor->prev->next = createdNode;
            L->cursor->prev = createdNode;
            L->length +=1;
            L->index +=1;
        }
    }
}

void insertAfter(List L, int x) {
    if(L == NULL) {
        fprintf(stderr,"List is NULL\n");
        exit(1);
    }
    //insertion after the last element(tail)
    if(length(L) > 0 && index(L) >= 0){
        if(L->cursor == L->back) {
            append(L,x); //if this one doesnt work check append
        }else {  //insertion into the middle of the list
            //create the new node now tht u have verified preconditions have been met
            Node createdNode = newNode(x);
            if(createdNode == NULL) {
                fprintf(stderr,"Memory allocation failed\n");
                exit(1);
            }
            //redirect the pointers 
            createdNode->prev = L->cursor;
            createdNode->next = L->cursor->next;
            L->cursor->next->prev = createdNode;
            L->cursor->next = createdNode;
            L->length +=1;
            L->index+=1;
        }
    }
}

void deleteFront(List L) {
    //check if the list is NULL
    if(L == NULL) {
        printf("Trying to delete an empty list\n");
        exit(1);
    }
    //check if the list is empty
    if(length(L) <= 0) {
        printf("List is empty\n");
        exit(1);
    }
    Node temp = L->front;
    if(length(L) > 1){ //in the case that the list has more than 1 node 
        L->front = L->front->next;
        L->front->prev = NULL;
        L->length -=1;
        L->index -=1;
    }else{//list has 1 node or no nodes
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length -=1;
        L->index -=1;
    }
    freeNode(&temp);
    
}

void deleteBack(List L) {
    //check if the list is NULL
    if(L == NULL) {
        fprintf(stderr,"Trying to delete from a NULL list\n");
        exit(1);
    }
    //check if the list is empty
    if(length(L) <= 0) {
        printf("calling delete back on list whos length < 0 \n");
        exit(1);
    }
      Node temp = L->back;   // Temporarily store the current back node
    // checking if the cursor is pointing to the tail of the list 
    if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
      //reassigning the 2nd to last nodes pointer so that it can now point to null 
      L->back = L->back->prev;
      if(L->back != NULL){
          L->back->next = NULL;
      }
      L->length-=1;
      freeNode(&temp); //free memory for the node u just removed 
      
}


void delete(List L){
    //check if the list is NULL
    if(L == NULL) {
       fprintf(stderr,"Trying to delete a NULL list\n");
        exit(1);
    }
    if(length(L) > 0 && index(L) >= 0){ //checking for the preconditions 
        Node cursorNode = L->cursor;
        if(L->cursor == L->front){ //if the cursor is pointing the head of the list 
            deleteFront(L);
        }else if(L->cursor == L->back){ //if cursor is pointing to the tail of the list 
            deleteBack(L);
        }else if(length(L) == 1){ //when the list only has one node 
            L->cursor = NULL;
            L->index -= 1;
            freeNode(&cursorNode);
        }else{//when the list is populated and cursor is somewhere in the middle of the list 
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            L->cursor = NULL;
            L->index -= 1;
            L->length -=1;
            freeNode(&cursorNode);
        }
    }
}
    
   

void printList(FILE* out, List L){
    //CASE 1: If it is @ NULL then just return ERROR
    if (L == NULL) {
        printf("List is NULL\n");
        exit(1);
    }
    //HOWEVER, if it is not @ NULL then we start by being @ the head and we work our way to the right (until we reach the tail)
    Node current = L->front;
    fprintf(out,"[");
    while (current != NULL) { //while head does not equal NULL, we keep going to the next item
        if (current->next) {
            fprintf(out,"%d ", current->data);
        } else {
            fprintf(out,"%d]\n", current->data); //once it hits the end, it will print the last data followed by a closing bracket& will start a new line
        }
        current = current->next;
    }
}

List copyList(List L) {
    if(L == NULL) {
        printf("List is NULL\n");
    }
    //initialize space for a new list
    List copyList = newList();
    //preserve the "head" of the list
    Node current = L->front;
    while(current != NULL) {
        append(copyList,current->data);
        current = current->next;
    }
    return copyList;
}
