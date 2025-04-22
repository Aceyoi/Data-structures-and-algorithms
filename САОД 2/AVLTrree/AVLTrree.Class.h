?//���������� ���� ���-22

#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iterator>

using namespace std;

template <typename T>
class AVLTree {
private:
    struct Node {
        T key; // ���� ����
        int height; // ������ ����
        Node* left; // ����� �������
        Node* right; // ������ �������

        Node(T k) : key(k), height(1), left(nullptr), right(nullptr) {} // ����������� ����
    };

    Node* root; // ������ ������

    int height(Node* N) {
        return N ? N->height : 0; // ���������� ������ ���� ��� 0, ���� ���� ������
    }

    int getBalance(Node* N) {
        return N ? height(N->left) - height(N->right) : 0; // ���������� ������ ���� ��� 0, ���� ���� ������
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left; // ����� ������� ���� y
        Node* T2 = x->right; // ������ ������� ���� x

        // ��������� ������ �������
        x->right = y;
        y->left = T2;

        // ��������� ������
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // ���������� ����� ������
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right; // ������ ������� ���� x
        Node* T2 = y->left; // ����� ������� ���� y

        // ��������� ����� �������
        y->left = x;
        x->right = T2;

        // ��������� ������
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // ���������� ����� ������
        return y;
    }

    Node* insert(Node* node, T key) {
        // 1. ��������� ����������� ������� � BST
        if (!node) return new Node(key); // ���� ���� ������, ������� ����� ����

        if (key < node->key)
            node->left = insert(node->left, key); // ��������� � ����� ���������
        else if (key > node->key)
            node->right = insert(node->right, key); // ��������� � ������ ���������
        else
            return node; // ������������� ����� �� �����������

        // 2. ��������� ������ �������� ����
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. �������� ������ ������� �������� ����, ����� ���������, ���� �� �� ������������������
        int balance = getBalance(node);

        // ���� ���� ���� ������������������, �� ���� 4 ������

        // �����-����� ������
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // ������-������ ������
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // �����-������ ������
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // ������-����� ������
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // ���������� ���������� ��������� �� ����
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node; // �������� � �������� ����
        while (current->left != nullptr)
            current = current->left; // ���� ����� �� �����
        return current; // ���������� ���� � ����������� ���������
    }

    Node* deleteNode(Node* root, T key) {
        // 1. ��������� ����������� �������� � BST
        if (!root) return root; // ���� ���� ������, ���������� ���

        if (key < root->key)
            root->left = deleteNode(root->left, key); // ������� �� ������ ���������
        else if (key > root->key)
            root->right = deleteNode(root->right, key); // ������� �� ������� ���������
        else {
            // ���� � ����� �������� ��� ��� ��������
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right; // �������� �������

                // ������ ��� ��������
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else // ������ � ����� ��������
                    *root = *temp; // �������� ���������� ��������� �������

                delete temp; // ������� ������ ����
            }
            else {
                // ���� � ����� ���������: �������� ��������� (����������� � ������ ���������)
                Node* temp = minValueNode(root->right);

                // �������� ������ ��������� � ������� ����
                root->key = temp->key;

                // ������� ���������
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // ���� ������ ����� ������ ���� ����, ���������� ���
        if (!root) return root;

        // 2. ��������� ������ �������� ����
        root->height = 1 + max(height(root->left), height(root->right));

        // 3. �������� ������ ������� �������� ���� (����� ���������, ���� �� �� ������������������)
        int balance = getBalance(root);

        // ���� ���� ���� ������������������, �� ���� 4 ������

        // �����-����� ������
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // �����-������ ������
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // ������-������ ������
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // ������-����� ������
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* updateNode(Node* node, T oldKey, T newKey) {
        if (!node) return node; // ���� ���� ������, ���������� ���

        if (oldKey < node->key)
            node->left = updateNode(node->left, oldKey, newKey); // ��������� � ����� ���������
        else if (oldKey > node->key)
            node->right = updateNode(node->right, oldKey, newKey); // ��������� � ������ ���������
        else {
            node->key = newKey; // ��������� ����
            return node;
        }

        // ��������� ������ �������� ����
        node->height = 1 + max(height(node->left), height(node->right));

        // �������� ������ ������� �������� ����, ����� ���������, ���� �� �� ������������������
        int balance = getBalance(node);

        // ���� ���� ���� ������������������, �� ���� 4 ������

        // �����-����� ������
        if (balance > 1 && newKey < node->left->key)
            return rightRotate(node);

        // ������-������ ������
        if (balance < -1 && newKey > node->right->key)
            return leftRotate(node);

        // �����-������ ������
        if (balance > 1 && newKey > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // ������-����� ������
        if (balance < -1 && newKey < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // ���������� ���������� ��������� �� ����
        return node;
    }

    Node* searchNode(Node* node, T key) {
        if (!node || node->key == key)
            return node; // ���� ���� ������ ��� ���� ������, ���������� ����

        if (key < node->key)
            return searchNode(node->left, key); // ���� � ����� ���������

        return searchNode(node->right, key); // ���� � ������ ���������
    }

    void preOrder(Node* node) {
        if (!node) return; // ���� ���� ������, ������������
        cout << node->key << " "; // ������� ���� ����
        preOrder(node->left); // ���������� ������� ����� ���������
        preOrder(node->right); // ���������� ������� ������ ���������
    }

    // ������� ��� ����� ���� ������ ������ � ������
    void collectKeys(Node* node, vector<T>& keys) {
        if (!node) return; // ���� ���� ������, ������������
        collectKeys(node->left, keys); // ���������� �������� ����� �� ������ ���������
        keys.push_back(node->key); // ��������� ���� �������� ���� � ������
        collectKeys(node->right, keys); // ���������� �������� ����� �� ������� ���������
    }

public:
    AVLTree() : root(nullptr) {} // ����������� ������

    void insert(T key) {
        root = insert(root, key); // ��������� ���� � ������
    }

    void remove(T key) {
        root = deleteNode(root, key); // ������� ���� �� ������
    }

    void update(T oldKey, T newKey) {
        root = updateNode(root, oldKey, newKey); // ��������� ���� � ������
    }

    Node* search(T key) {
        return searchNode(root, key); // ���� ���� � ������
    }

    void preOrder() {
        preOrder(root); // ������� ������ � ������� ����������� ������
    }

    // ������� ��� ����� ���� ������ ������ � ������
    vector<T> getKeys() {
        vector<T> keys;
        collectKeys(root, keys);
        return keys;
    }


};
/*

AVL ��������
����� ������� - �����, ������
������� ������� (������� �������) - ����-������, �����-�����, ����-�����, �����-������

*/