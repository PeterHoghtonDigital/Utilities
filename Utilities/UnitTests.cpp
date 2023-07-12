#include "UnitTests.h"

#include <iostream>

#include "UnitTestDynamicArray.h"
#include "UnitTestStaticArray.h"

namespace UnitTests
{
	void Run()
	{
		UnitTestStaticArray();
		UnitTestDynamicArray();

		std::cout << "All tests passed!" << std::endl;
	}
}