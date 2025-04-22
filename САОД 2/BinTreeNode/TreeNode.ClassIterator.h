//���������� ���� ���-22
#pragma once

#include<exception>
#include <iostream>
#include <vector>
#include "TreeNode.Modul.h"
#include "TreeNode.Class.h"


using namespace std;

//��������� ����� ��������� ��� BST ������
template <typename T>
class BSTIterator {
protected:
    /// ������, ������������, ������ �� �������� ����� ������
    int iterationComplete;
    TreeNode<T>* stack;  // ���� ��� �������� ����� ������
    TreeNode<T>* current;  // ������� ���� ��������

};