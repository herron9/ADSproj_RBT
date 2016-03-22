//  RBTree.cpp
//  EventCounter
//
//  Copyright © 2016 rr. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "RBtree.h"
#include <math.h>

using namespace std;

static int i=0;

RBTNode::RBTNode(long key, long count){
    this->N_key=key;
    this->N_count=count;
    this->color=BLACK;
    this->parent=NULL;
    this->left=NULL;
    this->right=NULL;
}


RBTree::RBTree(){
    root = NULL;
}

void RBTree::deleteAll()
{
    deleteAll(root);
}

RBTree::~RBTree()
{
//    deleteAll();
}


//constructs BBST from a sorted array
RBTNode* ArrayToBST(vector<RBTNode> & node, long start, long end,int height,long size)
{
    height++;
    
    if (start > end) return NULL;
    //Get the middle element and make it root
    long mid = (start + end)/2;
    
    RBTNode *root = &node[mid];
    
    //Recursively construct the left subtree and make it left child of root
    root->left = ArrayToBST(node, start, mid-1,height,size);
    if (root->left!= nullptr) root->left->parent = root;
    
    //Recursively construct the right subtree and make it right child of root
    root->right = ArrayToBST(node, mid+1, end,height,size);
    if (root->right!= nullptr) root->right->parent = root;
   
    long h=log2(size);
    if(height>h) node[mid].color=RED;//set leaves in the last degree red
    return root;
}

void RBTree::setRoot(RBTNode *froot){
    this->root= froot;
}

RBTNode* RBTree::getRoot(){
    return root;
}
void RBTree::increase(long id, long Num){
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(id)) != NULL){
        node->N_count=node->N_count+Num;
        cout<<node->N_count<<endl;
    }else
    {
        insert(id, Num);
        cout<<Num<<endl;
    }

}

void RBTree::reduce(long id, long dec){
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(id)) != NULL){//exist
        node->N_count=node->N_count-dec;
        if (node->N_count<=0) {// count<=0
            remove(id);
            cout<<0<<endl;
        }else{
            cout<<node->N_count<<endl;
        }
    }else// doesn't exist
    {
        cout<<0<<endl;
    }
    
}

void RBTree::count(long id){
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(id)) != NULL){
        cout<<node->N_count<<endl;
    }else
    {
        cout<<0<<endl;
    }
}

void RBTree::next(long id){
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(id)) != NULL){
        RBTNode *newroot =node->right;//case has right child
        if (newroot != NULL){//next is the leftmost node in right subtree
            while(newroot->left != NULL) newroot = newroot->left;
            cout<<newroot->N_key<<" "<<newroot->N_count<<endl;
        }else{
            //case no right child
            RBTNode * p = node->parent;
            if (p->left==node) cout<<p->N_key<<" "<<p->N_count<<endl;//node is a left child
            else{
                while ((p!=NULL) && (node==p->right))//node is a right child
                {
                    node = p;
                    p = p->parent;
                }
                if (p==NULL) {//given id is the largest node of the tree
                    cout<<"0 0"<<endl;
                } else cout<<p->N_key<<" "<<p->N_count<<endl;
            }
        }
    }
}

void RBTree::previous(long id){
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(id)) != NULL){
        RBTNode *newroot =node->left;//case has left child
        if (newroot != NULL){//previous is the rightmost node in left subtree
            while(newroot->right != NULL) newroot = newroot->right;
            cout<<newroot->N_key<<" "<<newroot->N_count<<endl;
        }else{
            //case no left child
            RBTNode * p = node->parent;
            if (p->right==node) cout<<p->N_key<<" "<<p->N_count<<endl;//node is a right child
            else{
                while ((p!=NULL) && (node==p->left))//node is a left child
                {
                    node = p;
                    p = p->parent;
                }
                if (p==NULL) {//given id is the smallest node of the tree
                    cout<<"0 0"<<endl;
                } else cout<<p->N_key<<" "<<p->N_count<<endl;
            }
        }
    }

    
}

RBTNode* RBTree::findPivot(long id1, long id2){
    RBTNode *node =root;
    if(node!=NULL) {
        if (node->N_key>=id1&&node->N_key<=id2) {//root in the range
            return node;
        }
        while(node!=NULL&&(node->N_key>id2||node->N_key<id1)) {
            if (node->N_key>id2) {
                node=node->left;
            }
            if (node->N_key<id1) {
                node=node->right;
            }
        }
    }
    return node;

}

long RBTree::sumCount(RBTNode *node){
    long sum=0;
    if(node != NULL)
    {
        sum=node->N_count+sumCount(node->left)+sumCount(node->right);
    }
    return sum;
}

