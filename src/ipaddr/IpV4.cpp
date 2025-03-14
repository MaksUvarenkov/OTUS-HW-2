#include <algorithm>
#include <ipaddr/IpV4.h>

#include <vector>
#include <sstream>

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

	IpV4::IpV4(const std::string &expectedIp) : _stringRepresentation(expectedIp) {

		if (!IsValidIPv4(expectedIp)) {
			throw std::runtime_error("String can not be convertible to IPV4 format.");
		}

		std::vector<std::string> parts;
		std::string part;
		std::istringstream iss(expectedIp);

		auto pos = 0;
		while (std::getline(iss, part, '.')) {
			parts.push_back(part);
			_bytesRepresentation[pos++] = std::stoi(part);
			_digitRepresentation = (_digitRepresentation << 8) | static_cast<uint8_t>(std::stoi(part));
		}
	}

	bool IpV4::operator<(const IIpAddress &another) {

		return _digitRepresentation < another.GetDigitRepresentation();
	}

	bool IpV4::operator>(const IIpAddress &another) {

		return _digitRepresentation > another.GetDigitRepresentation();

	}

	uint32_t IpV4::GetDigitRepresentation() const {
		return _digitRepresentation;
	}

	std::ostream &operator<<(std::ostream &os, const IpV4 &obj) {
		return os << obj._stringRepresentation;
	}

	bool IpV4::AnyByteEqualsGiven(uint8_t given) const {

		return std::ranges::any_of(_bytesRepresentation, [given](int byte) {
			return byte == given;
		});

	}

} // otus_hw_2