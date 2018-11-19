#include <QCoreApplication>
#include "splay.cpp"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    struct node *root = newNode(100);
    root->left = newNode(50);
    root->right = newNode(200);
    root->left->left = newNode(40);
    root->left->left->left = newNode(30);
    root->left->left->left->left = newNode(20);

    root = search(root, 20);
    printf("Preorder traversal of the modified Splay tree is \n");
    preOrder(root);
    printf("/n");
    root = insert(root, 25);
    preOrder(root);
    return a.exec();
}
