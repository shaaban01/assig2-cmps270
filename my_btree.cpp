#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct treeNode
{
    T data;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
};

// ----------------------------------------------------------------

template <typename T>
class btree
{
public:
    // Constructor
    btree();
    // Destructor
    ~btree();

    // Inserts a node into the tree
    // require:
    //  - The value must not be NULL
    //  - The value must be of the same type

    // effect:
    //  - Inserts the node into the tree with the given value
    void addNode(T key);

    // Deletes a node from the tree
    // require:
    //  - The value must not be NULL
    //  - The value must be of the same type
    // effect:
    //  - Deletes the node from the tree with the given value if it exists
    //  - output an error message if the value is not found or if the value is not in a leaf node
    void deleteNode(T key);

    // require: nothing
    // effect: will return the size of the tree
    int treeSize();

    // require: nothing
    // effect:
    //  - return the size of the subtree
    //  - return 0 if the value is not found
    int subtreeSize(T key);

    // require: nothing
    // effect: print the tree in postOrder traversal
    void postOrderPrint();

    // require: nothing
    // effect: print the tree in postOrder traversal
    void preOrderPrint();

    // require: nothing
    // effect: print the tree in postOrder traversal
    void inOrderPrint();

private:
    // helper functions

    void destroy_tree(treeNode<T> *leaf);
    treeNode<T> *findNode(treeNode<T> *node, T val);
    int count(treeNode<T> *node);
    void postOrderPrint(treeNode<T> *node);
    void preOrderPrint(treeNode<T> *node);
    void inOrderPrint(treeNode<T> *node);

    treeNode<T> *root; // stores the root of the tree
    treeNode<T> *last; // stores the last added node
    int size;          // stores the size of the tree
};

// ----------------------------------------------------------------
// ----------------------------------------------------------------

template <typename T>
btree<T>::btree()
{
    this->root = NULL;
    size = 0;
}

template <typename T>
btree<T>::~btree()
{
    destroy_tree(root);
}

