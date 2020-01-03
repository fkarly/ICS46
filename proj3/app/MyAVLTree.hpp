#ifndef __PROJ_THREE_AVL_HPP
#define __PROJ_THREE_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	size_t count = 0;
	struct Node
	{
		Value value;
		Key key;
		Node * leftChild;
		Node * rightChild;
		Node * parent;
	};
	Node * root;
	std::vector<Key> inOrderVec;
	std::vector<Key> preOrderVec;
	std::vector<Key> postOrderVec;

public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For ICS 46, Fall 2019, I am not requiring these.
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required.


	~MyAVLTree()
	{
		deleteAll(root);
	}
	size_t size() const noexcept;
	bool isEmpty() const noexcept;
	bool contains(const Key & k) const;
	Value & find(const Key & k);
	const Value & find(const Key & k) const;
	void insert(const Key & k, const Value & v);
	void leftRotation(Node * node);
	void rightRotation(Node * node);
	std::vector<Key> inOrder();
	void inOrderRecursion(Node * node);
	std::vector<Key> preOrder();
	void preOrderRecursion(Node * node);
	std::vector<Key> postOrder();
	void postOrderRecursion(Node * node);
	void deleteAll(Node * node);
	int height(Node * node);
	void findAndInsert(Key k, Value v);

};

// AVL Tree Constructor
template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{
	root = nullptr;
}

// Return the size of the Tree
template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return count;
}

// Determines whether or not the tree is empty
template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return count == 0;
}

// Check if the tree contains a node with specific key
// Check the place where it would be placed at the first place.
template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
	Node * tmp = new Node();
	tmp = root;
	while(tmp != nullptr)
	{
		if(tmp->key == k)
			return true;
		else
		{
			if(k < tmp->key)
				tmp = tmp->leftChild;
			if(k > tmp->key)
				tmp = tmp->rightChild;
		}
	}

	return false;
}

// Find the key and return the value of the Node
// if it's there. Else, thrown an exception.
template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	Node * tmp = new Node();
	tmp = root;

	if(root == nullptr)
	{
		try
		{
			throw ElementNotFoundException("Element not found!");
		}
		catch(ElementNotFoundException& e)
		{ std::cout << e << std::endl;}
	}

	while(tmp != nullptr)
	{
		if(tmp->key == k)
			break;
		// If the search key is smaller than the current node key
		// search through the left.
		if(k < tmp->key)
		{
			try
			{
				if(tmp->leftChild != nullptr)
					tmp = tmp->leftChild;
				else
					throw ElementNotFoundException("Element not found!");
			}
			catch(ElementNotFoundException& e)
			{ std::cout << e << std::endl; break;}
		}

		// If the search key is grater than the current node key
		// search through the right.
		if(k > tmp->key)
		{
			try
			{
				if(tmp->rightChild != nullptr)
					tmp = tmp->rightChild;
				else
					throw ElementNotFoundException("Element not found!");
			}
			catch(ElementNotFoundException& e)
			{ std::cout << e << std::endl; break; }
		}
	}

	return tmp->value;
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	Node * tmp = new Node();
	tmp = root;

	if(root == nullptr)
	{
		try
		{
			throw ElementNotFoundException("Element not found!");
		}
		catch(ElementNotFoundException& e)
		{ std::cout << e << std::endl;}
	}

	while(tmp != nullptr)
	{
		if(tmp->key == k)
			break;
		// If the search key is smaller than the current node key
		// search through the left.
		if(k < tmp->key)
		{
			try
			{
				if(tmp->leftChild != nullptr)
					tmp = tmp->leftChild;
				else
					throw ElementNotFoundException("Element not found!");
			}
			catch(ElementNotFoundException& e)
			{ std::cout << e << std::endl; break;}
		}

		// If the search key is grater than the current node key
		// search through the right.
		if(k > tmp->key)
		{
			try
			{
				if(tmp->rightChild != nullptr)
					tmp = tmp->rightChild;
				else
					throw ElementNotFoundException("Element not found!");
			}
			catch(ElementNotFoundException& e)
			{ std::cout << e << std::endl; break; }
		}
	}

	return tmp->value;
}

// Inserting node to the tree
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	Node * tmp = new Node();

	// If the tree is empty, then create a new node with the k key and v value
	// and set that node as the root. Increment count counter
	if(isEmpty() == true)
	{
		tmp->value = v;
		tmp->key = k;
		tmp->leftChild = nullptr;
		tmp->rightChild = nullptr;
		tmp->parent = nullptr;
		root = tmp;
		count++;
	}
	else
	{
		// Set the temporary pointer to the root
		// and create a new node containing the new key and value.
		tmp = root;
		Node * newNode = new Node();
		newNode->value = v;
		newNode->key = k;
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
		// Temporary pointer will find a place to store the new node
		// If the new node is greater than the temporary pointed node,
		// then move to the right child; else, move to lett child
		// Until there is a spot to put the new node. Increment the count counter.
		while(tmp != nullptr)
		{
			if(k < tmp->key)
			{
				if(tmp->leftChild != nullptr)
					tmp = tmp->leftChild;
				else
				{
					tmp->leftChild = newNode;
					newNode->parent = tmp;
					count++;
					break;
				}
			}
			if(k > tmp->key)
			{
				if(tmp->rightChild != nullptr)
					tmp = tmp->rightChild;
				else
				{
					tmp->rightChild = newNode;
					newNode->parent = tmp;
					count++;
					break;
				}
			}
		}
	}

	// Balancing part. If the newly added node causes the tree to be unbalance,
	// search for the first unbalanced node from the newly added node,
	// then make a rotation.
	while(tmp != nullptr)
	{
		// Left Left Case
		if(height(tmp->leftChild) - height(tmp->rightChild) > 1 && k < tmp->leftChild->key)
		{
			rightRotation(tmp);
			break;
		}

		// Left Right Case
		if(height(tmp->leftChild) - height(tmp->rightChild) > 1 && k > tmp->leftChild->key)
		{
			leftRotation(tmp->leftChild);
			rightRotation(tmp);
			break;
		}

		// Right Right Case
		if(height(tmp->leftChild) - height(tmp->rightChild) < -1 && k > tmp->rightChild->key)
		{
			leftRotation(tmp);
			break;
		}

		// Right Left Case
		if(height(tmp->leftChild) - height(tmp->rightChild) < -1 && k < tmp->rightChild->key)
		{
			rightRotation(tmp->rightChild);
			leftRotation(tmp);
			break;
		}

		tmp = tmp->parent;
	}
}

