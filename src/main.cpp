#include <iostream>
#include <versioning/ProjectVersion.h>
#include <spdlog/spdlog.h>

int main() {

	spdlog::info("Hello, I am OTUS-HW-2!");
	spdlog::info("Version is: [{}]", to_string(otus_hw_2::ProjectVersion::GetVersion()));

	try {

		std::vector<std::vector<std::string> > ip_pool;

		for(std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

	}
	catch (const std::exception& what) {

	}


	return 0;
}
