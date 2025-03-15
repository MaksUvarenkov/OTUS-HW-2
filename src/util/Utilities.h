#ifndef IP_FILTER_UTILITIES_H
#define IP_FILTER_UTILITIES_H

#include <ipaddr/IpV4.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace otus_hw_2 {

	struct Utilities {

	public:
		struct HomeworkProcessor {

			explicit HomeworkProcessor(std::vector<otus_hw_2::IpV4> ipPool) : _ipPool(std::move(ipPool)) {}

			std::vector<otus_hw_2::IpV4> _ipPool;

		public:
			static constexpr uint8_t HomeworkFirstByteTheOnly = 1;
			static constexpr uint8_t HomeworkFirstByte = 46;
			static constexpr uint8_t HomeworkSecondByte = 70;
			static constexpr uint8_t HomeworkAnyByte = 46;

		public:
			void DoReverseLexicographySort();
			void PrintSorted();
			void PrintAddressesWithFirstByteEqualsGiven(uint8_t firstByte);
			void PrintAddressesWithPresetFirstAndSecondByteEqualsGiven(uint8_t firstByte, uint8_t secondByte);
			void PrintAddressesWithAnyByteEqualsGiven(uint8_t givenByte);
		};

	public:
		static std::string ParseInputString(const std::string &givenStr);
	};
}// namespace otus_hw_2
#endif//IP_FILTER_UTILITIES_H