// Left Rotation
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::leftRotation(Node * z)
{
	/*
	 Rotate this:
			z
		 / \
		t1  y
			 / \
			t2 x
				/ \
			t3  t4

		to:

				 y
			 /  \
		  z    x
		 / \  / \
		t1 t2t3 t4
	*/
	Node * y = z->rightChild;
	Node * t2 = y->leftChild;

	//set the y parent to the z parent.
	y->parent = z->parent;

	// If z has parent, comparet he value of y and z parent.
	// If y is smaller, then set z parent left child equal to y.
	// If y is grater, than set z parent right child equal to y.
	// If was the root, set y to become the new root.
	if(z->parent != nullptr)
	{
	  if(y->key < z->parent->key)
			z->parent->leftChild = y;
		else
			z->parent->rightChild = y;
	}
	else
		root = y;

	// Move z to become the left child of y, and set z parent to y
	// Attach whatever was in t2 to become the right child of z.
	y->leftChild = z;
	z->parent = y;
	z->rightChild = t2;
	if(t2 != nullptr)
		t2->parent = z;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rightRotation(Node * z)
{
	/*
	 Rotate this:
		 			z
				 /\
				y	t4
			 /\
		  x t3
		 / \
		t1 t2

		to:

				 y
			 /  \
		  x    z
		 / \  / \
		t1 t2t3 t4
	*/

	Node * y = z->leftChild;
	Node * t3 = y->rightChild;

	// If z has parent, comparet he value of y and z parent.
	// If y is smaller, then set z parent left child equal to y.
	// If y is grater, than set z parent right child equal to y.
	// If was the root, set y to become the new root.
	y->parent = z->parent;
	if(z->parent != nullptr)
	{
		if(y->key < z->parent->key)
			z->parent->leftChild = y;
		else
			z->parent->rightChild = y;
	}
	else
		root = y;

	// Move z to become the right child of y, and set z parent to y
	// Attach whatever was in t3 to become the left child of z.
	y->rightChild = z;
	z->parent = y;
	z->leftChild = t3;
	if(t3 != nullptr)
		t3->parent = z;
}

// Calls the inOrderRecursion and return the in order traversal vector.
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder()
{
	inOrderRecursion(root);
	return inOrderVec;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrderRecursion(Node * node)
{

	// Left, root, right.
	if(node != nullptr)
	{
		//std::cout <<"root = " << node->key << std::endl;
		inOrderRecursion(node->leftChild);
		//std::cout << node->key << " ";
		inOrderVec.push_back(node->key);
		inOrderRecursion(node->rightChild);
	}
}

// Calls the preOrderRecursion and return the pre order traversal vector.
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder()
{
	preOrderRecursion(root);
	return preOrderVec;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrderRecursion(Node * node)
{
	// Root, left, right.
	if(node != nullptr)
	{
		//std::cout << node->key << " ";
		preOrderVec.push_back(node->key);
		preOrderRecursion(node->leftChild);
		preOrderRecursion(node->rightChild);
	}
}

// Calls the postOrderRecursion and return the post order traversal vector.
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder()
{
	postOrderRecursion(root);
	return postOrderVec;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrderRecursion(Node * node)
{
	// Left, right, root.
	if(node != nullptr)
	{
		postOrderRecursion(node->leftChild);
		postOrderRecursion(node->rightChild);
		//std::cout << node->key << " ";
		postOrderVec.push_back(node->key);
	}
}

// Deleting all the nodes
// WORK IN PROGRESS !!!
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::deleteAll(Node * node)
{
	if(node != nullptr)
	{
		if(node->leftChild != nullptr)
			deleteAll(node->leftChild);
		if(node->rightChild != nullptr)
			deleteAll(node->rightChild);
		delete node;
	}
}

// Height function
// Leaf = 0, parent = 1, etc.
// Null pointer = -1
template<typename Key, typename Value>
int MyAVLTree<Key, Value>::height(Node * node)
{
	if(node == nullptr)
		return -1;
	else
		return std::max(height(node->leftChild), height(node->rightChild)) + 1;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::findAndInsert(Key k, Value v)
{
	Node * tmp = new Node();
	tmp = root;

	// If the there isn't any node in the tree, perform insertion
	if(root == nullptr)
	{
		insert(k,v);
	}

	while(tmp != nullptr)
	{
		if(tmp->key == k)
		{
			tmp->value = tmp->value + 1;
			return;
		}
		else
		{
			// If the search key is smaller than the current node key
			// search through the left.
			// If key is not found, do insertion.
			if(k < tmp->key)
			{
				if(tmp->leftChild != nullptr)
					tmp = tmp->leftChild;
				else
				{
				 	insert(k, v);
					return;
				}
			}
			// If the search key is grater than the current node key
			// search through the right.
			// If key is not found, do insertion.
			if(k > tmp->key)
			{
				if(tmp->rightChild != nullptr)
					tmp = tmp->rightChild;
				else
				{
					insert(k, v);
					return;
				}
			}
		}
	}
}

#endif
