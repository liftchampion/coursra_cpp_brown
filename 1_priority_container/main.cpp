#include <iostream>
#include "profile.h"
#include "test_runner.h"

int main()
{
	LOG_DURATION("gg")
	ASSERT_EQUAL(1,1)
	ASSERT_EQUAL(12,12)
	std::cout << "Hello, World!" << std::endl;
	return 0;
}