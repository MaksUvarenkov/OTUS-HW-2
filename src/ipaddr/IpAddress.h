#ifndef IP_FILTER_IPADDRESS_H
#define IP_FILTER_IPADDRESS_H


#include <cstdint>
#include <array>


namespace otus_hw_2 {

	class IpAddress {

		enum class Version {

			V4 = 0,
			V6 = 1

		};

		//Continue here
		const uint32_t ip_v4;

		const uint64_t ip_v6_low;
		const uint64_t ip_v6_high;




	};

} // otus_hw_2

#endif //IP_FILTER_IPADDRESS_H
