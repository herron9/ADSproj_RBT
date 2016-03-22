//
//  RBtree.h
//  EventCounter
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef RBtree_h
#define RBtree_h
#include <vector>

using namespace std;

enum NodeColor{
    RED,
    BLACK};

class RBTNode{
public:
    NodeColor color;
    long N_key;
    long N_count;
    RBTNode *parent;
    RBTNode *left;
    RBTNode *right;
    

    RBTNode(long key, long count);//default initialization
    
};

RBTNode* ArrayToBST(vector<RBTNode> &node, long start, long end,int height,long size);//buildTree

class RBTree {
private:
    RBTNode *root;
    
public:
    RBTree();
    ~RBTree();
    
    void setRoot(RBTNode *root);
    RBTNode* getRoot();
    void insert(long key,long count);
    
    RBTNode* search(long key);
    void remove(long key);
    
    void deleteAll();
    void increase(long key,long count);
    void reduce(long key,long count);
    void count(long key);
    void next(long key);
    void previous(long key);
    
    RBTNode* findPivot(long id1,long id2);
    long sumCount(RBTNode *node);
    void inrange(long id1,long id2);
    
    // 前序遍历"红黑树"
    void preOrder();
    // 中序遍历"红黑树"
    void inOrder();
    // 后序遍历"红黑树"
    void postOrder();
    
    void print();
private:
    void insert(RBTNode* &root, RBTNode* node);
    void insertRebalance(RBTNode* &root, RBTNode* node);
    
    RBTNode* search(RBTNode* x, long key) const;
    void remove(RBTNode* &root, RBTNode *node);//delete node
    void removeRebalance(RBTNode* &root, RBTNode *node, RBTNode *parent);
    
    void print(RBTNode* tree, long key, int direction);
    void deleteAll(RBTNode* &tree);

    
    // 前序遍历"红黑树"
    void preOrder(RBTNode* tree) const;
    // 中序遍历"红黑树"
    void inOrder(RBTNode* tree) const;
    // 后序遍历"红黑树"
    void postOrder(RBTNode* tree) const;
    // 左旋
    void leftRotate(RBTNode* &root, RBTNode* x);
    // 右旋
    void rightRotate(RBTNode* &root, RBTNode* y);
    
#define parentOf(r)   ((r)->parent)
#define getColor(r) ((r)->color)
#define isred(r)   ((r)->color==RED)
#define isblack(r)  ((r)->color==BLACK)
#define setBLACK(r)  do { (r)->color = BLACK; } while (0)
#define setRED(r)  do { (r)->color = RED; } while (0)
#define setParent(r,p)  do { (r)->parent = (p); } while (0)
#define setColor(r,c)  do { (r)->color = (c); } while (0)
};

#endif /* RBtree_h */
