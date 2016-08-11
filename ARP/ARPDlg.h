
// ARPDlg.h : ��� ����
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


// CARPDlg ��ȭ ����
class CARPDlg 
: public CDialogEx,
  public CBaseLayer
{
// �����Դϴ�.
public:
	CARPDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CLayerManager	m_LayerMgr;

	enum {			ARP_INITIALIZING,
					ARP_OPERATING,
					ARP_ENDPROCESSING,
					ARP_DEVICE } ;

	void			SetDlgState( int state );
	inline void		EndofProcess( );

// Object Layer
	CARPLayer*			m_ARP;
	CEthernetLayer*		m_Ether;
	CNILayer*			m_NI;
	CIPLayer*			m_IP;
	CTCPLayer*			m_TCP;

// Implementation
	UINT			m_wParam;
	DWORD			m_lParam;
};

#endif // !defined(AFX_ARPDLG_H__FE9C37CB_4C90_4772_99AD_50A9B24BCE62__INCLUDED_)