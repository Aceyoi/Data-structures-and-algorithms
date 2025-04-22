//���������� ���� ���-22
#pragma once

#include<exception>
#include <iostream>
#include <vector>

using namespace std;

//��������� ����� ����� ������
template<typename T>
class TreeNode {  //�������� ������
public:
    T value;            // �������� �������� ����                                                              
    TreeNode<T>* left;  // ��������� �� ����� �����
    TreeNode<T>* right; // ��������� �� ������ �����

    ///����������� ��� ����������
    TreeNode() {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    //����������� � ����� �����������
    // val - ������ ������
    TreeNode(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    //����������� � �����������
    // val - ������ ������
    // left - ��������� �� ����� �����
    // right - ��������� �� ������ �����
    TreeNode(T val, TreeNode<T>* left, TreeNode<T>* right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }

    // ��������������� ������� ��� ����������� ������ (������������ �����)
    void printTree(int level = 0) const {
        if (right != nullptr) {
            right->printTree(level + 1);  // ����������� ����� ������� ���������
        }
        for (int i = 0; i < level; ++i) {
            cout << "    ";  // ������ ��� ������ ������
        }
        cout << value << endl;  // ����� �������� ����
        if (left != nullptr) {
            left->printTree(level + 1);  // ����������� ����� ������ ���������
        }
    }

    // ��������, ������ �� ������
    bool isEmpty() const {
        if (value == T{} && left == nullptr && right == nullptr)
            return true;
        else 
            return false;
    }

    // �������� ���� �����
    void deleteTree() {
        if (left != nullptr) {
            left->deleteTree();  // ����������� �������� ������ ���������        
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            right->deleteTree();  // ����������� �������� ������� ���������
            delete right;
            right = nullptr;
        }
        if (left == nullptr && right == nullptr) {
            value = 0;
        }
    }

    // ������������ ����� (LNR) // ����� � ���� �������
    void traverseInOrder() {
        if (left != nullptr) {
            left->traverseInOrder();  // ����� �����
        }
        cout << value << " ";  // �����
        if (right != nullptr) {
            right->traverseInOrder();  // ������ �����
        }
    }

    // ������ ����� (NLR) // ����� � ���� �������
    void traversePreOrder() {
        cout << value << " ";  // ����� �������� �������� ����
        if (left != nullptr) {
            left->traversePreOrder();  // ����������� ����� ������ ���������
        }
        if (right != nullptr) {
            right->traversePreOrder();  // ����������� ����� ������� ���������
        }
    }

    // �������� ����� (LRN) // ����� � ���� �������
    void traversePostOrder() {
        if (left != nullptr) {
            left->traversePostOrder();  // ����� �����
        }
        if (right != nullptr) {
            right->traversePostOrder();  // ������ �����
        }
        cout << value << " ";  // �����
    }

    // ������� ���������� ����� � ������  
    int countNodes() {
        if (isEmpty() == true) {
            return 0;
        }
        else {

            int count = 1;  // ������� ������
            if (left != nullptr) {
                count += left->countNodes();  // ������� � ����� �����
            }
            if (right != nullptr) {
                count += right->countNodes();  // ������� � ������ �����
            }
            return count;
        }
    }

    // ����������� ������� ������
    int depth() {
        if (isEmpty() == true) {
            return -1;
        }
        else {

            int leftDepth = left ? left->depth() : 0;
            int rightDepth = right ? right->depth() : 0;
            return 1 + max(leftDepth, rightDepth);
        }
    }

    // ������������� �����������
    TreeNode<T>* easycopy() {
        return this;
    }

    // �������� �����������
    TreeNode<T>* deepcopy() {
        TreeNode<T>* newTreeNode = new TreeNode<T>(value);  // �������� �������� �������� ����        
        if (left != nullptr) {
            newTreeNode->left = left->deepcopy();  // ���������� �������� ����� ���������
        }
        if (right != nullptr) {
            newTreeNode->right = right->deepcopy();  // ���������� �������� ������ ���������
        }
        return newTreeNode;
    }

    // ����� ��� ���������� ���������� ������� ���������� ������ � ������� LNR (In-order �����)
    void TreeArray(vector<T>& arr) {


        if (left != nullptr) {
            left->TreeArray(arr);  // ����������� ����� ������ ���������
        }

        arr.push_back(value);  // ��������� �������� �������� ����

        if (right != nullptr) {
            right->TreeArray(arr);  // ����������� ����� ������� ���������
        }
    }
};    

//��������� ����� ����� ��������� ������
template<typename T>
class BinTreeNode : public TreeNode<T> {  //�������� ������
public:

    //����������� � ����� �����������
    // val - ������ ������
    BinTreeNode(T val){
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    // ������� �������� � ������  
    void popbtn(T val) {
        if (this->left == nullptr) {
            this->left = new BinTreeNode<T>(val);  // ��������� � ����� �����
        }
        else {
        if (this->right == nullptr) {
            this->right = new BinTreeNode<T>(val);  // ��������� � ������ �����
        }
        else {
            static_cast<BinTreeNode<T>*>(this->left)->popbtn(val);
        }}
    }
};

//��������� ����� ����� ������ ������
template<typename T>
class BinSearchNode : public TreeNode<T> {  //�������� ������
public:

    //����������� � ����� �����������
    // val - ������ ������
    BinSearchNode(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    // O(n) � ��� ������������������� ������
    // O(log2n) � ��� ����������������� ������  
    // ������� �������� � ������ ������                                                               
    void popbsn(T val) {
        if (val < this->value) {  // ���� �������� ������ ��������, ���� � ����� �����
            if (this->left == nullptr) {
                this->left = new BinSearchNode<T>(val);  // ��������� � ����� �����, ���� ��� �����
            }
            else {
                static_cast<BinSearchNode<T>*>(this->left)->popbsn(val);  // ����������� ������� � ����� ���������
                /*
                �������� static_cast ������������ �������������� ��������� � ������� ����� � ��������� �� ����������� �����
                */
            }
        }
        else 
            if (val > this->value) {  // ���� �������� ������ ��������, ���� � ������ �����
            if (this->right == nullptr) {
                this->right = new BinSearchNode<T>(val);  // ��������� � ������ �����, ���� ��� �����
            }
            else {
                static_cast<BinSearchNode<T>*>(this->right)->popbsn(val);  // ����������� ������� � ������ ���������
            }
        }
    }

    // O(n) � ��� �� ����������������� ������
    // O(log2n) � ��� ����������������� ������
    T successor(T val) {
        T bigval;  // ���������� ��� �������� ���������
        bool found = false;  // ���� ��� ������������, ��� �� ������ ���� � val
        BinSearchNode<T>* current = this;  // �������� � �������� ����

        // ����������� ����� �������� � �������������� ���������
        while (current != nullptr) {
            if (val < current->value) {
                // ���� �������� ������ ��������, ���������� ������� ������� ��� ���������� ���������
                bigval = current->value;
                current = static_cast<BinSearchNode<T>*>(current->left);
            }
            else if (val > current->value) {
                // ���� �������� ������ ��������, ��� ������
                current = static_cast<BinSearchNode<T>*>(current->right);
            }
            else {
                // ���� � ������� ��������� ������  
                found = true;///                        
                if (current->right != nullptr) {
                    // ���� ���� ������ ���������, ������� ����������� ������� � ��
                    return findMinValue(static_cast<BinSearchNode<T>*>(current->right));

                }
                break;
            }
        }
        if (found == true) {
            return bigval;
        }
        else {
            return val;
        }
    }

    // ��������������� ����� ��� ���������� ������������ �������� � ���������
    T findMinValue(BinSearchNode<T>* node) {
        while (node->left != nullptr) {
            node = static_cast<BinSearchNode<T>*>(node->left);
        }
        return node->value;
    }

    // O(n) � ��� ������������������� ������
    // O(log2n) � ��� ����������������� ������
    // ����� ��� ������ �������� � ������ ������ (������������ ��� ��������)
    T search(T val) {
        // ��������� �������� � ������� �����
        if (val == this->value) {
            return this->value;  // �������� �������
        }
        if (val < this->value && this->left != nullptr) {
            // ���� �������� ������, �� ���� � ����� ���������
            return static_cast<BinSearchNode<T>*>(this->left)->search(val);  // ����� � ����� ���������        }
        }
        if (val > this->value && this->right != nullptr) {
            // ���� �������� ������, �� ���� � ������ ���������
            return static_cast<BinSearchNode<T>*>(this->right)->search(val);  // ����� � ������ ���������        }
        }
    return -1;
    }

    // O(n) � ��� ������������������� ������
    // O(log2n) � ��� ����������������� ������
    // ����� ��� �������� ������ �������� � ������ ������
    bool searchbool(T val) {
        // ��������� �������� � ������� �����
        if (val == this->value) {
            return true;  // �������� �������
        }
        if (val < this->value && this->left != nullptr) {
            // ���� �������� ������, �� ���� � ����� ���������
            return static_cast<BinSearchNode<T>*>(this->left)->searchbool(val);  // ����� � ����� ���������        }
        }
        if (val > this->value && this->right != nullptr) {
            // ���� �������� ������, �� ���� � ������ ���������
            return static_cast<BinSearchNode<T>*>(this->right)->searchbool(val);  // ����� � ������ ���������        }
        }
        return false;
    }

    // O(n) � ��� ������������������� ������
    // O(log2n) � ��� ����������������� ������
    // �������� �������� �� ������ ������
    void del(T val) {
        // ���� �������� ������ �������� ����, ��� �����
        if (val < this->value && this->left != nullptr) {
            // ���������, �������� �� ����� ������� ������� �����
            if (this->left->value == val) {
                TreeNode<T>* target = this->left; // ���� ��� ��������
                // ������������ ������, ���� � ���� ���� �������
                if (target->left == nullptr && target->right == nullptr) {
                    // ���� �� ����� ��������
                    delete target;
                    this->left = nullptr;
                }
                else if (target->left != nullptr && target->right == nullptr) {
                    // ���� ����� ������ ������ �������
                    this->left = target->left;
                    delete target;
                }
                else if (target->left == nullptr && target->right != nullptr) {
                    // ���� ����� ������ ������� �������
                    this->left = target->right;
                    delete target;
                }
                else {
                    // ���� ����� ����� ��������
                    TreeNode<T>* successorParent = target;
                    TreeNode<T>* successor = target->right;
                    while (successor->left != nullptr) {
                        successorParent = successor;
                        successor = successor->left;
                    }
                    target->value = successor->value; // ������ ��������
                    if (successorParent->left == successor) {
                        successorParent->left = successor->right;
                    }
                    else {
                        successorParent->right = successor->right;
                    }
                    delete successor;
                }
            }
            else {
                // ����������� �������� � ����� ���������
                static_cast<BinSearchNode<T>*>(this->left)->del(val);
            }
        }
        // ���� �������� ������ �������� ����, ��� ������
        else if (val > this->value && this->right != nullptr) {
            // ���������, �������� �� ������ ������� ������� �����
            if (this->right->value == val) {
                TreeNode<T>* target = this->right; // ���� ��� ��������
                // ������������ ������, ���� � ���� ���� �������
                if (target->left == nullptr && target->right == nullptr) {
                    // ���� �� ����� ��������
                    delete target;
                    this->right = nullptr;
                }
                else if (target->left != nullptr && target->right == nullptr) {
                    // ���� ����� ������ ������ �������
                    this->right = target->left;
                    delete target;
                }
                else if (target->left == nullptr && target->right != nullptr) {
                    // ���� ����� ������ ������� �������
                    this->right = target->right;
                    delete target;
                }
                else {
                    // ���� ����� ����� ��������
                    TreeNode<T>* successorParent = target;
                    TreeNode<T>* successor = target->right;
                    while (successor->left != nullptr) {
                        successorParent = successor;
                        successor = successor->left;
                    }
                    target->value = successor->value; // ������ ��������
                    if (successorParent->left == successor) {
                        successorParent->left = successor->right;
                    }
                    else {
                        successorParent->right = successor->right;
                    }
                    delete successor;
                }
            }
            else {
                // ����������� �������� � ������ ���������
                static_cast<BinSearchNode<T>*>(this->right)->del(val);
            }
        }
        // ���� �������� ��������� � ������ ������
        else if (val == this->value) {
            // ��������� ��������� ���� ��� ��������, ���� �����������
            cout << "�������� ����� ������ �� �������������� ���� �������." << endl;
        }
        else {
            // �������� �� �������
            cout << "�������� " << val << " �� ������� � ������." << endl;
        }
    }
};