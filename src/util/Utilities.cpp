#include "Utilities.h"

namespace otus_hw_2 {

	std::string Utilities::ParseInputString(const std::string& line) {

		std::istringstream iss(line);
		std::vector<std::string> parts;
		std::string part;

		while (std::getline(iss, part, '\t')) {
			parts.push_back(part);
		}

		if (parts.size() != 3) {
			throw std::runtime_error("Expected pattern 'text1 \\t text2 \\t text3' unmatched.");
		}

		for (const auto& p : parts) {
			if (p.empty()) {
				throw std::runtime_error("Expected pattern 'text1 \\t text2 \\t text3' unmatched.");
			}
		}

		return parts[0];
	}

} // otus_hw_2