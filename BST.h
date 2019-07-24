/* BST.h */

                              /* note: destructor, operator== not defined, implemented */

#include <iostream>

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SERACH_TREE

template <typename DataType>
class BST
{
public:
    /*** Function Memebers ***/
    BST();
    bool empty() const;
    void inorder(std::ostream &out) const; // Inorder traversal of BST. Note: inorder uses private auxiliary function inorderAux().
    void graph(std::ostream &out) const; // Graphic output of BST. Note: graph( uses private auxiliary function graphAux( .
    // recursively search BST
    // bool search(const DataType &item) const;

    // iteratively search BST
    bool search(const DataType &item) const;

    void insert(const DataType &item); // insert

    void remove(const DataType &item); //Note: remove uses auxiliary function search2( to locate the node

private:
    class BinNode
    {
    public:
        DataType data;
        BinNode *left;
        BinNode *right;

        //Default Constructor
        BinNode() : left(0), right(0) {}

        //Explicit Constructor
        BinNode(DataType item)
            : data(item), left(0), right(0) {}

    }; //end of BinNode declaration

    //typedef BinNode *BinNodePointer;
    
    /*** Data Members ***/
    BinNode * myRoot;

    /*** Private Function Members ***/
    void inorderAUX(std::ostream &out, 
                    BST<DataType>::BinNode *subtreePtr) const;
    
    void graphAUX(std::ostream &out, int indent, 
                    BST<DataType>::BinNode *subtreeRoot) const;

    
    void search2(const DataType &item, bool &found, 
                BinNode *&locptr, BinNode *&parent) const;
   
    // recursive search helper function
    // bool searchAUX(BST<DataType>::BinNode *subtreeRoot,
                    //const DataType &item) const;

}; //end of class template declaration

//--- Definition of constructor
template <typename DataType>
inline BST<DataType>::BST()
: myRoot(0)
{}

//--- Definition of empty()
template <typename DataType>
inline bool BST<DataType>::empty() const
{ return myRoot == 0; }


//--- Definition of inorder()
template <typename DataType>
inline void BST<DataType>::inorder(std::ostream & out) const
{
    inorderAUX(out, myRoot);
}

//--- Definition of inorderAUX()
template <typename DataType>
void BST<DataType>::inorderAUX(std::ostream &out,
                    BST<DataType>::BinNode *subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        inorderAUX(out, subtreeRoot->left);   // L operation
        out << subtreeRoot->data << " ";      // V operation
        inorderAUX(out, subtreeRoot->right);  // R operation
    }
}

//--- Definition of graph()
template <typename DataType>
inline void BST<DataType>::graph(std::ostream &out) const
{ graphAUX(out, 0, myRoot); }

//---Definition of graphAUX()
#include<iomanip>
template<typename DataType>
void BST<DataType>::graphAUX(std::ostream &out, int indent,
                            BST<DataType>::BinNode *subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        graphAUX(out, indent + 8, subtreeRoot->right);
        out << std::setw(indent) << " " << subtreeRoot->data << std::endl;

    }
}

//--- Definition of search() (iterative method)
template <typename DataType>
bool BST<DataType>::search(const DataType &item) const
{
    BST<DataType>::BinNode *locptr = myRoot;
    bool found = false;
    while (!found && locptr != 0)
    {
        if(item == locptr->data)     // descend left
        { locptr = locptr->left; }
        else if(locptr->data < item) // descend right
        { locptr = locptr->right; }
        else                         // item found
        { found = true; }
    }
    return found;
}


//--- Definition of insert()
template <typename DataType>
void BST<DataType>::insert(const DataType & item)
{
    BST<DataType>::BinNode *
        locptr = myRoot,    // search pointer
        parent = 0;         // pointer to parent of current node
    bool found = false;     // indicates if item already in BST

    while (!found && locptr != 0)
    {
        parent = locptr;
        if (item < locptr->data)  // descend left
            locptr = locptr->left;
        else if (locptr->data < item)
            locptr = locptr->right;
        else
            found = true;   
    }
    if (!found)
    {                                // construct node containing item
        locptr = new BST<DataType>::BinNode(item);
        if (parent == 0)             // empty tree
            myRoot = locptr;
        else if(item < parent->data) // insert to left of parent
            parent->left = locptr;
        else                         // insert to right of parent
            parent->right = locptr;
    }
    else
        std::cout << "Item already in the tree\n";
}


//--- Definition of remove()
template <typename DataType>
void BST<DataType>::remove(const DataType &item)
{
    bool found;                         // signals if item is found
    BST<DataType>::BinNode *
        x,                              // points to node to be deleted
        parent;                         // "  " parent of x and xSucc
    search2(item, found, x, parent);

    if(!found)
    {
        std::cout << "Item not in the BST\n";
        return;
    }
    //else
    if(x->left != 0 && x->right != 0)
    {                              // node has 2 children
        // Find x's inorder successor and its parent
        BST<DataType>::BinNode * xSucc = x->right;
        parent = x;
        while (xSucc->left != 0)   // descend left
        {
            parent = xSucc;
            xSucc = xSucc->left;
        }
        
        // Move contencts of xSucc to x and change x
        // to point to successor, which will be removed.
        x->data = xSucc->data;
        x = xSucc;
    } //end if node has 2 children

    // Now proceed with case where node has 0 or 1 child
    BST<DataType>::BinNode subtree = x->left; // pointer to a subtree of x
    if(subtree == 0)
        subtree = x->right;
    if(parent == 0)                           // root being removed
        myRoot = subtree;
    else if (parent->left == x)               // left child of parent
        parent->left = subtree;
    else                                      // right child of parent
        parent->right = subtree;
    delete x;
}

//--- Definition of search2()
template <class DataType>
void BST<DataType>::search2(const DataType &item, bool &found,
                            BST<DataType>::BinNode *&locptr,
                            BST<DataType>::BinNode *&parent) const
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)          // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->data < item)     // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else                              // item found
            found = true;  
    }
}


/* //--- Definition of search() (recursive method)
template <typename DataType>
inline bool BST<DataType>::search(const DataType &item) const
{ return searchAUX(myRoot, item); }

//--- Definition of searchAUX()
template <typename DataType>
bool BST<DataType>::searchAUX(BST<DataType>::BinNode *subtreeRoot,
                            const DataType &item) const
{
    if (subtreeRoot == 0) // empty subtree
    {
        return false;
    // else there is a nonempty subtree
    if (item < subtreeRoot->data) // search left subtree
    { return searchAUX(subtreeRoot->left, item); }
    else if(subtreeRoot->data < item) // search right subtree
    { return searchAUX(subtreeRoot->right, item); }
    else  //item is found
    {return true;}
    }
} */

#endif
