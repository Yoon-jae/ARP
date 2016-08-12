#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"

class CARPLayer
	: public CBaseLayer
{
private:
	inline void		ResetHeader( );


	// Cache table data structure


public:
	CARPLayer( char* pName );
	virtual ~CARPLayer();

	void SetSrcIPAddress(unsigned char* src_ip);
	void SetDstIPAddress(unsigned char* dst_ip);
	void SetEnetSrcAddress(unsigned char* pAddress);
	void SetEnetDstAddress(unsigned char* pAddress);
	void SetOption(unsigned int arp_option);

	unsigned char* GetSrcIPAddress();
	unsigned char* GetDstIPAddress();
	unsigned char* GetEnetSrcAddress();
	unsigned char* GetEnetDstAddress();
	unsigned int GetOption();

	BOOL Send(unsigned char* ppayload, int nlength);
	BOOL Receive(unsigned char* ppayload);

	typedef struct _ETHERNET_ADDR
	{
		union {
			struct { unsigned char e0, e1, e2, e3, e4, e5; } s_un_byte;
			unsigned char s_ether_addr[6];
		} S_un;

		#define addr0 S_un.s_un_byte.e0
		#define addr1 S_un.s_un_byte.e1
		#define addr2 S_un.s_un_byte.e2
		#define addr3 S_un.s_un_byte.e3
		#define addr4 S_un.s_un_byte.e4
		#define addr5 S_un.s_un_byte.e5

		#define addrs  S_un.s_ether_addr

	} ETHERNET_ADDR, *LPETHERNET_ADDR;

	typedef struct _IP_ADDR
	{
		union {
			struct { unsigned char e0, e1, e2, e3; } s_un_byte;
			unsigned char s_ether_addr[4];
		} S_un;

		#define addr0 S_un.s_un_byte.e0
		#define addr1 S_un.s_un_byte.e1
		#define addr2 S_un.s_un_byte.e2
		#define addr3 S_un.s_un_byte.e3

		#define addrs  S_un.s_ether_addr

	} IP_ADDR, *LPIP_ADDR;


	typedef struct _ARPLayer_HEADER {
		unsigned short arp_hardType;
		unsigned short arp_protocolType;
		unsigned char arp_hardLength;
		unsigned char arp_protocolLength;
		unsigned short arp_option;
		ETHERNET_ADDR arp_srcHardAddress;
		IP_ADDR arp_srcProtocolAddress;
		ETHERNET_ADDR arp_dstHardAddress;
		IP_ADDR arp_dstProtocolAddress;
	} ARPLayer_HEADER, *PARPLayer_HEADER;

protected:
	ARPLayer_HEADER m_sHeader;
};