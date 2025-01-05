#ifndef IP_FILTER_UTILITIES_H
#define IP_FILTER_UTILITIES_H

#include <vector>
#include <string>
#include <sstream>

namespace otus_hw_2 {

	struct Utilities {

	public:

		static std::vector<std::string> SplitString(const std::string &givenStr, char delimiter) {

			std::vector<std::string> result;
			std::stringstream ss(givenStr);
			std::string item;

			while (getline(ss, item, delimiter)) {
				result.push_back(item);
			}

			return result;

		}


	};

} // otus_hw_2

#endif //IP_FILTER_UTILITIES_H
