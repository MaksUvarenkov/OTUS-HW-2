#include <iostream>
#include <versioning/ProjectVersion.h>
#include <util/Utilities.h>
#include <spdlog/spdlog.h>

int main() {

	spdlog::info("Hello, I am OTUS-HW-2!");
	spdlog::info("Version is: [{}]", to_string(otus_hw_2::ProjectVersion::GetVersion()));

	try {

		std::vector<std::vector<std::string> > ip_pool;

		for(std::string line; std::getline(std::cin, line);)
		{
			auto expectedIpV4 = otus_hw_2::Utilities::ParseInputString(line);

		}

	}
	catch (const std::exception& what) {

	}


	return 0;
}
