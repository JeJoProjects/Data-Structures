/******************************************************************************
 * Simple template implementation of a binary search class.
 *
 * @Authur : JeJo
 * @Date   : 10 - 12 -2017
 * @license: free to use and distribute(no further support as well)
 *
 Algorithm		Average case    Worst case
  Space		     O(n)              O(n)
  Search         O(log n)          O(n) @todo
  Insert         O(log n)          O(n)
  Delete         O(log n)          O(n) @todo
 *****************************************************************************/

#ifndef BINARY_SEARCH_TREE_T_HPP
#define BINARY_SEARCH_TREE_T_HPP

// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <memory>      // std::unique_ptr
#include <utility>     // std::move, std::exchange
#include <type_traits> // std::is_fundamental

JEJO_BEGIN

template<typename Type> class BinarySearchTree final
{
private:
	template<typename T> struct Node final
	{
		// members of Node<T>
		T key;   // T must default constructible
		std::unique_ptr<Node<T>> rightNode;
		std::unique_ptr<Node<T>> leftNode;

		// explicit constructor
		explicit Node(const T& k)
			: rightNode{ nullptr }
			, leftNode{ nullptr }
			, key{k}
		{}

		// copy disabled
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		// move enabled
		Node(Node&& other)
			: key{ std::is_fundamental<T>
			        ? other->key
			        : std::exchange(other->key, T{}) }
			, rightNode{ std::exchange(other.rightNode, nullptr) }
			, leftNode{ std::exchange(other.leftNode, nullptr) }
		{}
		Node& operator=(Node&& other)
		{
			this->key = std::is_fundamental<T>
				? other->key
				: std::exchange(other->key, T{});
			this->rightNode = std::exchange(other.rightNode, nullptr);
			this->leftNode = std::exchange(other.leftNode, nullptr);
			return *this;
		}

		// destructor
#if _DEBUG
		~Node() 
		{
			std::cout << "Deleting: " << this->key << "\n";
		}
#endif // _DEBUG
	};

	// convenience types
	using NodeT = Node<Type>;
	using UPtrNodeT = std::unique_ptr<NodeT>;

	// member (root) pointer node
	UPtrNodeT _rootNode;

private:
	// internal function(s)
	// helper function to insert the nodes
	void insertHelper(UPtrNodeT& root, const Type& keyArg)
	{
#if _DEBUG
		std::cout << "Now processing: " << keyArg << '\t';
#endif
		// if the tree is empty, return a new node
		if (!root)
		{
			root = std::make_unique<NodeT>(keyArg);
#if _DEBUG
			std::cout << "created...: " << keyArg << '\n';
#endif
			return;
		}
		// same entries(@todo value should be replaced)
		else if (root && keyArg == root->key)
		{
#if _DEBUG
			std::cout << "Key already exist!\n";
#endif
			return;
		}
		else if (root && keyArg < root->key)
		{
#if _DEBUG
			std::cout << "keyArg < root->key\n";
#endif
			this->insertHelper(root->leftNode, keyArg);
		}
		else if (keyArg > root->key)
		{
#if _DEBUG
			std::cout << "keyArg > root->key\n";
#endif
			this->insertHelper(root->rightNode, keyArg);
		}
#if _DEBUG
		else
		{
			std::cout << "Error part!\n" << '\n';
		}
#endif
	}

	// helper function for ostream operator<<
	void ostreamHelper(std::ostream& out, const UPtrNodeT& root) const noexcept
	{
		if (root)
		{
			ostreamHelper(out, root->leftNode);
			out << root->key << " ";
			ostreamHelper(out, root->rightNode);
		}
	}

public:
	// default constructor
	BinarySearchTree()
		: _rootNode{ nullptr }
	{}

	// to insert the key to the tree
	void insert(const Type& keyArg)
	{
		this->insertHelper(_rootNode, keyArg);
	}

	// non-member: ostream operator<< overload
	friend std::ostream& operator<<(
		std::ostream& out, const BinarySearchTree& obj) noexcept
	{
		out << "Binary search tree....: ";
		obj.ostreamHelper(out, obj._rootNode);
		return out << '\n';
	}
};

JEJO_END

#endif // BINARY_SEARCH_TREE_T_HPP

/*****************************************************************************/
