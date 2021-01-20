#ifndef DEF_TREE
#define DEF_TREE

#include <vector>

class Tree;

class Tree{

    public:
        Tree (char); // construit une feuille
        Tree (Tree*, Tree*, char);
        ~Tree ();

    public:
        Tree* leftChild ();
        Tree* rightChild ();
        const char tagValue ();
        const bool isLeaf ();

    private:
        const char tag;
        const bool leaf; // vrai ssi l'arbre est une feuille
        std::vector <Tree*> children;
};

#endif