void RBTree::inrange(long id1, long id2)
{
    RBTNode* pivot=findPivot(id1, id2);
    if(pivot==NULL) cout<<0<<endl;
    else{
        if (pivot->left==NULL&&pivot->right==NULL) {// pivot is a leaf
            cout<<pivot->N_count<<endl;
        }else{
            long sumINIT=pivot->N_count;
            long sumL=0;
            long sumR=0;
            RBTNode*pivotL =pivot->left;
            RBTNode*pivotR =pivot->right;
            while (pivotL!=NULL&&(pivotL->left!=NULL||pivotL->right!=NULL)) {//isn't a leaf
                if (pivotL->N_key>=id1) {
                    sumL=sumL+sumCount(pivotL->right)+pivotL->N_count;
                    pivotL=pivotL->left;
                }else{
                    pivotL=pivotL->right;
                }
            }
            if (pivotL!=NULL&&pivotL->N_key>=id1) sumL=sumL+pivotL->N_count;
            
            while (pivotR!=NULL&&(pivotR->left!=NULL||pivotR->right!=NULL)) {//isn't a leaf
                if (pivotR->N_key<=id2) {
                    sumR=sumR+sumCount(pivotR->left)+pivotR->N_count;
                    pivotR=pivotR->right;
                }else{
                    pivotR=pivotR->left;
                }
            }
            if (pivotR!=NULL&&pivotR->N_key<=id2) sumR=sumR+pivotR->N_count;
            
            cout<<sumL+sumR+sumINIT<<endl;
        }
    }

}

