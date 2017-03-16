//
//  main.c
//  RecursiveIndexing
//
//  Created by Nandan Thakkar on 3/13/17.
//  Copyright © 2017 Nandan Thakkar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "printToXML.h"

//will resize as the hashtable resizes
HashNode tok_table[100];
static int i = 0;
//linked list that stores the keys to the hashtable in alphanumeric order
static Node* keyset_root;

FILE * fp;

void printTokenData(){
    Node * temp = keyset_root;
    HashNode * ptr;
    while(temp != NULL){
        fprintf(fp, "\t<word text=\"%s\">\n", temp->token);
        ptr = getHashNode(temp->token);
        while(ptr != NULL){
            fprintf(fp, "\t\t<file name=\"%s\">%d</file>\n",ptr->filename,ptr->token_count);
            ptr = ptr->next;
        }
        fprintf(fp, "\t</word>\n");
        temp = temp->next;
    }
    return;
}

void exportToXML(){
    if ((fp = fopen("/Users/jollythakkar/Documents/RecursiveIndexing/RecursiveIndexing/export.xml", "w")) == NULL){
        
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<fileIndex>\n");
    printTokenData();
    fprintf(fp, "</fileIndex>\n");

}

//just for testing. but its implementation is needed.
HashNode * getHashNode(char * tok){
    HashNode * temp = &tok_table[i];
    i++;
    return temp;
    
}

//just for testing
int main(int argc, const char * argv[]) {
    // insert code here...
    keyset_root = (Node *) malloc(sizeof(Node));
    char * str = (char *)malloc(7);
    str = "Nandan";
    keyset_root->token = str;
    keyset_root->next = (Node *) malloc(sizeof(Node));
    Node * pointer= keyset_root;
    pointer = pointer-> next;
    str = (char *)malloc(5);
    str = "Doug";
    pointer->token = str;
    pointer->next = NULL;
    
    str = (char *)malloc(6);
    str = "file1";
    tok_table[0].filename = str;
    tok_table[0].token_count = 2;
    tok_table[0].next = (HashNode*)malloc(sizeof(HashNode));
    HashNode * pptr = tok_table[0].next;
    str = (char *)malloc(6);
    str = "file2";
    pptr->filename = str;
    pptr->token_count = 5;
    pptr->next = NULL;
    
    str = (char *)malloc(6);
    str = "file3";
    tok_table[1].filename = str;
    tok_table[1].token_count = 10;
    tok_table[1].next = (HashNode*)malloc(sizeof(HashNode));
    pptr = tok_table[1].next;
    str = (char *)malloc(6);
    str = "file4";
    pptr->filename = str;
    pptr->token_count = 50;
    pptr->next = NULL;
    
    exportToXML();
    printf("%s\n", keyset_root->token);
    printf("Hello, World!\n");
    return 0;
}
