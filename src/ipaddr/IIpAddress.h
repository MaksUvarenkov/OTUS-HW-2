#ifndef IP_FILTER_IIPADDRESS_H
#define IP_FILTER_IIPADDRESS_H

#include <string>

enum class IpVersion {

	V4 = 0,
	V6 = 1

};

struct IIpAddress {

public:

	virtual IpVersion GetVersion() = 0;
	virtual std::string ToString() = 0;

	virtual bool operator <(const IIpAddress& another);
	virtual bool operator =(const IIpAddress& another);


};




#endif //IP_FILTER_IIPADDRESS_H
