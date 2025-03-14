#ifndef IP_FILTER_IIPADDRESS_H
#define IP_FILTER_IIPADDRESS_H

#include <string>

enum class IpVersion {

	V4 = 0,
	V6 = 1

};

struct IIpAddress {

public:

	virtual IpVersion GetVersion() const = 0;
	virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetDigitRepresentation() const = 0;

	virtual bool operator <(const IIpAddress& another) = 0;
	virtual bool operator >(const IIpAddress& another) = 0;


};




#endif //IP_FILTER_IIPADDRESS_H
