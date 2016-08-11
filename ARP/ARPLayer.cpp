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

}

BOOL Send(unsigned char* ppayload, int nlength)
{
	return true;
}

BOOL Receive(unsigned char* ppayload)
{
	return false;
}
