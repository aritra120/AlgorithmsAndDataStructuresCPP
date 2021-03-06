#pragma once

#include "TreeType.h"
#include "BrinarySortedNode.cpp"

#include <stddef.h>
#include <iostream>

using namespace std;



template <class ItemType>
void BinarySearchTree<ItemType>::displayInOrder()
{
	displayInOrder(root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::displayPreOrder()
{
	displayPreOrder(root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::displayPostOrder()
{
	displayPostOrder(root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::displayInOrder(TreeNode< ItemType>* nodePtr)
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->left);
		cout << nodePtr->info << " ";
		displayInOrder(nodePtr->right);
	}
}
template <class T>
void BinarySearchTree<T>::displayPreOrder(TreeNode < T>* nodePtr)
{
	if (nodePtr)
	{
		cout << nodePtr->info << " ";
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

template <class T>
void BinarySearchTree<T>::displayPostOrder(TreeNode<T>* nodePtr)
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->info << " ";
	}

}

//
//	helper functions
template<class ItemType>
int CountNodes(TreeNode<ItemType>* treeNode)
{
	if (treeNode == NULL)
		return 0;
	else
		return CountNodes(treeNode->left) +
		CountNodes(treeNode->right) + 1;
}

//
//	helper functions
template<class ItemType>
int SumNodes(TreeNode<ItemType>* treeNode)
{
	if (treeNode == NULL)
		return 0;
	else
		return SumNodes(treeNode->left) +
		SumNodes(treeNode->right) + treeNode->info;
}

//
//	helper functions
template<class ItemType>
int SumOfLeafNodes1(TreeNode<ItemType>* treeNode)
{
	if (treeNode == NULL)
		return 0;
	else if (treeNode->IsLeaf())
		return treeNode->info;
	else
		return SumOfLeafNodes1(treeNode->left) +
		SumOfLeafNodes1(treeNode->right);
}


template<class ItemType>
int BinarySearchTree<ItemType>::NumberOfNodes() const
{
	return CountNodes(root);
}

template<class ItemType>
int BinarySearchTree<ItemType>::SumOfNodes() const
{
	return SumNodes(root);
}
template<class ItemType>
int BinarySearchTree<ItemType>::SumOfLeafNodes() const
{
	return SumOfLeafNodes1(root);
}


template<class ItemType>
void Retrieve(TreeNode<ItemType>* treeNode, ItemType& item, bool& found)
{

	if (treeNode == NULL)
		found = false; // item is not found.
	else if (item < treeNode->info) // Search left subtree.
		Retrieve(treeNode->left, item, found);
	else if (item > treeNode->info) // Search right subtree.
		Retrieve(treeNode->right, item, found);
	else
	{ // item is found.
		item = treeNode->info; found = true;
	}
}

template<class ItemType>    void BinarySearchTree<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Calls recursive function Retrieve to search  // the tree for item.
{
	Retrieve(root, item, found);
}

template<class ItemType>
void Insert(TreeNode<ItemType>*& treeNode, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is    //    maintained.
{
	if (treeNode == NULL)
	{ // Insertion place found.
		treeNode = new TreeNode<ItemType>(item);
	}
	else if (item < treeNode->info)
		Insert(treeNode->left, item);       // Insert in left subtree.
	else
		Insert(treeNode->right, item);     // Insert in right subtree.
}
template<class ItemType>
void BinarySearchTree<ItemType>::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	Insert(root, item);
}
template<class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
	if (item < tree->info)
		Delete(tree->left, item);  // Look in left subtree.
	else if (item > tree->info)
		Delete(tree->right, item);  // Look in right subtree.
	else
		DeleteNode(tree);  // Node found; call DeleteNode.
}

template<class ItemType>
void BinarySearchTree<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item // from tree.
{
	Delete(root, item);
}
template<class ItemType>    void DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to // by tree is no longer in the tree.  If tree is // a leaf node or has only non-NULL child pointer // the node pointed to by tree is deleted;      // otherwise, the user's data is replaced by its // logical predecessor and the predecessor's node // is deleted.
{
	TreeNode<ItemType>* tempPtr;



	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		ItemType data = tree->info;
		GetPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data); // Delete predecessor node.
	}
}



template<class ItemType>    void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most // node in tree.
{
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}

template<class ItemType>
void BinarySearchTree<ItemType>::PrintTree(ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
	Print(root, outFile);
}


template<class ItemType>
void Print(TreeNode<ItemType>* tree, ofstream& outFile)
// Prints info member of items in tree in sorted // order on outFile.
{
	if (tree != NULL)
	{
		Print(tree->left, outFile); // Print left subtree.
		outFile << tree->info;
		Print(tree->right, outFile); // Print right subtree.
	}
}

template<class ItemType>     void InPrint(TreeNode<ItemType>* tree, ofstream& outFile)
// Prints info member of items in tree in sorted // order on outFile.
{
	if (tree != NULL)
	{
		InPrint(tree->left, outFile); // Print left subtree.
		outFile << tree->info;
		InPrint(tree->right, outFile); // Print right subtree.
	}
}

template<class ItemType>
void PrePrint(TreeNode<ItemType>* tree, ofstream& outFile)
// Prints info member of items in tree in sorted // order on outFile.
{
	if (tree != NULL)
	{
		outFile << tree->info;
		PrePrint(tree->left, outFile); // Print left subtree.
		PrePrint(tree->right, outFile); // Print right subtree.
	}
}

template<class ItemType>
void PostPrint(TreeNode<ItemType>* tree, ofstream& outFile)
// Prints info member of items in tree in sorted // order on outFile.
{
	if (tree != NULL)
	{
		PostPrint(tree->left, outFile); // Print left subtree.
		PostPrint(tree->right, outFile); // Print right subtree.
		outFile << tree->info;
	}
}

template<class ItemType>
bool BinarySearchTree<ItemType>::IsEmpty() const
{
	return root == NULL;
}


template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
	root = NULL;
}
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
// Post: tree is empty; nodes have been deallocated.
{
	if (tree != NULL)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}


template<class ItemType>
void BinarySearchTree<ItemType>::BinarySearchTree::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}





