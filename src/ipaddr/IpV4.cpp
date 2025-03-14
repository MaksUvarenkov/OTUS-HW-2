#include <algorithm>
#include "IpV4.h"

namespace otus_hw_2 {

	bool IpV4::IsNumber(const std::string& str) {
		return !str.empty() && std::all_of(str.begin(), str.end(), [](char ch) {
			return std::isdigit(ch);
		});
	}

	bool IpV4::IsValidIPv4(const std::string& ip) {
		std::vector<std::string> parts;
		std::string part;
		std::istringstream iss(ip);

		while (std::getline(iss, part, '.')) {
			parts.push_back(part);
		}

		if (parts.size() != 4) {
			return false;
		}

		return std::ranges::all_of(parts, [](const std::string& part){

			if (!IsNumber(part)) {
				return false;
			}

			if (part.size() > 1 && part[0] == '0') {
				return false;
			}

			int num = std::stoi(part);
			if (num < 0 || num > 255) {
				return false;
			}
			return true;

		});
	}

	IpV4::IpV4(const std::string &expectedIp) : _string_repr(expectedIp) {

		if (!IsValidIPv4(expectedIp)) {
			throw std::runtime_error("String can not be convertible to IPV4 format.");
		}

		std::vector<std::string> parts;
		std::string part;
		std::istringstream iss(expectedIp);

		auto locator = _bytes_representation.begin();
		while (std::getline(iss, part, '.')) {
			parts.push_back(part);
			*locator = std::stoi(part);
		}
	}

} // otus_hw_2