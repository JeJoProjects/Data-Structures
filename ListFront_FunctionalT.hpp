/******************************************************************************
 * following functions are not well implemented. It has the problem of using
 * std::unique_ptr<>, which has to be solved, before start using them.
 *
 * @Authur : JeJo
 * @Date   : 01 - 12 -2017
 * @license: free to use and distribute(no further support as well)
 *
 * 1: @todo(function description)  : frontInsert()
 * 2: @todo(function description)  : print()
 * 3: @todo(function description)  : rangeSum()
 *
 * @tparam: each 'Node' has a data member of generic type
 *****************************************************************************/

#ifndef LIST_FRONT_FUNCTIONAL_T_HPP
#define LIST_FRONT_FUNCTIONAL_T_HPP

// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <memory>               // std::unique_ptr
#include <utility>              // std::move
#include <initializer_list>     // std::initializer_list

JEJO_BEGIN

// forward declaration
template<typename Type> struct Node;

// convenience (template alias)type
template<typename Type>
using UPtrNode = std::unique_ptr<Node<Type>>;

/* class 'Node': provides a class for keeping resources in the list
 * implementation, where elements would be inserted at the front of the list.
 *
 * @tparam: each 'Node' has a data member of generic type
 */
template<typename Type> struct Node final
{
	Type data{};
	UPtrNode<Type> nextNode = nullptr;
	~Node() { std::cout << "\nDeleting: " << data << " "; }
};

template<typename Type>
constexpr void frontInsert(UPtrNode<Type> &head, const Type x) noexcept
{
	UPtrNode<Type> tempNode = std::make_unique<Node<Type>>();
	tempNode->data = std::move(x);
	tempNode->nextNode = std::move(head);
	head = std::move(tempNode);
}

template<typename Type>
constexpr void print(UPtrNode<Type> Head) noexcept
{
	std::cout << "The list is: ";
	while (Head)
	{
		std::cout << (*Head).data << " ";
		Head = std::move(Head->nextNode);
	}
	std::cout << '\n';
}

/*********************** test-function to be called for testing ***************/
template<typename Type>
void testListFront_function(const std::initializer_list<Type> list) noexcept
{
	UPtrNode<Type> head = nullptr;

	for (const Type &element : list)
	{
		JeJo::frontInsert(head, element);
	}
	JeJo::print(std::move(head));
}

JEJO_END

#endif // LIST_FRONT_FUNCTIONAL_T_HPP

/*****************************************************************************/
