#include "tree.h"

Tree::Tree (char a) : tag (a), leaf (true){}

Tree::Tree (Tree* left, Tree* right, char a) : tag (a), leaf (false){
    children.resize (2);
    children [0] = left;
    children [1] = right;
}

Tree* Tree::leftChild (){
    return children [0];
}

Tree* Tree::rightChild (){
    return children [1];
}

const char Tree::tagValue (){
    return tag;
}

const bool Tree::isLeaf (){
    return leaf;
}