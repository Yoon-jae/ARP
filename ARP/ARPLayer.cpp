#include "stdafx.h"
#include "ARP.h"
#include "ARPLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CARPLayer::CARPLayer( char* pName)
: CBaseLayer( pName )
{
	ResetHeader();
}

CARPLayer::~CARPLayer()
{
}

void CARPLayer::ResetHeader()
{
	m_sHeader.arp_hardType = 0x0000;
	m_sHeader.arp_protocolType = 0x0000;
	m_sHeader.arp_hardLength = 0x00;
	m_sHeader.arp_protocolLength = 0x00;
	m_sHeader.arp_option = 0x0000;
	memset(m_sHeader.arp_srcHardAddress.addrs, 0, 6);
	memset(m_sHeader.arp_srcProtocolAddress.addrs, 0, 4);
	memset(m_sHeader.arp_dstHardAddress.addrs, 0, 6);
	memset(m_sHeader.arp_dstProtocolAddress.addrs, 0, 4);
}

BOOL CARPLayer::Send(unsigned char* ppayload, int nlength)
{
	return true;
}

BOOL CARPLayer::Receive(unsigned char* ppayload)
{
	return false;
}

void CARPLayer::SetEnetSrcAddress(unsigned char *pAddress)
{
	memcpy(&m_sHeader.arp_srcHardAddress.addrs, pAddress, 6);
}

void CARPLayer::SetEnetDstAddress(unsigned char *pAddress)
{
	memcpy(&m_sHeader.arp_dstHardAddress.addrs, pAddress, 6);
}

void CARPLayer::SetSrcIPAddress(unsigned char* src_ip)
{
	memcpy(m_sHeader.arp_srcProtocolAddress.addrs, src_ip, 4);
}

void CARPLayer::SetDstIPAddress(unsigned char* dst_ip)
{
	memcpy(m_sHeader.arp_dstProtocolAddress.addrs, dst_ip, 4);
}

void CARPLayer::SetOption(unsigned int arp_option)
{
	m_sHeader.arp_option = arp_option;
}

unsigned char* CARPLayer::GetEnetSrcAddress()
{
	return m_sHeader.arp_srcHardAddress.addrs;
}

unsigned char* CARPLayer::GetEnetDstAddress()
{
	return m_sHeader.arp_dstHardAddress.addrs;
}

unsigned char* CARPLayer::GetSrcIPAddress()
{
	return m_sHeader.arp_srcProtocolAddress.addrs;
}

unsigned char* CARPLayer::GetDstIPAddress()
{
	return m_sHeader.arp_dstProtocolAddress.addrs;
}

unsigned int CARPLayer::GetOption()
{
	return m_sHeader.arp_option;
}