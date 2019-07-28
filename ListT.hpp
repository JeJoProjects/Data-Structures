/******************************************************************************
 * Simple template implementation of a List(insert at position n) class.
 *
 * @Authur : JeJo
 * @Date   : 03 - 12 -2017
 * @license: free to use and distribute(no further support as well)
 *
 *****************************************************************************/

#ifndef LIST_T_HPP
#define LIST_T_HPP


// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <string>
#include <memory>               // std::unique_ptr
#include <utility>              // std::move
#include <cstddef>              // std::size_t
#include <stdexcept>            // std::runtime_error
#include <initializer_list>     // std::initializer_list

JEJO_BEGIN

/* class 'List<>': provides a class for list, where elements could be
 * inserted at the user provided position.
 *
 * However, the positions greater than the size of the List<> shall not be
 * provided.
 *
 * @tparam: generic type
 */
template<typename Type> class List final
{
private:
	/* class 'Node': provides a class for keeping resources in the list
	 * implementation.
	 *
	 * @tparam: 'Node' has a data member of generic type.
	 */
	template<typename T> struct Node final
	{
		T data{};
		std::unique_ptr<Node<T>> nextNode = nullptr;
		~Node() { std::cout << "Deleting: " << data << '\n'; }
	};

private:
	// convenience (template alias)type(s)
	using NodeT = Node<Type>;
	using UPtrNode = std::unique_ptr<NodeT>;

	// head of the list
	UPtrNode _headNode = nullptr;
	// size of the list
	std::size_t _size = 0;
	// last element of the list
	Type _lastElement{};

public:
	// Constructor(s)
	List() = default;
	/* @todo: since it is a test project, further care for copying
	 * and moving of 'List' class not been considered.
	 *
	 * For simplicity-sake, they are simply disabled.
	 */
	List(const List&) = delete;
	List& operator=(const List&) = delete;
	List(List&&) = delete;
	List& operator=(List&&) = delete;

	// list initialization constructor
	List(const std::initializer_list<Type> list) noexcept
	{
		for (const Type& element : list) this->insert(element);
	}

	// return the size of the list
	std::size_t size() const noexcept { return _size; }

	// return the state of the list
	bool is_empty() const noexcept { return _headNode == nullptr; }

	// return the front of the list
	Type front() const
	{
		return this->is_empty() // @todo this needed to be improved
			? throw std::string{ "The list is empty: front() call failed!" }
			: _headNode->data;
	}

	// return the back of the list
	Type back() const
	{
		return this->is_empty() // @todo this needed to be improved
			? throw std::string{ "The list is empty: back() call failed!" }
			: _lastElement;
	}

	void insert(std::size_t pos, const Type &data)
	{
		UPtrNode tempNode = std::make_unique<NodeT>();
		tempNode->data = data;
		if (pos == 0) //@todo handle non valid positions
		{
			tempNode->nextNode = std::move(_headNode);
			_headNode = std::move(tempNode);
			++_size;   // increment the size
			_lastElement = _headNode->data;
		}
		else
		{
			NodeT *getNode = _headNode.get();
			for (std::size_t index = 0; index < pos - 1; ++index)
				getNode = getNode->nextNode.get();

			tempNode->nextNode = std::move(getNode->nextNode);
			getNode->nextNode = std::move(tempNode);
			++_size; // increment the size
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const List &obj) noexcept
	{
		for (const NodeT *tempNode = obj._headNode.get();
			tempNode;
			tempNode = tempNode->nextNode.get())
		{
			out << tempNode->data << " ";
		}
		return out << std::endl;
	}
};

/*************** test function(s) to be called in the main() *****************/
void testList()
{
	List<int> obj;
	for (std::size_t i = 0; i < 3; ++i)
	{
		int input;
		std::cout << "Enter element: "; std::cin >> input;
		obj.insert(i, input);
		std::cout << obj;
		std::cout << "First element: " << obj.front() << " "
			<< "Last element: " << obj.back() << std::endl;
	}
	std::cout << "Hello\n";
	obj.insert(1, 2022);
	obj.insert(3, 40);
	std::cout << obj;
}

JEJO_END

#endif // LIST_T_HPP

/*****************************************************************************/
