#ifndef IP_FILTER_UTILITIES_H
#define IP_FILTER_UTILITIES_H

#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <ipaddr/IpV4.h>

namespace otus_hw_2 {

	struct Utilities {

	public:

		struct HomeworkProcessor {

			explicit HomeworkProcessor(std::vector<otus_hw_2::IpV4> ipPool) : _ipPool(std::move(ipPool))
			{ }

			std::vector<otus_hw_2::IpV4> _ipPool;

		public:

			static constexpr uint8_t HomeworkFirstByte = 46;
			static constexpr uint8_t HomeworkSecondByte = 70;
			static constexpr uint8_t HomeworkAnyByte = 46;

		public:

			void DoReverseLexicographySort();
			void PrintSorted();
			void PrintAddressesWithPresetFirstAndSecondByte(uint8_t firstByte, uint8_t secondByte);
			void PrintAddressesWithAnyByteEqualsGiven(uint8_t givenByte);


		};

	public:

		static std::string ParseInputString(const std::string &givenStr);


	};
}
#endif //IP_FILTER_UTILITIES_H
