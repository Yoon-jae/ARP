
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#if !defined(AFX_STDAFX_H__119ECB1B_6E70_4662_A2A9_A20B5201CA81__INCLUDED_)
#define AFX_STDAFX_H__119ECB1B_6E70_4662_A2A9_A20B5201CA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//{{AFX_INSERT_LOCATION}}

#define MAX_LAYER_NUMBER		0xff

#define ETHER_MAX_SIZE			1514
#define ETHER_HEADER_SIZE		14
#define ETHER_MAX_DATA_SIZE		( ETHER_MAX_SIZE - ETHER_HEADER_SIZE )
#define ETHER_PROTO_TYPE_IP		0x0800
#define ETHER_PROTO_TYPE_ARP	0x0806
#define ETHER_PROTO_TYPE_RARP	0x0835

#define TCP_HEADER_SIZE			( sizeof(unsigned int) * 2 +				\
								  sizeof(unsigned short) * 5 +					\
								  sizeof(unsigned char) * 6 )
#define TCP_DATA_SIZE			( ETHER_MAX_SIZE - ( TCP_HEADER_SIZE +  IP_HEADER_SIZE + \
																		ETHER_HEADER_SIZE ) )

#define IP_HEADER_SIZE			( sizeof(unsigned short) * 4 +					\
								  sizeof(unsigned char) * 12  )
#define IP_DATA_SIZE			( ETHER_MAX_SIZE - ( IP_HEADER_SIZE  + \
														ETHER_HEADER_SIZE ))

#define APP_HEADER_SIZE			( sizeof(unsigned short) +					\
								  sizeof(unsigned char)  +				\
								  sizeof(unsigned long) )
#define APP_DATA_SIZE 			( ETHER_MAX_DATA_SIZE - ( APP_HEADER_SIZE +		\
												          TCP_HEADER_SIZE +		\
												          IP_HEADER_SIZE ) )

#define ARP_HARDTYPE			0x0001	// Ethernet frame
#define ARP_PROTOTYPE_IP		0x0800
#define ARP_PROTOTYPE_ARP		0x0806
#define ARP_PROTOTYPE_RARP		0x0835
#define ARP_OPCODE_REQUEST		0x0001
#define ARP_OPCODE_REPLY		0x0002
#define ARP_HEADER_SIZE			28

#define NI_COUNT_NIC	10

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

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#endif // !defined(AFX_STDAFX_H__119ECB1B_6E70_4662_A2A9_A20B5201CA81__INCLUDED_)
