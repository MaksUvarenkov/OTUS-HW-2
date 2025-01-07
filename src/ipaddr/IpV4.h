#ifndef IP_FILTER_IPADDRESS_H
#define IP_FILTER_IPADDRESS_H

#include <cstdint>
#include <array>
#include <stdexcept>
#include <charconv>

#include <ipaddr/IIpAddress.h>
#include <util/Utilities.h>

namespace otus_hw_2 {

	class IpV4 : public virtual IIpAddress {

		//Continue here
		std::array<uint8_t, 4> _bytes_representation;
		std::string _string_repr;

	public:

//		Expected pattern "192.168.100.100 something another ..."
		IpV4(std::string address) {

			auto expectedIp = address.substr(0, address.find(" "));

			if (expectedIp.empty()) {
				throw std::invalid_argument("String [" + address + "] can not be converted to IPV4.");
			}

			auto ipString = Utilities::SplitString(expectedIp, '.');
			if (ipString.size() != 4) {
				throw std::invalid_argument("String [" + address + "] can not be converted to IPV4. Check pattern.");
			}

			auto byteIter = _bytes_representation.begin();
			for (auto byteRepr: ipString) {

				auto [ptr, ec] = std::from_chars(byteRepr.data(), byteRepr.data() + byteRepr.size(), *byteIter);
				if (ec == std::errc{}) {
					throw std::invalid_argument("String [" + address + "] can not be converted to IPV4. Check pattern.");
				}
				++byteIter;

				_string_repr += byteRepr;
				if (byteRepr != *(ipString.end() - 1)) {
					_string_repr += ".";
				}
			}
		}

	public:

		IpVersion GetVersion() override { return IpVersion::V4; }
		std::string ToString() override { return _string_repr; }

	};

} // otus_hw_2

#endif //IP_FILTER_IPADDRESS_H
