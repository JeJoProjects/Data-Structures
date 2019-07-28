// C++ header
#include <string>

// data-structure headers
#include "BinarySearchTreeT.hpp"
#include "FenwickTreeT.hpp"

int main()
{
#if 0 // Test : class BinarySearchTreeT<>
	std::cout << "<------------------- class BinarySearchTreeT<> test ------------------->\n";
	JeJo::BinarySearchTree<int> bst{};
	bst.insert(1);
	bst.insert(-5);
	bst.insert(111);
	bst.insert(113);
	bst.insert(114);
	bst.insert(110);
	bst.insert(112);
	bst.insert(112);
	bst.insert(-5);
	bst.insert(0);
	std::cout << bst;
#endif

#if 1 // Test : class FenwickTreeT<>
	std::cout << "\n<-------------- class FenwickTreeT<> test -------------->\n";
	JeJo::testFenwickTree({ 1, 2, 7, 8 });
#endif
	return 0;
}
