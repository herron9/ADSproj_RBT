//
//  main.cpp
//  EventCounter
//  Copyright © 2016 rr. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "RBtree.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    time_t start = clock();
    string filename = argv[1];
    ifstream file(filename);
    int j=0;
    long size;
    file>>size;
    long id;
    long count;
    vector<RBTNode> nodelist;
    
    while (j<size) {
        file>>id>>count;
        RBTNode *node = new RBTNode(0,0);
        node->N_key=id;
        node->N_count=count;
        nodelist.push_back(*node);
        j++;
    }

    file.close();
    RBTree tree;
    tree.setRoot(ArrayToBST(nodelist, 0, size-1,0,size));
    
    time_t end = clock();
    printf("the running time is : %f\n", double(end -start)/CLOCKS_PER_SEC);
    
    string fn;
    long p1=0;
    long p2=0;
    while (cin>>fn) {
        if (fn == "quit") break;
        if (fn=="increase"&&cin>>p1>>p2) tree.increase(p1,p2);
        if (fn=="reduce"&&cin>>p1>>p2)   tree.reduce(p1,p2);
        if (fn=="count"&&cin>>p1)        tree.count(p1);
        if (fn=="inrange"&&cin>>p1>>p2)  tree.inrange(p1,p2);
        if (fn=="next"&&cin>>p1)         tree.next(p1);
        if (fn=="previous"&&cin>>p1)     tree.previous(p1);
    }
    return 0;
}

