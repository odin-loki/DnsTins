// DnsServerData.h : This file contains the 'DnsServerData' function prototypes and libs.
//

#pragma once

#include <array>
#include <string>
#include <vector>

using namespace std;

///IPV4 root DNS Namespace servers. https://www.iana.org/domains/root/servers
class RootDNS_ip4
{
public:
	RootDNS_ip4();
	~RootDNS_ip4();

	const array<string, 13> GetData(void);
private:
	array<string, 13> rootDNS_ip4;
};

///IPV6 root DNS Namespace servers. https://www.iana.org/domains/root/servers
class RootDNS_ip6
{
public:
	RootDNS_ip6();
	~RootDNS_ip6();

	const array<string, 13> GetData(void);
private:
	array<string, 13> rootDNS_ip6;
};

///IPV4 Public DNS Namespace servers. https://public-dns.info/nameservers-all.txt
class PublicDNS_ip4
{
public:
	PublicDNS_ip4();
	~PublicDNS_ip4();

	const array<string, 19606>* GetData(void);
private:
	array<string, 19606>* publicDNS_ip4;
};

///IPV6 Public DNS Namespace servers. https://public-dns.info/nameservers-all.txt
class PublicDNS_ip6
{
public:
	PublicDNS_ip6();
	~PublicDNS_ip6();

	const array<string, 186>* GetData(void);
private:
	array<string, 186>* publicDNS_ip6;
};

///Returns a list of all ip4 DNS Servers as strings.
const vector<string>* AllDNS_ServersAsString(void);

///Returns a list of DNS servers read from file.
const vector<string>* ReadDNS(wstring filename);
