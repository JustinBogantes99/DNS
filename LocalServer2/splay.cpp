// The code is adopted from http://goo.gl/SDH9hH
#include<stdio.h>
#include<stdlib.h>
#include <QDebug>
#include <QList>
#include <QStringList>
// An AVL tree node
struct node
{

    QString dominio;
    QString ip;
    struct node *left, *right;
};
struct node* newNode(QString pDominio,QString pIp);
struct node *rightRotate(struct node *x);
struct node *leftRotate(struct node *x);
struct node *splay(struct node *root, QString pDominio);
struct node *search(struct node *root,QString pDominio);
struct node *insert(struct node *root, QString pDominio, QString pIp);
struct node* delete_key(struct node *root, QString pDominio);
void imprimirArbol(struct node *root,int altura);
struct node*  getToPythonFormat(QString tree);
QStringList splitComas(QString string);
QString passToPythonFormat(struct node *root);


void imprimirArbol(struct node *root,int altura){
    QString espacios="";
    for(int n=0;n<altura;n++){
        espacios+=" ";
    }
    qDebug()<<espacios<<root->dominio<<root->ip;
    if(root->left!=0){

        imprimirArbol((root->left),altura+1);
    }
    if(root->right!=0){
         imprimirArbol((root->right),altura+1);
    }
}
struct node* newNode(QString pDominio,QString pIp)
{
    struct node* node = new struct node;
    node->dominio= pDominio;
    node->ip=pIp;
    node->left  = node->right  = NULL;
    return (node);
}
struct node *rightRotate(struct node *x)
{
    struct node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
struct node *splay(struct node *root, QString pDominio)
{
    if (root == NULL || root->dominio.length()==0) return root;
    if (root->dominio.compare(pDominio)>0)
    {
        if (root->left == NULL) return root;

        if (root->left->dominio.length()>pDominio.length())
        {
            root->left->left = splay(root->left->left, pDominio);
            root = rightRotate(root);
        }
        else if (root->left->dominio.length()<pDominio.length())
        {
            root->left->right = splay(root->left->right, pDominio);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL)? root: rightRotate(root);
    }
    else
    {
        if (root->right == NULL) return root;


        if (root->right->dominio.length()>pDominio.length())
        {
            root->right->left = splay(root->right->left, pDominio);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->dominio.length()<pDominio.length())
        {
            root->right->right = splay(root->right->right, pDominio);
            root = leftRotate(root);
        }

        return (root->right == NULL)? root: leftRotate(root);
    }
}

struct node *search(struct node *root,QString pDominio)
{
    return splay(root, pDominio);
}


struct node *insert(struct node *root, QString pDominio, QString pIp)
{
    // Simple Case: If tree is empty
    if (root == NULL) return newNode(pDominio,pIp);
    // Bring the closest leaf node to root
    root = splay(root, pDominio);
    // If key is already present, then return
    if (root->dominio.length()==pDominio.length()) return root;
    // Otherwise allocate memory for new node
    struct node *newnode  = newNode(pDominio,pIp);
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->dominio.length()> pDominio.length())
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
    return newnode; // newnode becomes new root
}
// The delete function for Splay tree. Note that this function
// returns the new root of Splay Tree after removing the key
struct node* delete_key(struct node *root, QString pDominio)
{
    struct node *temp;
    if (!root)
        return NULL;

    // Splay the given key
    root = splay(root,pDominio);

    // If key is not present, then
    // return root
    if (pDominio.compare(root->dominio) != 0)
        return root;

    // If key is present
    // If left child of root does not exist
    // make root->right as root
    if (!root->left)
    {
        temp = root;
        root = root->right;
    }

    // Else if left child exits
    else
    {
        temp = root;

        /*Note: Since key == root->key,
        so after Splay(key, root->lchild),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        // New root
        root = splay(root->left, pDominio);

        // Make right child of previous root  as
        // new root's right child
        root->right = temp->right;
    }

    // free the previous root node, that is,
    // the node containing the key
    free(temp);

    // return root of the new Splay Tree
    return root;

}
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
QStringList splitComas(QString string){
    QStringList resultado;

   // qDebug()<<string;
    int parentesis=0;
    int ultimaComa=0;
    int cantComas=0;
    for(int n =0; n<string.length();n++){
        if(string.at(n).toLatin1()=='['){
            parentesis+=1;
        }
        else if(string.at(n).toLatin1()==']'){
            parentesis-=1;
        }
        if(cantComas==2 && parentesis==0 ){
            resultado.push_back(string.mid(ultimaComa,n+1-ultimaComa));
        }
        if((string.at(n).toLatin1()==',' )&& parentesis==0  ){
            resultado.push_back(string.mid(ultimaComa,n-ultimaComa));
            ultimaComa=n+1;
            cantComas+=1;
        }
    }
    return resultado;
}

struct node*  getToPythonFormat(QString tree){
    if(tree.compare("[]")==0){
        return NULL;
    }

    QString resultado=tree.mid(1,tree.length()-2);
    QStringList valores=splitComas(resultado);
    QStringList parametros=QString(valores.at(0)).split(";");;
    struct node*nuevoNodo=newNode(parametros.at(0),parametros.at(1));
    nuevoNodo->left=getToPythonFormat(valores.at(1));
    nuevoNodo->right=getToPythonFormat(valores.at(2));

    return nuevoNodo;
}
QString passToPythonFormat(struct node *root){
    if(root==NULL){
        return "[]";
    }
    QString nodoValue=root->dominio +";"+root->ip;
    QString resultado="";
    resultado="["+nodoValue +","+ passToPythonFormat(root->left) +","+passToPythonFormat(root->right) +"]";
    return resultado;
}
