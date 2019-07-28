// C++ header
#include <string>

// data-structure headers
#include "ListFrontT.hpp"
#include "ListT.hpp"

int main()
{
#if 1 // Test : class ListFrontT<>
	JeJo::testListFront({ 2, 3, 5, 8, 10 }); // template class
#endif

#if 1 // Test : class ListT<>
	std::cout << "\n<------------------ class ListT<> test ------------------>\n";
	JeJo::testList();
#endif

	return 0;
}
