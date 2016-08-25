
// ARPDlg.h : 헤더 파일
//

#if !defined(AFX_ARPDLG_H__FE9C37CB_4C90_4772_99AD_50A9B24BCE62__INCLUDED_)
#define AFX_ARPDLG_H__FE9C37CB_4C90_4772_99AD_50A9B24BCE62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LayerManager.h"
#include "TCPLayer.h"
#include "IPLayer.h"
#include "ARPLayer.h"
#include "EthernetLayer.h"
#include "NILayer.h"


// CARPDlg 대화 상자
class CARPDlg 
: public CDialogEx,
  public CBaseLayer
{
// 생성입니다.
public:
	CARPDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ARP_DIALOG };

	/* About ARPDlg */

	// My Device
	CComboBox		mCombo_MyDev;
	CString			mEdit_MyEther;
	CIPAddressCtrl	mIP_MyIP;

	// ARP Cache Table
	CListCtrl		mList_ARPCacheTable;
	CIPAddressCtrl	mIP_ARPDSTIP;

	// Proxy ARP Entry
	CListCtrl		mList_PARPEntry;

	// Gratuituos ARP
	CString			mEdit_GARPEther;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()

private:
	CLayerManager	m_LayerMgr;

	enum {			ARP_INITIALIZING,
					ARP_OPERATING,
					ARP_ENDPROCESSING,
					ARP_DEVICE } ;

	void			SetDlgState( int state );
	inline void		EndofProcess( );
	unsigned char* CARPDlg::MacAddrToHexInt(CString ether);

// Object Layer
	CARPLayer*			m_ARP;
	CEthernetLayer*		m_Ether;
	CNILayer*			m_NI;
	CIPLayer*			m_IP;
	CTCPLayer*			m_TCP;

// Implementation
	UINT			m_wParam;
	DWORD			m_lParam;
public:
	afx_msg void OnBnClickedMydevSelect();
	afx_msg void OnBnClickedArpRequest();
	afx_msg void OnCbnSelchangeMydevList();

	void			CacheTableUpdate();

};

#endif // !defined(AFX_ARPDLG_H__FE9C37CB_4C90_4772_99AD_50A9B24BCE62__INCLUDED_)