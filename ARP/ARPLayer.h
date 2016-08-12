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

	BOOL Send(unsigned char* ppayload, int nlength);
	BOOL Receive(unsigned char* ppayload);

	typedef struct _ARPLayer_HEADER {
		unsigned short arp_hardType;
		unsigned short arp_protocol;
		unsigned char arp_hardLength;
		unsigned char arp_protocolLength;
		unsigned short arp_option;
		unsigned int arp_srcHardAddress;
		unsigned int arp_srcProtocolAddress;
		unsigned int arp_dstHardAddress;
		unsigned int arp_dstHardProtocolAddress;
	} ARPLayer_HEADER, *PARPLayer_HEADER;

protected:
	ARPLayer_HEADER m_sHeader;
};