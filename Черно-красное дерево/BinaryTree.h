#pragma once

#include "TreeNode.h"	// Содержит определения классов TreeNode и TreeltemType
#include <exception>
#include <string>
#include <queue>		// queue

class TreeException : public std::exception
{
public:
	TreeException(const std::string & message = "") : std::exception(message.c_str()) { }
};

template <class TreeItemType>
class BinaryTree
{
public:
	// Конструкторы и деструктор:
	BinaryTree();
	BinaryTree(const TreeItemType& rootltem);
	BinaryTree(const TreeItemType& rootltem, BinaryTree<TreeItemType>& leftTree, BinaryTree<TreeItemType>& rightTree);
	BinaryTree(const BinaryTree<TreeItemType>& tree);
	~BinaryTree();

	// Операции над деревом:
	TreeItemType getRootData() const;
	bool isEmpty() const;
	BinaryTree<TreeItemType> getLeftSubtree() const;
	BinaryTree<TreeItemType> getRightSubtree() const;
	void preorderTraverse(void(*visit)(TreeItemType &anitem));
	void inorderTraverse(void(*visit)(TreeItemType &anitem));
	void postorderTraverse(void(*visit)(TreeItemType &anitem));
	BinaryTree<TreeItemType>& operator=(const BinaryTree<TreeItemType>& rhs);

	unsigned int getDepth() const;
	unsigned int getDepthOfMin() const;
	unsigned int getDepthOfMax() const;
	void printLevels() const;
	void print() const;
	template <class TreeItemType> friend std::ostream& operator<<(std::ostream& out, const BinaryTree<TreeItemType> &tree);
	void attach(const TreeItemType &newItem);
	bool isExist(TreeItemType &anitem) const;
	void deleteItem(TreeItemType &anitem);


protected:
	void setRootData(const TreeItemType& newltem);
	void attachLeft(const TreeItemType& newltem);
	void attachRight(const TreeItemType& newltem);
	void attachLeftSubtree(BinaryTree<TreeItemType>& leftTree);
	void attachRightSubtree(BinaryTree<TreeItemType>& rightTree);
	void detachLeftSubtree(BinaryTree<TreeItemType>& leftTree);
	void detachRightSubtree(BinaryTree<TreeItemType>& rightTree);
	BinaryTree(TreeNode<TreeItemType> *nodePtr);
	void copyTree(TreeNode<TreeItemType> *treePtr, TreeNode<TreeItemType> *& newTreePtr) const;
	void destroyTree(TreeNode<TreeItemType> *& treePtr);
	TreeNode<TreeItemType>* rootPtr() const;
	void setRootPtr(TreeNode<TreeItemType> *newRoot);
	void getChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *& leftChildPtr, TreeNode<TreeItemType> *& rightChildPtr) const;
	void setChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *leftChildPtr, TreeNode<TreeItemType> *rightChildPtr);
	void preorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));
	void inorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));
	void postorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));

	void attach_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr);
	unsigned int getDepth_helper(TreeNode<TreeItemType> *nodePtr) const;
	unsigned int getDepthOfMin_helper(TreeNode<TreeItemType> *nodePtr) const;
	unsigned int getDepthOfMax_helper(TreeNode<TreeItemType> *nodePtr) const;
	void printLevels_helper(unsigned int level, std::queue<TreeNode<TreeItemType>*> &levelHubs) const;
	void print_helper(TreeNode<TreeItemType> *nodePtr, unsigned int level) const;
	bool isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &anitem) const;
	TreeNode<TreeItemType>* deleteItem_helper(TreeNode<TreeItemType> *&nodePtr);

	void rotate_left(TreeNode<TreeItemType> * node);
	void rotate_right(TreeNode<TreeItemType> * node);
	//void insert_case1(TreeNode<TreeItemType> * node);
	//void insert_case2(TreeNode<TreeItemType> * node);
	//void insert_case3(TreeNode<TreeItemType> * node);
	//void insert_case4(TreeNode<TreeItemType> * node);
	//void insert_case5(TreeNode<TreeItemType> * node);
private:
	TreeNode<TreeItemType> *root;
};

#include <algorithm>	// std::max
#include <iostream>		// std::cout, std::cin
#include <iomanip>		// std::setw, std::setf, std::right

