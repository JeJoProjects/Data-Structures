/******************************************************************************
 * Simple implementation of template class Binary Indexed Tree(Fenwick Tree).
 *
 * @Authur :  JeJo
 * @Date   :  01 - 02 -2018
 * @license: free to use and distribute(no further support as well)
 *
 * Provides a data structure which allows:
 *     calculation of prefix-sum : O(log (n)) complexity
 *     element update            : O(log (n)) complexity
 * This is achieved by representing the numbers as a tree, where the value of
 * each node is the sum of the numbers in that subtree.
 *****************************************************************************/

#ifndef FENWICK_TREE_T_HPP
#define FENWICK_TREE_T_HPP

// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <vector>               // std::vector<>
#include <cstddef>              // std::size_t
#include <initializer_list>     // std::initializer_list<>
#include <type_traits>          // std::is_arithmetic

JEJO_BEGIN

/* class 'FenwickTree<>': provides all the possible operations on the
 * Fenwick Tree(also known as Binary Indexed Tree).
 *
 * See    : https://www.youtube.com/watch?v=v_wj_mOAlig
 * @tparam: uses class template SFINAE technique, to conditionally instantiate
 * the class template depending on the template arguments
 * integers or floating.
 * i.e. partial specialization for the class FenwickTree<Type, void>.
 */

/* convenience template alias type to specialize the FenwickTree<> class only
 * for integer and floating types.
 */
template<typename T>
using only_for_integrals = std::enable_if_t<std::is_arithmetic_v<T>, void>;

// default FenwickTree<> case: not implemented
template<typename T, typename Enable = void> class FenwickTree;

// o-stream operator overload for convenience printing
template<typename T>
std::ostream& operator<<(std::ostream& out,
	const FenwickTree<T, only_for_integrals<T>> &obj) noexcept;

// definition of specialized FenwickTree<>
template<typename Type>
class FenwickTree<Type, only_for_integrals<Type>> final
{
private:
	// internal storage of tree element
	std::vector<Type> _array;

	// convenience type(s)
	using size_type = typename std::vector<Type>::size_type;

public:
	using int64 = long long int;

	// Constructor(s)
	explicit FenwickTree(const size_type size) noexcept
		: _array(size + 1)
	{}

	explicit FenwickTree(const std::initializer_list<Type> list) noexcept
		: _array(list.size() + 1)
	{
		int64 index = 1;
		std::cout << "Constructing tree...................................\n";
		for (const Type element: list) this->insert_at(element, index++);
		std::cout << "Construction finished...\n";
	}

	// returns weather the tree is empty
	bool empty() const noexcept { return this->_array.empty(); }

	// returns the size of the tree
	size_type size() const noexcept { return this->_array.size() - 1; }

	/** Remove last set bit of number x (to go back or for summing)
	 *
	 * Exact last set bit   :     x & (-x)
	 * Remove it            : x - x & (-x)
	 * Example      : x =  13 = 00001101
	 *               -x = -13 = 11110011
	 *          x & (-x)=       00000001
	 *      x - x & (-x)=       00001100
	 *
	 */

	// inserts the element at the given index
	void insert_at(const Type element, int64 index) noexcept
	{
		std::cout << "Updating element: " << element
			      << " at: " << index << '\n';
		const int64 array_size = static_cast<int64>(_array.size());
		while (index < array_size)
		{
			this->_array[index] += element;
			index = index + (index & -index);
		}
	}

	//@todo: bug needs to be fixed
	void emplace(Type element) noexcept
	{
		// element += prefixSum(this->size() - 1);
		_array.emplace_back(element);
		// this->insert_at(element, this->size());
		std::cout << "\nem-placing... "<< element << "\n";
	}

	// returns the prefix sum of given index
	Type prefixSum(int64 index) const noexcept
	{
		Type sum = 0;
		while (index > 0)
		{
			sum += this->_array[index];
			index = index - (index & -index);
		}
		return sum;
	}

	// return the range sum of the given range
	Type rangeSum(int64 from, int64 to) const noexcept
	{
		return  this->prefixSum(to) - this->prefixSum(from - 1);
	}

	// get the original element by range summing
	Type element_at(int64 index) const noexcept
	{
		return this->rangeSum(index, index);
	}

	// o-stream operator overload for convenience printing
	friend std::ostream& operator<< <>(
		std::ostream& out, const FenwickTree &obj) noexcept;
};

template<typename Type>
std::ostream& operator<< (std::ostream& out,
	const FenwickTree<Type, only_for_integrals<Type>> &obj) noexcept
{
	using int64 = typename FenwickTree<Type, only_for_integrals<Type>>::int64;
	out << "\n\nReading Original Array: index from 1 to size().......\n";

	for (int64 i = 1, n = (int64)obj.size(); i <= n; ++i)
		out << obj.element_at(i) << " ";
	return out << '\n';
}

/*************** test function(s) to be called in the main() *****************/
template<typename Type> void testFenwickTree(
	const std::initializer_list<Type> list = { 1, 2, 3, 4, 5 })
{
	FenwickTree<Type> obj{ list };

	//if constexpr (std::is_same_v<int, Type>)
		//obj.emplace(static_cast<Type>(6));

	std::cout << obj;
}

JEJO_END

#endif // FENWICK_TREE_T_HPP

/*****************************************************************************/
