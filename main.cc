// C++ header
#include <string>

// data-structure headers
#include "ListFront_FunctionalT.hpp"
#include "ListFrontT.hpp"
#include "ListT.hpp"
#include "Matrix2DT.hpp"

int main()
{
#if 0 // Test : functional ListFrontT<>
	std::cout << "\n<------------- functional ListFrontT<> test ------------->\n";
	JeJo::testListFront_function({ 2, 3, 5, 8, 10 }); // template function
#endif

#if 0 // Test : class ListFrontT<>
	JeJo::testListFront({ 2, 3, 5, 8, 10 }); // template class
#endif

#if 0 // Test : class ListT<>
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
