#ifndef IP_FILTER_IPADDRESS_H
#define IP_FILTER_IPADDRESS_H

#include <cstdint>
#include <array>
#include <stdexcept>

#include <ipaddr/IIpAddress.h>

namespace otus_hw_2 {

	class IpV4 : public virtual IIpAddress {

		//Continue here
		const std::array<uint8_t, 4> _bytes_representation;

	public:

		IpV4(std::string address) {

			auto expectedIp = address.substr(0, address.find(" "));

			if (expectedIp.empty()) {
				throw std::invalid_argument("String [" + address + "] can not be converted to IPV4");
			}


		}

	public:

		IpVersion GetVersion() override { return IpVersion::V4; }
		std::string ToString() override { return ""; }





	};

} // otus_hw_2

#endif //IP_FILTER_IPADDRESS_H
