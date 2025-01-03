#include <iostream>
#include <versioning/ProjectVersion.h>
#include <spdlog/spdlog.h>

int main() {

	spdlog::info("Hello, I am OTUS-HW-2!");
	spdlog::info("Version is: [{}]", to_string(otus_hw_2::ProjectVersion::GetVersion()));

	try {

	}
	catch (const std::exception& what) {

	}


	return 0;
}