void RBTree::leftRotate(RBTNode* &root, RBTNode* x)
{
    RBTNode *y = x->right;
    x->right = y->left;//set x's new rchild
    if (y->left != NULL) y->left->parent = x;//set y's parent
    y->parent = x->parent;// y replace x as the new child of px
    
    if (x->parent == NULL)
    {
        root = y;
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;//set x's new parent
}

void RBTree::rightRotate(RBTNode* &root, RBTNode* y)
{
    RBTNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;
    x->parent = y->parent;
    
    if (y->parent == NULL)
    {
        root = x;
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}


void RBTree::insert(RBTNode* &root, RBTNode* node)
{
    RBTNode *search = NULL;
    RBTNode *Troot = root;

    while (Troot != NULL)//find parent for new node
    {
        search = Troot;
        if (node->N_key < Troot->N_key) Troot = Troot->left;
        else Troot = Troot->right;
    }
    node->parent = search;
    
    if (search!=NULL)//parent exist
    {
        if (node->N_key < search->N_key) search->left = node;
        else search->right = node;
    }
    else root = node;//empty tree
    node->color = RED;
    

    insertRebalance(root, node);//rebalance
}

void RBTree::insert(long key,long count)
{
    RBTNode *node=NULL;
    node=  new RBTNode(key, count);
    insert(root, node);
}

void RBTree::insertRebalance(RBTNode* &root, RBTNode* node)
{
    RBTNode *p, *gp;
    while ((p = parentOf(node)) && isred(p))//node has parent and its color is Red
    {
        gp = parentOf(p);//p has parent
        //case XYr: push the deficient up the tree
        if (p == gp->left)//p is lc of gp and uncle is Red
        {
            RBTNode *uncle = gp->right;
            if (uncle && isred(uncle))
            {
                setBLACK(uncle);
                setBLACK(p);
                setRED(gp);
                node = gp;//new rebalancing node
                continue;
            }
            
            //case LLb: p&n are Red and U is black
            if (p->left == node)
            {
                setBLACK(p);
                setRED(gp);
                rightRotate(root, gp);
            }else//case LRb p->right== node
            {
                RBTNode *tmp;
                leftRotate(root, p);
                tmp = p;
                p = node;
                node = tmp;//update parent-child relationship
            }
        }
        else//p is rc of gp and uncle is Red
        {
            RBTNode *uncle = gp->left;
            if (uncle && isred(uncle))
            {
                setBLACK(uncle);
                setBLACK(p);
                setRED(gp);
                node = gp;
                continue;
            }
            if (p->right == node)//case RRb
            {
                setBLACK(p);
                setRED(gp);
                leftRotate(root, gp);
            }else{//case RLb
                RBTNode *tmp;
                rightRotate(root, p);
                tmp = p;
                p = node;
                node = tmp;
            }

        }
    }
    setBLACK(root);
}

void RBTree::remove(RBTNode* &root, RBTNode *node)
{
    RBTNode *child, *parent;
    NodeColor color;

    if ( (node->left!=NULL) && (node->right!=NULL) )//delete degree 2 node
    {
        RBTNode *replace = node;
        replace = replace->left;//root of node's left subtree
        while (replace->right != NULL)
            replace = replace->right;//get the largeest child in left subtree
        
        if (parentOf(node))//node isn't root
        {
            if (parentOf(node)->left == node)//node is left child
                parentOf(node)->left = replace;
            else
                parentOf(node)->right = replace;//node is right child
        }
        else root = replace;//node is root
        
        child = replace->left;//replace may have left but no right child
        parent = parentOf(replace);
        color = getColor(replace);
        
        if (parent == node)//replace is the driect child of node
        {
            parent = replace;
        }
        else
        {
            if (child) setParent(child, parent);//let child be the child of replace's parent
            parent->right = child;//child:exist or NULL
            replace->left = node->left;
            setParent(node->left, replace);
        }
        setParent(replace, node->parent);
        setColor(replace, node->color);
        replace->right = node->right;
        node->right->parent = replace;
        
        if (color == BLACK)//deleted a black node, subtree became deficient
            removeRebalance(root, child, parent);
        delete node;
        node=NULL;
        return;
    }
    //delete  degree 1 node
    if (node->left !=NULL) child = node->left;
    else child = node->right;
    
    parent = node->parent;
    color = node->color;
    
    if (child)//degree 1
        child->parent = parent;
    
    if (parent)//deleted node isn't root
    {
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else root = child;
    
    if (color == BLACK) //deleted a black node, subtree became deficient
        removeRebalance(root, child, parent);
    
//    delete node;//degree 0 or degree 1;
    node=NULL;
}


void RBTree::remove(long key)
{
    RBTNode *node = new RBTNode(0,0);
    if ((node = search(root, key)) != NULL)
        remove(root, node);
}

void RBTree::removeRebalance(RBTNode* &root, RBTNode *node, RBTNode *parent)
{
    RBTNode *sibling;
    
    while ((!node || isblack(node)) && node != root)
    {
        if (parent->left == node)//node is the leftC of p
        {
            sibling = parent->right;
            if (isred(sibling))//case1 node B sibling R
            {
                setBLACK(sibling);
                setRED(parent);//black in perivous
                leftRotate(root, parent);
                sibling = parent->right;
            }//else sibling is BLACK
            if ((!sibling->left || isblack(sibling->left)) &&//child of sibling are B
                (!sibling->right || isblack(sibling->right)))
            {
                setRED(sibling);
                node = parent;
                parent = parentOf(node);
            }
            else//exist Red child of sibling
            {
                if (!sibling->right || isblack(sibling->right))//rightC black
                {
                    setBLACK(sibling->left);
                    setRED(sibling);
                    rightRotate(root, sibling);
                    sibling = parent->right;
                }
                setColor(sibling, getColor(parent));//rightC random
                setBLACK(parent);
                setBLACK(sibling->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else//node is the rightC of p
        {
            sibling = parent->left;
            if (isred(sibling))//sibling is red
            {
                setBLACK(sibling);
                setRED(parent);
                rightRotate(root, parent);
                sibling = parent->left;
            }
            if ((!sibling->left || isblack(sibling->left)) &&
                (!sibling->right || isblack(sibling->right)))
            {
                setRED(sibling);
                node = parent;
                parent = parentOf(node);
            }
            else
            {
                if (!sibling->left || isblack(sibling->left))
                {
                    setBLACK(sibling->right);
                    setRED(sibling);
                    leftRotate(root, sibling);
                    sibling = parent->left;
                }
                setColor(sibling, getColor(parent));
                setBLACK(parent);
                setBLACK(sibling->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node) setBLACK(node);
}




RBTNode* RBTree::search(RBTNode* Sroot, long key) const
{
    while ((Sroot!=NULL) && (Sroot->N_key!=key))//tree isn't empty and root!=target
    {
        if (key < Sroot->N_key)  Sroot = Sroot->left;
        else                     Sroot = Sroot->right;
    }
    
    return Sroot;

}

RBTNode* RBTree::search(long key)
{
     return search(root, key);//???
}

void RBTree::print(RBTNode* tree, long key, int direction)
{
    if(tree != NULL)
    {
        isred(tree)? i++:i;
        if(direction==0)
            cout <<" "<< tree->N_key<<" "<<tree->N_count<< "(B) is root" << endl;
        else
            cout <<" "<< tree->N_key <<" "<<tree->N_count<<  (isred(tree)?"(R)":"(B)") << " is " << key << "'s "  << " "
            << (direction==1?"right child" : "left child") << endl;
        print(tree->left, tree->N_key, -1);
        print(tree->right,tree->N_key,  1);
    }
}

void RBTree::print()
{
    if (root!= NULL)
        i=0;
        print(root, root->N_key, 0);
    cout<<"there are "<<i<<" Rs"<<endl;
}

void RBTree::deleteAll(RBTNode* &tree)
{
    if (tree==NULL)
        return ;
    
    if (tree->left != NULL)
        return deleteAll(tree->left);
    if (tree->right != NULL)
        return deleteAll(tree->right);
    
    delete tree;
    tree=NULL;
}