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
		std::array<uint8_t, 4> _bytes_representation{};
		std::string _string_repr;

	private:

		static bool IsNumber(const std::string& str);
		static bool IsValidIPv4(const std::string& ip);

	public:

		explicit IpV4(const std::string& expectedIp);

	public:

		IpVersion GetVersion() override { return IpVersion::V4; }
		std::string ToString() override { return _string_repr; }

	};

} // otus_hw_2

#endif //IP_FILTER_IPADDRESS_H
