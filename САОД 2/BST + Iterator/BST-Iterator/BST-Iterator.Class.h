//���������� ���� ���-22
#pragma once

#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include <stack>
#include "TreeNode.Class.h"

using namespace std;

// ��������� ����� ���� ������
template <typename T>
class Node {
public:
    T value;         // �������� ����
    Node<T>* left;        // ����� �������
    Node<T>* right;       // ������ �������

    // ����������� ����
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

// ��������� ����� ��� ��������� ������ ������
template <typename T>
class BST {
private:
    BinSearchNode<T>* root; // ������ ������

    //Node<T>* root; // ������ ������

    //// O(log2n) � ��� ����������������� ������  
    //// ����� ������� �������� � ��������� ������ ������                                                             
    //Node<T>* insert(Node<T>* node, T value) {
    //    if (!node) {
    //        return new Node<T>(value);
    //    }
    //    if (value < node->value) {
    //        node->left = insert(node->left, value);
    //    }
    //    else if (value > node->value) {
    //        node->right = insert(node->right, value);
    //    }
    //    return node;
    //}

    //// ����� ��� ������ ������ � ������� �����������
    //void traverseInOrder(Node<T>* node) {
    //    if (node) {
    //        traverseInOrder(node->left);
    //        cout << node->value << " ";
    //        traverseInOrder(node->right);
    //    }
    //}

    //// ����� ��� �������� ������� ���� � ������
    //bool search(Node<T>* node, T value) {
    //    if (!node) {
    //        return false;
    //    }
    //    if (value == node->value) {
    //        return true;
    //    }
    //    else if (value < node->value) {
    //        return search(node->left, value);
    //    }
    //    else {
    //        return search(node->right, value);
    //    }
    //}

    //// ����� ��� ������� ���� � ������
    //Node<T>* remove(Node<T>* node, T value) {
    //    if (!node) {
    //        return nullptr;
    //    }

    //    if (value < node->value) {
    //        node->left = remove(node->left, value);
    //    }
    //    else if (value > node->value) {
    //        node->right = remove(node->right, value);
    //    }
    //    else {
    //        if (!node->left) {
    //            Node<T>* rightChild = node->right;
    //            delete node;
    //            return rightChild;
    //        }
    //        else if (!node->right) {
    //            Node<T>* leftChild = node->left;
    //            delete node;
    //            return leftChild;
    //        }
    //        else {
    //            Node<T>* successorParent = node;
    //            Node<T>* successor = node->right;
    //            while (successor->left) {
    //                successorParent = successor;
    //                successor = successor->left;
    //            }
    //            node->value = successor->value;
    //            if (successorParent->left == successor) {
    //                successorParent->left = successor->right;
    //            }
    //            else {
    //                successorParent->right = successor->right;
    //            }
    //            delete successor;
    //        }
    //    }
    //    return node;
    //}
public:
    // ����������� ��� ����������
    BST() : root(nullptr) {}

    // ����� ������� �������� � ������
    void insert(T value) {
        if (!root) {
            root = new BinSearchNode<T>(value);
        }
        else {
            root->popbsn(value);
        }
    }

    // ����� ��� ������ �������� ������ � ������� ����������� (in order)
    void traverseInOrder() {
        if (root) {
            root->traverseInOrder();
        }
        cout << endl;
    }

    // ����� ������ (�������� ���� �� ��������) �������� � ������
    bool search(T value) {
        if (root) {
            return root->searchbool(value);
        }
        return false;
    }

    // ����� �������� �������� ������
    void remove(T value) {
        if (root) {
            root->del(value);
        }
    }

    // ����� ��������� ����� ��� ������(LNR) ��� ��������� ������ ������
    class Iterator {
    private:
        stack<BinSearchNode<T>*> nodeStack; // ���� ��� �������� ������ �� ������ ������

        // ����� ������ ������ 
        void pushLeft(BinSearchNode<T>* node) {
            while (node) {
                nodeStack.push(node);
                node = static_cast<BinSearchNode<T>*>(node->left);
            }
        }

    public:
        // �����������
        Iterator(BinSearchNode<T>* root) {
            pushLeft(root);
        }

        // ����� �������� ���� �� ��������� �������
        bool hasNext() {
            return !nodeStack.empty();
        }

        // ����� ������ BST ������ �� �������� LNR
        T next() {
            BinSearchNode<T>* current = nodeStack.top();
            nodeStack.pop();
            T value = current->value;
            if (current->right) {
                pushLeft(static_cast<BinSearchNode<T>*>(current->right));
            }
            return value;
        }
    };

    // ����� ������ ������������ ������ ���������
    Iterator getIterator() {
        return Iterator(root);
    }
};