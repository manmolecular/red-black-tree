// Узел дерева
// файл TreeNode.h
#pragma once
#include <cstddef>		// Определение константы NULL

template <class TreeItemType>
class TreeNode 
{
	enum {BLACK = 0, RED = 1};
private:
	TreeNode() : leftChildPtr(NULL), rightChildPtr(NULL), parentPtr(NULL), color(BLACK), isEmpty(1) {};
	TreeNode(const TreeItemType& nodeItem, 
		TreeNode<TreeItemType> * left = NULL, 
		TreeNode<TreeItemType> * right = NULL, 
		TreeNode<TreeItemType> * parent = NULL) : 
		item(nodeItem), 
		isEmpty(1), 
		leftChildPtr(left), 
		rightChildPtr(right),
		parentPtr(parent) 
	{};
	TreeItemType item; 
	TreeNode<TreeItemType> * leftChildPtr, * rightChildPtr, * parentPtr;
	bool color, isEmpty;
	template <class TreeItemType> friend class BinaryTree;
};