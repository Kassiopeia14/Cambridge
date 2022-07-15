#include <iostream>

#include "../modSHA256Generator/SHA256Generator.h"

int main()
{
	SHA256Generator sha256Generator;

	std::cout << sha256Generator.generate("Hello, World!") << std::endl;

	return 0;
}