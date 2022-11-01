#include <iostream>

template <typename T>
struct treeNode
{
    T *data;
    struct treeNode *left;
    struct treeNode *right;
};

template <typename T>
class btree
{
public:
    btree();
    ~btree();

    void addNode(int key);
    void destroy_tree();

private:
    void addNode(int key, treeNode<T> *leaf);
    void destroy_tree(treeNode<T> *leaf);

    treeNode<T> *root;
};
template <typename T>
btree<T>::btree()
{
    this.root = NULL;
}

template <typename T>
btree<T>::~btree()
{
    destroy_tree();
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

template <typename T>
void btree<T>::addNode(int key, treeNode<T> *leaf)
{
    if (key < leaf->key_value)
    {
        if (leaf->left != NULL)
            addNode(key, leaf->left);
        else
        {
            leaf->left = new treeNode<T>;
            leaf->left->key_value = key;
            leaf->left->left = NULL;  // Sets the left child of the child treeNode to null
            leaf->left->right = NULL; // Sets the right child of the child treeNode to null
        }
    }
    else if (key >= leaf->key_value)
    {
        if (leaf->right != NULL)
            addNode(key, leaf->right);
        else
        {
            leaf->right = new treeNode<T>;
            leaf->right->key_value = key;
            leaf->right->left = NULL;  // Sets the left child of the child treeNode to null
            leaf->right->right = NULL; // Sets the right child of the child treeNode to null
        }
    }
}

int main()
{
}
