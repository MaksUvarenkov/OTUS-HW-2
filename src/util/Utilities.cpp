#include "Utilities.h"
#include "spdlog/spdlog.h"

#include <utility>
#include <algorithm>
#include <iostream>

namespace otus_hw_2 {

	std::string Utilities::ParseInputString(const std::string &line) {

		std::istringstream iss(line);
		std::vector<std::string> parts;
		std::string part;

		while (std::getline(iss, part, '\t')) {
			parts.push_back(part);
		}

		if (parts.size() != 3) {
			throw std::runtime_error("Expected pattern 'text1 \\t text2 \\t text3' unmatched.");
		}

		for (const auto &p: parts) {
			if (p.empty()) {
				throw std::runtime_error("Expected pattern 'text1 \\t text2 \\t text3' unmatched.");
			}
		}

		return parts[0];
	}

	void Utilities::HomeworkProcessor::DoReverseLexicographySort() {

		std::sort(_ipPool.begin(), _ipPool.end(), std::greater<>());

	}

	void Utilities::HomeworkProcessor::PrintSorted() {
		for (const auto &ip: _ipPool) {
			std::cout << ip << std::endl;
		}
	}

	void
	Utilities::HomeworkProcessor::PrintAddressesWithPresetFirstAndSecondByteEqualsGiven(uint8_t firstByte, uint8_t secondByte) {

		for (const auto &ip: _ipPool) {

			auto firstByteOfAddr = ip.GetByteOfAddress(IpV4::ByteNumber::FIRST);
			auto secondByteOfAddr = ip.GetByteOfAddress(IpV4::ByteNumber::SECOND);

			if (firstByteOfAddr == firstByte && secondByteOfAddr == secondByte)
				std::cout << ip << std::endl;
		}

	}

	void Utilities::HomeworkProcessor::PrintAddressesWithAnyByteEqualsGiven(uint8_t givenByte) {

		for (const auto &ip: _ipPool) {

			if (ip.AnyByteEqualsGiven(givenByte))
				std::cout << ip << std::endl;
		}

	}

	void Utilities::HomeworkProcessor::PrintAddressesWithFirstByteEqualsGiven(uint8_t firstByte) {

		for (const auto &ip: _ipPool) {

			if (ip.GetByteOfAddress(IpV4::ByteNumber::FIRST) == firstByte)
				std::cout << ip << std::endl;
		}

	}
} // otus_hw_2