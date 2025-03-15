#include <iostream>
#include <ipaddr/IpV4.h>
#include <spdlog/spdlog.h>
#include <util/Utilities.h>
#include <versioning/ProjectVersion.h>

using namespace otus_hw_2;

int main() {

	spdlog::set_level(spdlog::level::err);
	spdlog::info("Hello, I am OTUS-HW-2!");
	spdlog::info("Version is: [{}]", to_string(ProjectVersion::GetVersion()));

	try {

		std::vector<IpV4> ip_pool;

		for (std::string line; std::getline(std::cin, line);) {
			try {
				auto expectedIpV4 = Utilities::ParseInputString(line);
				ip_pool.emplace_back(expectedIpV4);
			} catch (const std::exception &ex) {
				spdlog::error("Can not transform given string to IPV4. String: [{}]", line);
			}
		}

		Utilities::HomeworkProcessor processor(ip_pool);

		processor.DoReverseLexicographySort();
		processor.PrintSorted();
		processor.PrintAddressesWithFirstByteEqualsGiven(Utilities::HomeworkProcessor::HomeworkFirstByteTheOnly);
		processor.PrintAddressesWithPresetFirstAndSecondByteEqualsGiven(Utilities::HomeworkProcessor::HomeworkFirstByte,
																		Utilities::HomeworkProcessor::HomeworkSecondByte);
		processor.PrintAddressesWithAnyByteEqualsGiven(Utilities::HomeworkProcessor::HomeworkAnyByte);

	} catch (const std::exception &ex) {
		spdlog::error("Failed to process given input. Closing. Due to: [{}]", ex.what());
	}

	return 0;
}