template<class TreeItemType>
void rotate_left(TreeNode<TreeItemType> * node)
{
	TreeNode<TreeItemType> * pivot = node->rightChildPtr;
	pivot->parentPtr = node->parentPtr;
	if (node->parentPtr)
	{
		if (node->parentPtr->leftChildPtr == node)
		{
			node->parentPtr->leftChildPtr = pivot;
		}
		else
		{
			node->parentPtr->rightChildPtr = pivot;
		}
	}
	node->rightChildPtr = pivot->leftChildPtr;
	if (pivot->leftChildPtr)
	{
		pivot->leftChildPtr->parentPtr = node;
	}
	node->parentPtr = pivot;
	pivot->leftChildPtr = node;
}

template<class TreeItemType>
void rotate_right(TreeNode<TreeItemType> * node)
{
	TreeNode<TreeItemType> * pivot = node->leftChildPtr;
	pivot->parentPtr = node->parentPtr;
	if (node->parentPtr)
	{
		if (node->parentPtr->leftChildPtr == node)
		{
			node->parentPtr->leftChildPtr = pivot;
		}
		else
		{
			node->parentPtr->rightChildPtr = pivot;
		}
	}
	node->leftChildPtr = pivot->rightChildPtr;
	if (pivot->rightChildPtr)
	{
		pivot->rightChildPtr->parentPtr = node;
	}
	node->parentPtr = pivot;
	pivot->rightChildPtr = node;
}

template<class TreeItemType>
void insert_case1(TreeNode<TreeItemType> *node)
{
	if (node->parentPtr == NULL)
	{
		node ->color = TreeNode<TreeItemType>::BLACK;
	}
	else
	{
		insert_case2(node);
	}
}

template<class TreeItemType>
void insert_case2(TreeNode<TreeItemType> *node)
{
	if (node->parentPtr->color == TreeNode<TreeItemType>::BLACK)
	{
		return
	}
	else
	{
		insert_case3(node);
	}
}

template<class TreeItemType>
TreeNode<TreeItemType> *uncle(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *g = node->parentPtr->parentPtr;
	if (g->leftChildPtr == node->parentPtr)
	{
		return g->rightChildPtr;
	}
	else
	{
		return g->leftChildPtr;
	}
}

template<class TreeItemType>
TreeNode<TreeItemType> *grandpa(TreeNode<TreeItemType> *node)
{
	return node->parentPtr->parentPtr;
}

