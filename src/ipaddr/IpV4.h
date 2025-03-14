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
		std::array<uint8_t, 4> _bytesRepresentation{};
		uint32_t _digitRepresentation;
		std::string _stringRepresentation;

	public:

		[[nodiscard]] uint32_t GetDigitRepresentation() const override;

	private:

		static bool IsNumber(const std::string& str);
		static bool IsValidIPv4(const std::string& ip);

	public:

		explicit IpV4(const std::string& expectedIp);

	public:

		[[nodiscard]] IpVersion GetVersion() const override { return IpVersion::V4; }
		[[nodiscard]] std::string ToString() const override { return _stringRepresentation; }

	public:

		bool operator <(const IIpAddress& another) override;
		bool operator >(const IIpAddress& another) override;

		friend std::ostream& operator<<(std::ostream& os, const IpV4& obj);

	};

} // otus_hw_2

#endif //IP_FILTER_IPADDRESS_H
