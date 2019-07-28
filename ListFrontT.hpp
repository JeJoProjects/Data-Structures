/******************************************************************************
 * Simple template implementation of a List(front insertion) class.
 *
 * @Authur : JeJo
 * @Date   : 01 - 12 -2017
 * @license: free to use and distribute(no further support as well)
 *
 *****************************************************************************/

#ifndef LIST_FRONT_T_HPP
#define LIST_FRONT_T_HPP

// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <memory>               // std::unique_ptr
#include <utility>              // std::move
#include <cstddef>              // std::size_t
#include <stdexcept>            // std::runtime_error
#include <initializer_list>     // std::initializer_list

JEJO_BEGIN

/* class 'ListFront<>': provides a class for list, where elements could be
 * inserted at the front of the list.
 *
 * @tparam: generic type
 */
template<typename Type> class ListFront final
{
private:
	/* class 'Node': provides a class for keeping resources in the list
	 * implementation, where elements would be inserted at the front of
	 * the list.
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
	ListFront() = default;
	/* @todo: since it is a test project, further care for copying
	 * and moving of 'ListFront' class not been considered.
	 *
	 * For simplicity-sake, they are simply disabled.
	 */
	ListFront(const ListFront&) = delete;
	ListFront& operator=(const ListFront&) = delete;
	ListFront(ListFront&&) = delete;
	ListFront& operator=(ListFront&&) = delete;

	// list initialization constructor
	ListFront(const std::initializer_list<Type> list)
	{
		for (const Type& element : list) this->insert(element);
	}

	// return the size of the list
	std::size_t size() const noexcept { return _size; }

	// return the state of the list
	bool is_empty() const noexcept { return _headNode == nullptr; }

	// return the last inserted element(front) of the list
	const Type front() const noexcept
	{
		return this->is_empty()
			? (Type{}) // @todo this needed to be improved
			: _headNode->data;
	}

	// return the first inserted element(back) of the list
	const Type back() const noexcept
	{
		return this->is_empty()
			? (Type{}) // @todo this needed to be improved
			: _lastElement;
	}

	void insert(const Type &x) noexcept
	{
		UPtrNode tempNode = std::make_unique<NodeT>();
		tempNode->data = x;
		tempNode->nextNode = std::move(_headNode);
		_headNode = std::move(tempNode);
		++_size; // increment the size
		if (_size == 1) _lastElement = _headNode->data;
	}

	friend std::ostream& operator<<(
		std::ostream& out, const ListFront &obj) noexcept
	{
		out << "The list is: ";

		const NodeT *tempNode = obj._headNode.get();
		for ( ; tempNode ; tempNode = tempNode->nextNode.get())
			out << tempNode->data << " ";

		return delete tempNode, tempNode = nullptr, out << '\n';
	}
};

/*************** test function to be called in the main() *****************/
template<typename Type>
void testListFront(const std::initializer_list<Type> list)
{
	ListFront<Type> obj{ list };
	std::cout << std::boolalpha
		<< "is empty: " << obj.is_empty()
		<< "\nthe element at front: " << obj.front() << '\n';

	std::cout << "Enter number of elements in the array: ";
	std::size_t size; std::cin >> size;
	while (size--)
	{
		std::cout << "Enter the element: ";
		Type x;
		std::cin >> x;
		obj.insert(x);

		std::cout << "The size: " << obj.size() << ", "
			<< "is empty: " << obj.is_empty() << ", "
			<< "The front: " << obj.front() << ", "
			<< "The back: " << obj.back() << ", "
			<< obj << '\n';
	}
	std::cout << "\nTest success\n";
}

JEJO_END

#endif // LIST_FRONT_T_HPP

/*****************************************************************************/
