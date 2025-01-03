#include <iostream>
#include <versioning/ProjectVersion.h>

int main() {

	std::cout << "Hello, I am OTUS-HW-2!" << std::endl;
	std::cout << "Version is: " << otus_hw_2::ProjectVersion::GetVersion() << std::endl;
	return 0;

}
