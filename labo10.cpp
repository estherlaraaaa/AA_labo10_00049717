//
//  main.cpp
//  Created by Carlos Paredes on 10/30/19.
//  Copyright © 2019 Carlos Paredes. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
    int height;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->height = 1;
    return temp;
}

void preOrder(struct node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct node *insert(struct node *node, int key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int main()
{
    struct node *root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 8);

    std::cout << "INORDER: ";
    inOrder(root);
    std::cout << "PREORDER: ";
    preOrder(root);

    return 0;
}