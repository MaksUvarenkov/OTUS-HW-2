#include <iostream>
#include <versioning/ProjectVersion.h>
#include <ipaddr/IpV4.h>
#include <util/Utilities.h>
#include <spdlog/spdlog.h>

int main() {

	spdlog::set_level(spdlog::level::err);

	spdlog::info("Hello, I am OTUS-HW-2!");
	spdlog::info("Version is: [{}]", to_string(otus_hw_2::ProjectVersion::GetVersion()));

	try {

		std::vector<otus_hw_2::IpV4> ip_pool;

		for(std::string line; std::getline(std::cin, line);)
		{
			try {
				auto expectedIpV4 = otus_hw_2::Utilities::ParseInputString(line);
				ip_pool.emplace_back(expectedIpV4);
			}
			catch (const std::exception &ex) {
				spdlog::error("Can not transform given string to IPV4. String: [{}]", line);
			}
		}

		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>());

		for (const auto &ip : ip_pool ){

			std::cout << ip << std::endl;

		}

	}
	catch (const std::exception &ex) {
		spdlog::error("Failed to process given input. Closing. Due to: [{}]", ex.what());
	}


	return 0;
}