template<class TreeItemType>
void insert_case3(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *uncle = uncle(node);
	if (uncle && uncle->color == TreeNode<TreeItemType>::RED && node->parentPtr->color == TreeNode<TreeItemType>::RED)
	{
		node->parentPtr->color == TreeNode<TreeItemType>::BLACK;
		uncle->color = TreeNode<TreeItemType>::BLACK;
		TreeNode<TreeItemType> *grandpa = grandpa(node);
		grandpa->color == TreeNode<TreeItemType>::RED;
		insert_case1(grandpa);
	}
	else
	{
		insert_case4(node);
	}
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::deleteItem(TreeItemType &anitem)
{
	if (root->item == anitem)
		throw TreeException("TreeException: невозможно удалить корень дерева");
	TreeNode<TreeItemType> *tmpPtr = root, *nodePtr = NULL;
	while (tmpPtr != NULL && tmpPtr->item != anitem)
	{
		nodePtr = tmpPtr;
		if (anitem > tmpPtr->item)
			tmpPtr = tmpPtr->rightChildPtr;
		else
			tmpPtr = tmpPtr->leftChildPtr;
	}
	if (tmpPtr == NULL)
		throw TreeException("TreeException: элемент не найден");
	else
	{
		if (nodePtr->rightChildPtr != NULL)
		{
			if (nodePtr->rightChildPtr->item == anitem)
				nodePtr->rightChildPtr = deleteItem_helper(nodePtr->rightChildPtr);
		}
		if (nodePtr->leftChildPtr != NULL)
		{
			if (nodePtr->leftChildPtr->item == anitem)
				nodePtr->leftChildPtr = deleteItem_helper(nodePtr->leftChildPtr);
		}
	}
}

template<class TreeItemType>
TreeNode<TreeItemType>* BinaryTree<TreeItemType>::deleteItem_helper(TreeNode<TreeItemType>*& nodePtr)
{
	if (nodePtr->leftChildPtr == NULL)
	{
		if (nodePtr->rightChildPtr == NULL)
		{
			delete nodePtr;
			return NULL;
		}
		else
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
			delete nodePtr;
			return nextNodePtr;
		}
	}
	else // nodePtr->leftChildPtr != NULL
	{
		if (nodePtr->rightChildPtr == NULL)
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->leftChildPtr;
			delete nodePtr;
			return nextNodePtr;
		}
		else // nodePtr->leftChildPtr != NULL && nodePtr->rightChildPtr != NULL
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
			if (nextNodePtr->leftChildPtr == NULL)
			{
				nodePtr->item = nextNodePtr->item;
				nodePtr->rightChildPtr = nextNodePtr->rightChildPtr;
				delete nextNodePtr;
				return nodePtr;
			}
			else
			{
				while (nextNodePtr->leftChildPtr != NULL)
					nextNodePtr = nextNodePtr->leftChildPtr;
				nodePtr->item = nextNodePtr->item;
				TreeNode<TreeItemType> *tmpPtr = nodePtr->rightChildPtr;
				while (tmpPtr->leftChildPtr != nextNodePtr)
					tmpPtr = tmpPtr->leftChildPtr;
				tmpPtr->leftChildPtr = deleteItem_helper(nextNodePtr);
				return nodePtr;
			}
		}
	}
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist(TreeItemType &anitem) const
{
	return isExist_helper(root, anitem);
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &anitem) const
{
	if (nodePtr != NULL)
	{
		if (nodePtr->item == anitem)
			return 1;
		else if (anitem > nodePtr->item)
			return isExist_helper(nodePtr->rightChildPtr, anitem);
		else
			return isExist_helper(nodePtr->leftChildPtr, anitem);
	}
	else
		return 0;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print() const
{
	print_helper(root, getDepth());
}

template<class TreeItemType>
std::ostream& operator<<(std::ostream& out, const BinaryTree<TreeItemType> &tree)
{
	tree.print_helper(tree.root, tree.getDepth());
	return out;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print_helper(TreeNode<TreeItemType> *nodePtr, unsigned int level) const
{
	if (nodePtr)
	{
		print_helper(nodePtr->rightChildPtr, level - (unsigned int)1);
		std::cout << std::setw(level << (unsigned int)3) << std::setfill('-') << std::right << nodePtr->item << std::endl;
		print_helper(nodePtr->leftChildPtr, level - (unsigned int)1);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels() const
{
	std::queue<TreeNode<TreeItemType>*> levelHubs;
	levelHubs.push(root);
	printLevels_helper((unsigned int)0, levelHubs);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels_helper(unsigned int level, std::queue<TreeNode<TreeItemType>*> &levelHubs) const
{
	std::cout << "LEVEL " << level << ':' << std::endl;
	std::queue<TreeNode<TreeItemType>*> nextLevelHubs;
	while (!levelHubs.empty())
	{
		std::cout << levelHubs.front()->item << std::endl;
		if (levelHubs.front()->leftChildPtr != NULL)
			nextLevelHubs.push(levelHubs.front()->leftChildPtr);
		if (levelHubs.front()->rightChildPtr != NULL)
			nextLevelHubs.push(levelHubs.front()->rightChildPtr);
		levelHubs.pop();
	}
	if (nextLevelHubs.empty())
		return;
	else
		printLevels_helper(level + (unsigned int)1, nextLevelHubs);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
	{
		return getDepth_helper(root);
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return 0;
	else
	{
		return (unsigned int)1 + std::max(getDepth_helper(nodePtr->leftChildPtr), getDepth_helper(nodePtr->rightChildPtr));
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
		return getDepthOfMin_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMin_helper(nodePtr->leftChildPtr);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
		return getDepthOfMax_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (root == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMax_helper(nodePtr->rightChildPtr);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach(const TreeItemType &newItem)
{
	attach_helper(newItem, root);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr)
{
	if (nodePtr->isEmpty)
	{
		nodePtr->item = newItem;
		nodePtr->isEmpty = 0;
		nodePtr->color = TreeNode<TreeItemType>::RED;
		nodePtr->leftChildPtr = new TreeNode<TreeItemType>;
		nodePtr->rightChildPtr = new TreeNode<TreeItemType>;
		if (nodePtr->leftChildPtr == NULL || nodePtr->rightChildPtr == NULL)
			throw TreeException("TreeException: невозможно выделить память");
		nodePtr->leftChildPtr->parentPtr = nodePtr;
		nodePtr->rightChildPtr->parentPtr = nodePtr;
		//insert_case1(nodePtr);
	}
	else
	{
		if (newItem > nodePtr->item)
			attach_helper(newItem, nodePtr->rightChildPtr);
		else
			attach_helper(newItem, nodePtr->leftChildPtr);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree()
{
	root = new TreeNode<TreeItemType>;
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem)
{
	root = new TreeNode<TreeItemType>(rootitem);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem, BinaryTree<TreeItemType>& leftTree, BinaryTree<TreeItemType>& rightTree)
{
	root = new TreeNode<TreeItemType>(rootitem, NULL, NULL);
	attachLeftSubtree(leftTree);
	attachRightSubtree(rightTree);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const BinaryTree<TreeItemType>& tree)
{
	copyTree(tree.root, root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::~BinaryTree()
{
	destroyTree(root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(TreeNode<TreeItemType> *nodePtr) : root(nodePtr) {}

template <class TreeItemType>
bool BinaryTree<TreeItemType>::isEmpty() const
{
	return (root == NULL);
}

template <class TreeItemType>
TreeItemType BinaryTree<TreeItemType>::getRootData() const
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	return root->item;
} // Конец функции getRootData

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootData(const TreeItemType& newitem)
{
	if (!isEmpty())
		root->item = newitem;
	else
	{
		root = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root == NULL)
			throw TreeException(
				"TreeException: невозможно выделить память");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeft(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->leftChildPtr != NULL)
		throw TreeException("TreeException: переписать левое поддерево невозможно");
	else
	{
		root->leftChildPtr = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->leftChildPtr == NULL)
			throw TreeException("TreeException: невозможно выделить память ");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRight(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->rightChildPtr != NULL)
		throw TreeException("TreeException: невозможно переписать правое поддерево ");
	else
	{
		root->rightChildPtr = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->rightChildPtr == NULL)
			throw TreeException("TreeException: невозможно выделить память");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->leftChildPtr != NULL)
		throw TreeException("TreeException: невозможно переписать левое поддерево");
	else
	{
		root->leftChildPtr = leftTree.root;
		leftTree.root = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->rightChildPtr != NULL)
		throw TreeException("TreeException: невозможно переписать правое поддерево");
	else
	{
		root->rightChildPtr = rightTree.root;
		rightTree.root = NULL;

	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->leftChildPtr == NULL)
		throw TreeException("TreeException: левого поддерева не существует");
	else
	{
		leftTree = BinaryTree<TreeItemType>(root->leftChildPtr);
		root->leftChildPtr = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->rightChildPtr == NULL)
		throw TreeException("TreeException: правого поддерева не существует");
	else
	{
		rightTree = BinaryTree<TreeItemType>(root->rightChildPtr);
		root->rightChildPtr = NULL;
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getLeftSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->leftChildPtr, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getRightSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->rightChildPtr, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorderTraverse(void(*visit)(TreeItemType &anitem))
{
	preorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorderTraverse(void(*visit)(TreeItemType &anitem))
{
	inorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorderTraverse(void(*visit)(TreeItemType &anitem))
{
	postorder(root, visit);
}

template <class TreeItemType>
BinaryTree<TreeItemType>& BinaryTree<TreeItemType>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		destroyTree(root);
		copyTree(rhs.root, root);
	}
	return *this;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::copyTree(TreeNode<TreeItemType> *treePtr, TreeNode<TreeItemType> *& newTreePtr) const
{
	if (treePtr != NULL)
	{
		newTreePtr = new TreeNode<TreeItemType>(treePtr->item, NULL, NULL);
		if (newTreePtr == NULL)
			throw TreeException("TreeException: невозможно выделить память");
		copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
		copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
	}
	else
		newTreePtr = NULL;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::destroyTree(TreeNode<TreeItemType> *& treePtr)
{
	if (treePtr != NULL)
	{
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}

template <class TreeItemType>
TreeNode<TreeItemType> *BinaryTree<TreeItemType>::rootPtr() const
{
	return root;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootPtr(TreeNode<TreeItemType> *newRoot)
{
	root = newRoot;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::getChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *& leftPtr, TreeNode<TreeItemType> *& rightPtr) const
{
	leftPtr = nodePtr->leftChildPtr;
	rightPtr = nodePtr->rightChildPtr;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::setChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *leftPtr, TreeNode<TreeItemType> *rightPtr)
{
	nodePtr->leftChildPtr = leftPtr;
	nodePtr->rightChildPtr = rightPtr;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		visit(treePtr->item);
		preorder(treePtr->leftChildPtr, visit);
		preorder(treePtr->rightChildPtr, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		inorder(treePtr->leftChildPtr, visit);
		visit(treePtr->item);
		inorder(treePtr->rightChildPtr, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		postorder(treePtr->leftChildPtr, visit);
		postorder(treePtr->rightChildPtr, visit);
		visit(treePtr->item);
	}
}