template <typename T>
void btree<T>::destroy_tree(treeNode<T> *leaf)
{
    if (leaf != NULL)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

// ----------------------------------------------------------------

template <typename T>
void btree<T>::addNode(T key)
{
    this->size++;
    treeNode<T> *node = new treeNode<T>;
    node->data = key;
    node->left = NULL;
    node->right = NULL;

    // insert root node if empty
    if (this->root == NULL)
    {
        this->root = node;
        this->last = node;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        return;
    }

    // We will be finding the node to insert below.

    // Start with the current last node and move up as long as the
    // parent exists and the current node is its right child.
    treeNode<T> *cur = this->last;
    while (cur->parent != NULL && cur == cur->parent->right)
    {
        cur = cur->parent;
    }

    if (cur->parent != NULL)
    {
        if (cur->parent->right != NULL)
        {
            // The parent has a right child. Attach the new node to
            // the leftmost node of the parent's right subtree.
            cur = cur->parent->right;
            while (cur->left != NULL)
            {
                cur = cur->left;
            }
        }
        else
        {
            // The parent has no right child. This can only happen when
            // the last node is a right child. The new node can become
            // the right child.
            cur = cur->parent;
        }
    }
    else
    {
        // We have reached the root. The new node will be at a new level,
        // the left child of the current leftmost node.
        while (cur->left != NULL)
        {
            cur = cur->left;
        }
    }

    // This is the node below which we will insert. It has either no
    // children or only a left child.
    assert(cur->right == NULL);

    // Insert the new node, which becomes the new last node.
    last = node;
    if (cur->left != NULL)
        cur->right = node;
    else
        cur->left = node;
    node->parent = cur;
    node->left = NULL;
    node->right = NULL;
}

// ----------------------------------------------------------------

template <typename T>
int btree<T>::treeSize()
{
    return this->size;
}

// ----------------------------------------------------------------

template <typename T>
int btree<T>::subtreeSize(T key)
{
    if (findNode(root, key) == NULL)
        return 0;
    return count((findNode(root, key)));
}

template <typename T>
int btree<T>::count(treeNode<T> *node)
{
    if ((node->left == NULL) && (node->right == NULL))
        return 1;
    if ((node->right == NULL) || (node->left == NULL))
        return 2;
    return (1 + count(node->left) + count(node->right));
}

template <typename T>
treeNode<T> *btree<T>::findNode(treeNode<T> *node, T val)
{
    if (node == NULL)
        return NULL;
    if (node->data == val)
        return node;
    treeNode<T> *node1 = findNode(node->left, val);
    if (node1 != NULL)
        return node1;
    treeNode<T> *node2 = findNode(node->right, val);
    return node2;
}

// ----------------------------------------------------------------

template <typename T>
void btree<T>::deleteNode(T key)
{

    treeNode<T> *node = findNode(root, key);
    if ((node->left == NULL) && (node->right == NULL))
    {
        size--;
        treeNode<T> *parentNode = node->parent;
        if (parentNode->left->data == key)
            parentNode->left = NULL;
        else
            parentNode->right = NULL;
    }
    else
        cout << "CANNOT DELETE NODE" << endl;
}

// ----------------------------------------------------------------

template <typename T>
void btree<T>::postOrderPrint()
{
    postOrderPrint(root);
}

template <typename T>
void btree<T>::preOrderPrint()
{
    preOrderPrint(root);
}

template <typename T>
void btree<T>::inOrderPrint()
{
    inOrderPrint(root);
}

template <typename T>
void btree<T>::postOrderPrint(treeNode<T> *node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    postOrderPrint(node->left);

    // then recur on right subtree
    postOrderPrint(node->right);

    // now deal with the node
    cout << node->data << " ";
}

template <typename T>
void btree<T>::preOrderPrint(treeNode<T> *node)
{
    if (node == NULL)
        return;

    /* first print data of node */
    cout << node->data << " ";

    /* then recur on left subtree */
    preOrderPrint(node->left);

    /* now recur on right subtree */
    preOrderPrint(node->right);
}

template <typename T>
void btree<T>::inOrderPrint(treeNode<T> *node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    inOrderPrint(node->left);

    /* then print the data of node */
    cout << (node->data) << " ";

    /* now recur on right child */
    inOrderPrint(node->right);
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

// test driver
int main()
{
    btree<int> tree1; // creating empty int tree

    // adding the nodes
    tree1.addNode(1);
    tree1.addNode(2);
    tree1.addNode(3);
    tree1.addNode(4);
    tree1.addNode(5);
    tree1.addNode(6);
    tree1.addNode(7);
    tree1.addNode(8);
    cout << "The size of the tree is: " << tree1.treeSize() << endl;
    tree1.inOrderPrint();
    cout << endl;
    tree1.preOrderPrint();
    cout << endl;
    tree1.postOrderPrint();
    cout << endl;
    tree1.deleteNode(1); // should give an error
    tree1.deleteNode(8); // delete the node with value 8
    cout << "The size of the tree after deleting 8: " << tree1.treeSize() << endl;
    cout << "The size of the subtree 3 is: " << tree1.subtreeSize(3) << endl; // must return 3
    cout << endl;
    cout << endl;
    cout << endl;

    // check the same for char tree
    btree<char> tree2; // creating empty char tree

    // adding the nodes
    tree2.addNode('a');
    tree2.addNode('b');
    tree2.addNode('c');
    tree2.addNode('d');
    tree2.addNode('e');
    tree2.addNode('f');
    tree2.addNode('g');
    tree2.addNode('h');

    cout << "The size of the tree is: " << tree2.treeSize() << endl;
    tree2.inOrderPrint();
    cout << endl;
    tree2.preOrderPrint();
    cout << endl;
    tree2.postOrderPrint();
    cout << endl;
    tree2.deleteNode('d'); // should give an error
    tree2.deleteNode('h'); // delete the node with value h
    cout << "The size of the tree after deleting 8: " << tree2.treeSize() << endl;
    cout << "The size of the subtree c is: " << tree2.subtreeSize('c') << endl; // must return 3
    cout << endl;
    cout << endl;
    cout << endl;
}
