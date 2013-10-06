/**
 * 平衡二叉树
 * avl tree
 */
#include <iostream>
#include <stdlib.h>

using namespace std;

struct avl_node
{
    avl_node():data(0), height(0), freq(1), left(NULL), right(NULL) {}
    int data;
    int height;
    int freq;       // 表示相同的此结点有几个了
    avl_node* left;
    avl_node* right;
};

class avl_tree
{
public:
    avl_tree():root(NULL){}
    void insertData(int data)  //  插入
    {
        insertNode(root, data);
    }
    void deleteData(int data)  //  删除
    {
        deleteNode(root, data);
    }
    void traverse()            //  遍历
    {
        cout<<"avl "<<root->height<<": ";
        inOrderTraverse(root);
        cout<<endl;
    }
    avl_node* find(int data)   //  查找
    {
        return findNode(root, data);
    }
private:
    avl_node* root;
    void deleteNode(avl_node* &root, int data)
    {
        if(root == NULL)
            return;
        if(root->data > data)
        {
            deleteNode(root->left, data);
            if(2==height(root->left)-height(root->right))
            {
                if(data < root->left->data)
                    root = SingRotateLeft(root);
                else
                    root = DoubleRotateLR (root);
            }
        }
        else if(root->data < data)
        {
            deleteNode(root->right, data);
            if(2==height(root->left)-height(root->right))
            {
                if(data > root->right->data)
                    root = SingRotateRight(root);
                else
                    root = DoubleRotateRL(root);
            }
        }
        else // 若相等，则删除此结点
        {
            if(root->left && root->right)
            {
                avl_node* tmp = root->right;//tmp指向结点右儿子
                while(tmp->left)//找到右子树中的最小结点
                    tmp = tmp->left;
                root->data = tmp->data;
                root->freq = tmp->freq;
                deleteNode(root->right, tmp->data);
                if(2==height(root->left)-height(root->right))
                {// 当结点删除的时候，root的右子树只会降低，所以，左-右==2，则旋转
                    if(root->left->right!=NULL&& (height(root->left->right)>height(root->left->left) ))
                        // 如果root->left的右子树更高，则LR旋转，否则左旋
                        root = DoubleRotateLR(root);
                    else
                        root = SingRotateLeft(root);
                }
            }
            else
            {
                avl_node* tmp = root;
                if(root->left)
                    root = root->left;
                else if(root->right)
                    root = root->right;
                else
                    root = NULL;
            }
        }

        if(root)
            root->height = Max(height(root->left), height(root->right)) + 1;
    }
    void insertNode(avl_node* &root, int data)
    {
        if(root == NULL)
        {
            root = new avl_node;
            root->data = data;
            return;
        }
        if(root->data > data)
        {
            insertNode(root->left, data);
            if(2==height(root->left)-height(root->right))
            {
                if(data < root->left->data)
                    root = SingRotateLeft(root);
                else
                    root = DoubleRotateLR (root);
            }
        }
        else if(root->data < data)
        {
            insertNode(root->right, data);
            if(2==height(root->left)-height(root->right))
            {
                if(data > root->right->data)
                    root = SingRotateRight(root);
                else
                    root = DoubleRotateRL(root);
            }
        }
        else
            root->freq++;

        root->height = Max(height(root->left), height(root->right)) + 1;
    }

    avl_node* SingRotateLeft(avl_node* &k2)  //左左情况下的旋转
    {// 左左情况下，向右旋转
        avl_node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        k2->height = Max(height(k2->left), height(k2->right)) + 1;
        k1->height = Max(height(k1->left), height(k1->right)) + 1;
        return k1;
    }
    avl_node* SingRotateRight(avl_node* &k2) //右右情况下的旋转
    {// 右右情况下，向左旋转
        avl_node* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;

        k2->height = Max(height(k2->left), height(k2->right)) + 1;
        k1->height = Max(height(k1->left), height(k1->right)) + 1;
        return k1;
    }
    avl_node* DoubleRotateLR(avl_node* &k3)  //左右情况下的旋转
    {
        k3->left = SingRotateRight(k3->left);
        return SingRotateLeft(k3);
    }
    avl_node* DoubleRotateRL(avl_node* &k3)  //右左情况下的旋转
    {
        k3->right = SingRotateLeft(k3->right);
        return SingRotateRight(k3);
    }

    int Max(int a, int b) {return a>b?a:b;}
    avl_node* findNode(avl_node* root, int data)
    {
        if(!root)
            return NULL;
        if(root->data > data)
            return findNode(root->left, data);
        else if(root->data < data)
            return findNode(root->right, data);
        else
            return root;
    }
    int height(avl_node* root)
    {
        if(!root)
            return 0;
        return root->height;
        //return Max(height(root->left), height(root->right)) + 1;
    }

    void inOrderTraverse(avl_node* root)
    {
        if(!root)
            return;
        inOrderTraverse(root->left);
        cout<<root->data<<" ";
        inOrderTraverse(root->right);
    }

};

int main()
{
    avl_tree tree;
    for(int i=0; i<10; ++i)
    {
        tree.insertData(rand()%10);
        tree.traverse();
    }
    for(int i=0; i<10; ++i)
    {
        tree.deleteData(rand()%10);
        tree.traverse();
    }
    return 0;
}
