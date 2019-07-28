// C++ header
#include <string>

// data-structure headers
#include "BinarySearchTreeT.hpp"
#include "FenwickTree_FunctionalT.hpp"
#include "FenwickTreeT.hpp"
#include "ListFront_FunctionalT.hpp"
#include "ListFrontT.hpp"
#include "ListT.hpp"
#include "Matrix2DT.hpp"

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

#if 1 // Test : functional FenwickTreeT<>
	std::cout << "\n<----------- functional FenwickTreeT<> test --------------->\n";
	JeJo::testFenwickTree_testFunction({ 1,8,9,-7,-2,-4,5,0,-8,-1,-7 });
#endif

#if 1 // Test : class FenwickTreeT<>
	std::cout << "\n<-------------- class FenwickTreeT<> test -------------->\n";
	JeJo::testFenwickTree({ 1, 2, 7, 8 });
#endif

#if 1 // Test : functional ListFrontT<>
	std::cout << "\n<------------- functional ListFrontT<> test ------------->\n";
	JeJo::testListFront_function({ 2, 3, 5, 8, 10 }); // template function
#endif

#if 1 // Test : class ListFrontT<>
	JeJo::testListFront({ 2, 3, 5, 8, 10 }); // template class
#endif

#if 1 // Test : class ListT<>
	std::cout << "\n<------------------ class ListT<> test ------------------>\n";
	JeJo::testList();
#endif

#if 1 // Test : class Matrix2DT<>
	std::cout << "\n<---------------- class Matrix2DT<> test ---------------->\n";
	Matrix2D<int> mat{ 2, 2 };
	mat.emplace_row(1, 2);
	mat.emplace_row(3, 4);
	std::cout << mat;
#endif

	return 0;
}
