/* 
 * Kimberly Camanero 
 * kcamaner
 * 2024 Fall CSE101 PA1
 * Lex.c
 * main program creates the array of linked lists and lexicographically sorts the words using insertion sort 
 * Created on September 30, 2024, 4:47 PM
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define LINE_BUFFER 500 //to declare the max word length of each line

int main(int const argc,char** argv) { //[program name,input file,output file]

    if(argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    //create a file "stream"
    FILE* const inputFile = fopen(argv[1],"r");
    FILE* const outputFile = fopen(argv[2],"w");
    if(inputFile  == NULL) {
        printf("error opening file\n");
    }
    if(outputFile == NULL) {
        printf("error opening file\n");
        exit(1);
    }
    
    //count the number of lines in the input file
    int n = 0;
    char line[LINE_BUFFER];
    while(fgets(line,LINE_BUFFER,inputFile) != NULL) {
        n+=1;
    }
    
    rewind(inputFile); //move the pointer of the file to the beginning of the file
//    //delete line 28 bro, just counts the number of lines in a file
//    fprintf(outputFile,"%d\n",n);
    
    //creating the array for the words
    char **wordArray = malloc(n * sizeof(char *));
    if(wordArray == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n",argv[1]);
        exit(1);
    }
    
    //going through the file and storing each word into the array 
    for(int i=0;i<n;i++) {
        fgets(line,LINE_BUFFER,inputFile);
        wordArray[i] = strdup(line);
        if(wordArray[i] == NULL) {
            fprintf(stderr, "memory allocation failed\n");
            exit(1);
        }
    }
    // create list
    List list = newList();


    // insertion sort
    append(list, 0);
    for (int i = 0; i< n; i++){
        moveFront(list);
        while(index(list) != length(list) - 1 && strcmp(wordArray[i], wordArray[get(list)]) > 0){
            moveNext(list);
        }
        insertBefore(list, i);
    }


    //printing it
    moveFront(list);
    int x = 0;
    while(n > x){
        fprintf(outputFile, "%s", wordArray[get(list)]);
        moveNext(list);
        x++;
    }

    //free memory
    for(int i = 0; i < n; i++){
        free(wordArray[i]);
    }
    free(wordArray);
    freeList(&list);

    //closing files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}