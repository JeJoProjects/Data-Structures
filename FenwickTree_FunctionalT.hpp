/******************************************************************************
 * Simple implementation of Fenwick Tree using template functions.
 *
 * @Authur :  JeJo
 * @Date   :  01 - 02 -2018
 * @license: free to use and distribute(no further support as well)
 *
 * 1: To update the Fenwick's Tree  : update()
 * 2: To find the prefix sum        : prefixSum()
 * 3: To find the range sum         : rangeSum()
 * 4: TO read original array from FT: readArray()
 *
 * @Note  : template typename(s) should be considered while passing
 *			by referencing the arguments.
 *****************************************************************************/

#ifndef FENWICK_TREE_FUNCTIONAL_T_HPP
#define FENWICK_TREE_FUNCTIONAL_T_HPP

// macros for name-spacing
#define JEJO_BEGIN namespace JeJo {
#define JEJO_END }

// C++ headers
#include <iostream>
#include <vector>               // std::vector<>
#include <cstddef>              // std::size_t
#include <initializer_list>     // std::initializer_list<>

JEJO_BEGIN

// convenience type(s)
using int64 = long long int;

// (template)alias to enable the following functions for integer and float types.
template<typename T>
using only_for_integrals = std::enable_if_t<std::is_arithmetic_v<T>, void>;

// 1: to update or create Fenwick Tree with O(n * log (n)) complexity
template<typename Type, only_for_integrals<Type>* = nullptr>
void update(std::vector<Type> &FenwickTree, const Type val, int64 index)
{
	std::cout << "Updating index at " << index << " element: " << val << '\n';
	const int64 treeSize = static_cast<int64>(FenwickTree.size());
	while (index < treeSize)
	{
		FenwickTree[index] += val;
		index = index + (index & -index);
	}
}

// 2: to find the prefix Sum
template<typename Type, only_for_integrals<Type>* = nullptr>
Type prefixSum(const std::vector<Type> &FenwickTree, int64 index)
{
	Type sum = 0;
	while (index > 0)
	{
		sum += FenwickTree[index];
		index = index - (index & -index);
	}
	return sum;
}

// 3: to get an range sum with an time-complexity of O(log (n))
template<typename Type, only_for_integrals<Type>* = nullptr>
Type rangeSum(const std::vector<Type> &FenwickTree, int64 from, int64 to)
{
	return  prefixSum(FenwickTree, to) - prefixSum(FenwickTree, from - 1);
}

// 4: to read each elements of original array from FT
template<typename Type>
Type readArray(const std::vector<Type> &FenwickTree, int64 &index)
{
	return rangeSum(FenwickTree, index, index);
}

/*************************** example test-function ***************************/
template<typename Type, only_for_integrals<Type>* = nullptr>
void testFenwickTree_testFunction(const std::initializer_list<Type> list)
{
	// Fenwick's index start from 1; i.e it has 0 + n elements
	std::vector<Type> fenTree(list.size() + 1);

	// updating tree...
	std::cout << "Updating tree.........................................\n";
	int64 index = 1;
	for (const Type &element : list) update(fenTree, element, index++);

	// prefix sum of each indexes(starting from 0 to size() - 1)....
	std::cout << "\n\nPrefix Sum: index starting from 0 to size() - 1......\n";
	for (int64 i = 0, n = (int64)list.size(); i <= n; ++i)
		std::cout << prefixSum(fenTree, i) << " ";

	// range sum of from index 0 to size() - 1....
	std::cout << "\n\nRange Sum: index 0 to size() - 1.....................\n";
	for (int64 i = 0, n = (int64)list.size(); i <= n; ++i)
		std::cout << rangeSum(fenTree, 0, i) << " ";

	// tree itself....
	std::cout << "\n\nTree-itself: index starting from 0 to size() - 1.....\n";
	for (const auto &it : fenTree)    std::cout << it << " ";

	// reading original array(from index 1 to size())....
	std::cout << "\n\nReading Original Array: index from 1 to size().......\n";
	for (int64 i = 1, n = (int64)list.size(); i <= n; ++i)
		std::cout << readArray(fenTree, i) << " ";

	std::cout << "\n\n";
}

JEJO_END

#endif // FENWICK_TREE_FUNCTIONAL_T_HPP

/*****************************************************************************/
