// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <regex>

#include "StringConv.h"
#include "DnsServerData.h"
#include "tins/tins.h"


using namespace std;
using namespace Tins;

const vector<string>* CheckArgs(const int& argc, const wchar_t* const* const argv)
{
	wregex ip4(L"^((25[0-5]|(2[0-4]|1[0-9]|[1-9]|)[0-9])(\.(?!$)|$)){4}$");
	wregex txtfile(L"^(?i:.*)\.txt$");
	vector<string>* dnsName = new vector<string>;

	if (argc == 0)
	{
		throw exception("No user arguments.");
	}
	else if (argc != 2)
	{	//Program name first argument.
		throw exception("Invalid Number of Arguments");
	}
	else if (regex_match(argv[1], ip4))
	{
		wcout << "Single Argument." << endl;
		dnsName->emplace_back(WcharToString(argv[1]));
		return dnsName;
	}
	else if (regex_match(argv[1], txtfile))
	{
		wcout << "Multiple Arguments" << endl;
		return ReadDNS(argv[1]);
	}
}

void ShuffleIndex(const vector<uint32_t>* indexes)
{
	shuffle(indexes->begin(), indexes->end(), mt19937{ random_device{}() });
}

const vector<uint32_t>* GenArrRandomAccess(const uint32_t size)
{
	vector<uint32_t>* randomIndex =  new vector<uint32_t>;
	for (size_t i = 0; i < size; i++)
	{
		randomIndex->emplace_back(i);
	}
	ShuffleIndex(randomIndex);
	return randomIndex;
}




//Add the 255 ANY to the DNS-Type Enum.
int main(const int argc, const char * const * const argv)
{
	try
	{
		//const vector<string> destServer = CheckArgs(argc, argv);			//sender
		//const vector<string> recServer = AllDNS_ServersAsString();			//receiver
		//vector<uint32_t> recIndex = GenArrRandomAccess(recServer.size());	//random access
		//vector<uint32_t> destIndex = GenArrRandomAccess(destServer.size());	//random access

		//EthernetII eth;
		//IP* ip = new IP();
		//UDP* udp = new UDP();
		//DNS* dns = new DNS();

		//PacketSender sender;
		//IP pkt = IP("ADDRESS") / UDP(443, 443) / DNS();
		//pkt.rfind_pdu<DNS>().add_query({"www.google.com", DNS::ALL, DNS::IN });


		// The sender
		PacketSender sender;
		// The DNS request
		IP pkt = IP("8.8.8.8") / UDP(53, 1337) / DNS();
		// Add the query

		DNS::query qer;
		qer.dname("www.google.com");
		qer.query_class(DNS::ANY);
		qer.query_type(DNS::ALL);

		pkt.rfind_pdu<DNS>().add_query(qer);
		// We want the query to be resolverd recursively
		pkt.rfind_pdu<DNS>().recursion_desired(1);

		// Send and receive the response.
		std::unique_ptr<PDU> response(sender.send_recv(pkt));
		// Did we receive anything?
		if (response) {
			// Interpret the response
			DNS dns = response->rfind_pdu<RawPDU>().to<DNS>();
			// Print responses
			for (const auto& record : dns.answers()) {
				cout << record.dname() << " - " << record.data() << endl;
			}
		}
	}
	catch (const exception e)
	{
		wcout << "Error: " << e.what() << endl;
	} 
}
