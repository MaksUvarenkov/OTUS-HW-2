#include <gtest/gtest.h>

#include <iomanip>
#include <iostream>
#include <openssl/md5.h>// Для MD5
#include <sstream>

#include "spdlog/spdlog.h"
#include <fstream>
#include <ipaddr/IpV4.h>
#include <tests/TestData.h>
#include <util/Utilities.h>


std::string CalculateMD5(const std::string &input) {
	unsigned char digest[ MD5_DIGEST_LENGTH ];
	MD5((unsigned char *) input.c_str(), input.size(), digest);

	std::stringstream ss;
	for (unsigned char i: digest) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int) i;
	}
	return ss.str();
}


TEST(MyProjectTest, BasicTest) {
	EXPECT_EQ(1 + 1, 2);
}

TEST(CinTest, ReadInputFromFile) {

	std::streambuf *origCin = std::cin.rdbuf();

	std::ofstream testFile("test_input.txt");
	testFile << GTests::TestData::TestInput;
	testFile.close();

	std::ifstream testStream("test_input.txt");

	std::cin.rdbuf(testStream.rdbuf());

	std::vector<otus_hw_2::IpV4> ip_pool;

	for (std::string line; std::getline(std::cin, line);) {
		try {
			auto expectedIpV4 = otus_hw_2::Utilities::ParseInputString(line);
			ip_pool.emplace_back(expectedIpV4);
		} catch (const std::exception &ex) {
			spdlog::error("Can not transform given string to IPV4. String: [{}]", line);
		}
	}

	std::cin.rdbuf(origCin);

	std::remove("test_input.txt");

	testing::internal::CaptureStdout();

	otus_hw_2::Utilities::HomeworkProcessor processor(ip_pool);

	processor.DoReverseLexicographySort();
	processor.PrintSorted();
	processor.PrintAddressesWithFirstByteEqualsGiven(otus_hw_2::Utilities::HomeworkProcessor::HomeworkFirstByteTheOnly);
	processor.PrintAddressesWithPresetFirstAndSecondByteEqualsGiven(otus_hw_2::Utilities::HomeworkProcessor::HomeworkFirstByte,
																	otus_hw_2::Utilities::HomeworkProcessor::HomeworkSecondByte);
	processor.PrintAddressesWithAnyByteEqualsGiven(otus_hw_2::Utilities::HomeworkProcessor::HomeworkAnyByte);

	std::string output = testing::internal::GetCapturedStdout();

	std::string md5Hash = CalculateMD5(output);

	std::string expectedHash = "24e7a7b2270daee89c64d3ca5fb3da1a";

	EXPECT_EQ(md5Hash, expectedHash);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}