// C++ header
#include <string>

// data-structure headers
#include "ListFront_FunctionalT.hpp"
#include "ListFrontT.hpp"
#include "ListT.hpp"

int main()
{
#if 1 // Test : functional ListFrontT<>
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

	return 0;
}
