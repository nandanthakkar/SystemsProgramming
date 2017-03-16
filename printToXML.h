//
//  printToXML.h
//  RecursiveIndexing
//
//  Created by Nandan Thakkar on 3/16/17.
//  Copyright © 2017 Nandan Thakkar. All rights reserved.
//

#ifndef printToXML_h
#define printToXML_h

typedef struct _HashNode{
    char* filename;
    int token_count;
    struct _HashNode* next;
}HashNode;

typedef struct _Node{
    char* token;
    struct _Node * next;
}Node;




void stroll_through_files(char* root_dir);

//function that reads the file
void read_files(char* filepath);

// print Token Data in following way: <word text=”word0”><file name=”filename0”>count0</file></word>
void printTokenData();

// start writing XML file: <?xml version="1.0" encoding="UTF-8"?> <fileIndex>

void exortToXML();

// pass key as parameter. key will be used to map its value. Value will be returned.
HashNode * getHashNode(char * key);

// get file discriptor if path leads to file.
int getFileDescriptor(char * path);

// scroll file or directory
void scrollDir(char * path);

// parameter is file descriptor and use that fd to tokenize strings from file.
void tokenize(int );
#endif /* printToXML_h */
