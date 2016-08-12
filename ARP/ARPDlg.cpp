
// ARPDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ARP.h"
#include "ARPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CARPDlg 대화 상자




CARPDlg::CARPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CARPDlg::IDD, pParent),
	CBaseLayer("ARPDlg")
{
	mEdit_GARPEther = _T("");
	mEdit_MyEther = _T("");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_LayerMgr.AddLayer(this);
	m_LayerMgr.AddLayer(new CTCPLayer("TCP"));
	m_LayerMgr.AddLayer(new CIPLayer("IP"));
	m_LayerMgr.AddLayer(new CARPLayer("ARP"));
	m_LayerMgr.AddLayer(new CEthernetLayer("ETHER"));
	m_LayerMgr.AddLayer(new CNILayer("NI"));

	m_LayerMgr.ConnectLayers("NI ( *Ethernet ( *ARP ( +IP ( *TCP ( *ARPDlg ) ) ) -IP ) )"); 

	m_TCP = (CTCPLayer *)m_LayerMgr.GetLayer("TCP");
	m_IP = (CIPLayer *)m_LayerMgr.GetLayer("IP");
	m_ARP = (CARPLayer *)m_LayerMgr.GetLayer("ARP");
	m_Ether = (CEthernetLayer *)m_LayerMgr.GetLayer("ETHER");
	m_NI = (CNILayer *)m_LayerMgr.GetLayer("NI");
	
}

void CARPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CARPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CARPDlg 메시지 처리기

BOOL CARPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CARPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CARPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CARPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CARPDlg::SetDlgState(int state)
{
	UpdateData( TRUE ) ;

	CString		device_description;

	CButton*	pMYDEV_SelectButton = (CButton*) GetDlgItem(IDC_MYDEV_SELECT);

	CButton*	pARP_ItemDeleteButton = (CButton*) GetDlgItem(IDC_ARP_ITEM_DELETE);
	CButton*	pARP_AllDeleteButton = (CButton*) GetDlgItem(IDC_ARP_ALL_DELETE);
	CButton*	pARP_RequestButton = (CButton*) GetDlgItem(IDC_ARP_REQUEST);

	CButton*	pPARP_AddButton = (CButton*) GetDlgItem(IDC_PARP_ADD);
	CButton*	pPARP_DeleteButton = (CButton*) GetDlgItem(IDC_PARP_DELETE);

	CButton*	pGARP_AddButton = (CButton*) GetDlgItem(IDC_GARP_REQUEST);

	CEdit*		pGARP_EtherEdit = (CEdit*) GetDlgItem(IDC_GARP_ETHERNET);
	CEdit*		pMYDEV_EtherEdit = (CEdit*) GetDlgItem(IDC_MYDEV_ETHERNET);

	CComboBox*	pMYDEV_EtherComboBox = (CComboBox*) GetDlgItem(IDC_MYDEV_LIST);

	CIPAddressCtrl* pMYDEV_IPAddrCtrl = (CIPAddressCtrl*) GetDlgItem(IDC_MYDEV_IP);
	CIPAddressCtrl* pARP_IPAddrCtrl = (CIPAddressCtrl*) GetDlgItem(IDC_ARP_DSTIP);

	switch(state)
	{
	case ARP_INITIALIZING:
		break;

	case ARP_OPERATING:
		break;

	case ARP_ENDPROCESSING:
		break;

	case ARP_DEVICE:
		break;
	}
}