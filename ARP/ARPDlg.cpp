
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
	ON_WM_TIMER()
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
	m_LayerMgr.AddLayer(new CEthernetLayer("Ethernet"));
	m_LayerMgr.AddLayer(new CNILayer("NI"));

	// m_LayerMgr.ConnectLayers("NI ( *Ethernet ( *ARP ( +IP ( *TCP ( *ARPDlg ) ) ) -IP ) )"); 
	// m_LayerMgr.ConnectLayers("NI ( *Ethernet ( *ARP ( +IP ( *TCP ( *ARPDlg ) ) ) -IP ( *TCP ( *ARPDlg ) ) ) )");

	m_TCP = (CTCPLayer *)m_LayerMgr.GetLayer("TCP");
	m_IP = (CIPLayer *)m_LayerMgr.GetLayer("IP");
	m_ARP = (CARPLayer *)m_LayerMgr.GetLayer("ARP");
	m_Ether = (CEthernetLayer *)m_LayerMgr.GetLayer("Ethernet");
	m_NI = (CNILayer *)m_LayerMgr.GetLayer("NI");

	this->SetUnderLayer(m_TCP);
	m_TCP->SetUnderLayer(m_IP);
	m_IP->SetUnderLayer(m_ARP);
	m_ARP->SetUnderLayer(m_Ether);
	m_Ether->SetUnderLayer(m_NI);

	m_NI->SetUpperLayer(m_Ether);
	m_Ether->SetUpperLayer(m_IP);
	m_Ether->SetUpperLayer(m_ARP);
	m_IP->SetUpperLayer(m_TCP);
	m_TCP->SetUpperLayer(this);
}

void CARPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// Control과 변수를 이어주는 작업
	
	// My Device
	DDX_Control(pDX, IDC_MYDEV_LIST, mCombo_MyDev);
	DDX_Text(pDX, IDC_MYDEV_ETHERNET, mEdit_MyEther);
	DDX_Control(pDX, IDC_MYDEV_IP, mIP_MyIP);

	// ARP Cache Table
	DDX_Control(pDX, IDC_ARP_CACHE_TABLE, mList_ARPCacheTable);
	DDX_Control(pDX, IDC_ARP_DSTIP, mIP_ARPDSTIP);

	// Proxy ARP Entry
	DDX_Control(pDX, IDC_PARP_ENTRY, mList_PARPEntry);

	// Gratuituos ARP
	DDX_Text(pDX, IDC_GARP_ETHERNET, mEdit_GARPEther);
}

BEGIN_MESSAGE_MAP(CARPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MYDEV_SELECT, &CARPDlg::OnBnClickedMydevSelect)
	ON_BN_CLICKED(IDC_ARP_REQUEST, &CARPDlg::OnBnClickedArpRequest)
	ON_CBN_SELCHANGE(IDC_MYDEV_LIST, &CARPDlg::OnCbnSelchangeMydevList)
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
	SetDlgState(ARP_INITIALIZING);
	SetDlgState(ARP_DEVICE);
	
	// List Control에 3가지 Column 추가
	// Arp Cache Table
	((CListCtrl*)GetDlgItem(IDC_ARP_CACHE_TABLE))->InsertColumn(0,"IP Address",LVCFMT_LEFT,180);
	((CListCtrl*)GetDlgItem(IDC_ARP_CACHE_TABLE))->InsertColumn(1,"Ethernet Address",LVCFMT_LEFT,180);
	((CListCtrl*)GetDlgItem(IDC_ARP_CACHE_TABLE))->InsertColumn(2,"Timer",LVCFMT_LEFT,50);
	((CListCtrl*)GetDlgItem(IDC_ARP_CACHE_TABLE))->InsertColumn(3,"Status",LVCFMT_LEFT,130);

	// Proxy Cache Table
	((CListCtrl*)GetDlgItem(IDC_PARP_ENTRY))->InsertColumn(0,"Device",LVCFMT_LEFT,180);
	((CListCtrl*)GetDlgItem(IDC_PARP_ENTRY))->InsertColumn(1,"IP Address",LVCFMT_LEFT,180);
	((CListCtrl*)GetDlgItem(IDC_PARP_ENTRY))->InsertColumn(2,"Ethernet Address",LVCFMT_LEFT,180);


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

	CButton*	pGARP_RequestButton = (CButton*) GetDlgItem(IDC_GARP_REQUEST);

	CEdit*		pGARP_EtherEdit = (CEdit*) GetDlgItem(IDC_GARP_ETHERNET);
	CEdit*		pMYDEV_EtherEdit = (CEdit*) GetDlgItem(IDC_MYDEV_ETHERNET);

	CComboBox*	pMYDEV_EtherComboBox = (CComboBox*) GetDlgItem(IDC_MYDEV_LIST);

	CIPAddressCtrl* pMYDEV_IPAddrCtrl = (CIPAddressCtrl*) GetDlgItem(IDC_MYDEV_IP);
	CIPAddressCtrl* pARP_IPAddrCtrl = (CIPAddressCtrl*) GetDlgItem(IDC_ARP_DSTIP);

	switch(state)
	{
	case ARP_INITIALIZING:
		pARP_ItemDeleteButton->EnableWindow(FALSE);
		pARP_AllDeleteButton->EnableWindow(FALSE);
		pARP_RequestButton->EnableWindow(FALSE);
		pPARP_AddButton->EnableWindow(FALSE);
		pPARP_DeleteButton->EnableWindow(FALSE);
		pGARP_RequestButton->EnableWindow(FALSE);
		break;

	case ARP_OPERATING:
		pARP_ItemDeleteButton->EnableWindow(TRUE);
		pARP_AllDeleteButton->EnableWindow(TRUE);
		pARP_RequestButton->EnableWindow(TRUE);
		pPARP_AddButton->EnableWindow(TRUE);
		pPARP_DeleteButton->EnableWindow(TRUE);
		pGARP_RequestButton->EnableWindow(TRUE);

		pGARP_EtherEdit->EnableWindow(TRUE);
		pARP_IPAddrCtrl->EnableWindow(TRUE);

		pMYDEV_EtherComboBox->EnableWindow(FALSE);
		pMYDEV_IPAddrCtrl->EnableWindow(FALSE);
		pMYDEV_SelectButton->EnableWindow(FALSE);

		break;

	case ARP_ENDPROCESSING:
		break;

	case ARP_DEVICE:
		for(int i=0; i<NI_COUNT_NIC; i++) {
			if(!m_NI->GetAdapterObject(i))
				break;
			device_description = m_NI->GetAdapterObject(i)->description;
			device_description.Trim();
			pMYDEV_EtherComboBox->AddString(device_description);
		}

		pMYDEV_EtherComboBox->SetCurSel(0);
		CString macAddr = m_NI->GetAdapterObject(0)->name;

		mEdit_MyEther = m_NI->GetNICardAddress((char *)macAddr.GetString());
		break;
	}
}

/* My Device Select 버튼 클릭시 */
void CARPDlg::OnBnClickedMydevSelect()
{
	UpdateData(TRUE);

	// 입력된 IP 주소를 저장
	unsigned char mydev_ip[4];
	mIP_MyIP.GetAddress(mydev_ip[0],mydev_ip[1],mydev_ip[2],mydev_ip[3]);

	// 설정된 IP, MAC(16진수로 변환하여) 주소를 ARP Header에 설정.
	m_IP->SetSrcIPAddress(mydev_ip);
	m_ARP->SetEnetSrcAddress(MacAddrToHexInt(mEdit_MyEther));
	m_ARP->SetSrcIPAddress(mydev_ip);
	m_Ether->SetEnetSrcAddress(MacAddrToHexInt(mEdit_MyEther));


	// 선택한 NICard로 Adapter 등록
	int nIndex = mCombo_MyDev.GetCurSel();
	m_NI->SetAdapterNumber(nIndex);

	m_NI->PacketStartDriver();

	// Dialog 상태 변경
	SetDlgState(ARP_OPERATING);

	UpdateData(FALSE);
}

unsigned char* CARPDlg::MacAddrToHexInt(CString ether)
{
	CString noColStr;
	unsigned char *arp_ether = (u_char *)malloc(sizeof(u_char)*6);

	for(int i=0; i<6; i++) {
		// ":"으로 구분되어진 MAC 주소를 Substring하여, 1Byte씩 배열에 넣어 줌
		AfxExtractSubString(noColStr,ether,i,':');
		// 받아온 MAC 주소를 16진수로 변환시켜줌
		arp_ether[i] = (unsigned char)strtoul(noColStr.GetString(),NULL,16);
	}
	arp_ether[6] = '\0';

	return arp_ether;
}

/* ARP Request 버튼 클릭시 */
void CARPDlg::OnBnClickedArpRequest()
{
	UpdateData(TRUE);

	// 입력된 목적지 주소를 IP Header에 저장
	unsigned char dst_ip[4];
	mIP_ARPDSTIP.GetAddress(dst_ip[0], dst_ip[1],dst_ip[2],dst_ip[3]);
	m_IP->SetDstIPAddress(dst_ip);
	m_ARP->SetDstIPAddress(dst_ip);

	// UnderLayer Send
	BOOL bSuccess = FALSE ;

	unsigned char a = '0';
	bSuccess = mp_UnderLayer->Send(&a,1);


	// Dialog cache table update
	if(bSuccess) {

	} else {

	}


	// Change dialog setting 

	

	UpdateData(FALSE);
}


void CARPDlg::OnCbnSelchangeMydevList()
{
	UpdateData ( TRUE );

	// 찾은 Device List를 ComboBox에 저장
	CComboBox*	pMY_EtherComboBox = (CComboBox*)GetDlgItem(IDC_MYDEV_LIST);
	
	// ComboBox에서 선택된 Item으로 NIC의 Adapter 이름을 가져옴
	int sIndex = pMY_EtherComboBox->GetCurSel();
	CString nicName = m_NI->GetAdapterObject(sIndex)->name;
	
	// Adapter 이름으로 Mac Address를 가져옴
	mEdit_MyEther = m_NI->GetNICardAddress((char *)nicName.GetString());

	UpdateData ( FALSE );
}

void CARPDlg::OnTimer(UINT nIDEvent)
{

}

void CARPDlg::CacheTableUpdate()
{
	mList_ARPCacheTable.DeleteAllItems();

	int length = m_ARP->arp_table.size();
	for(int i=0; i<length; i++)
	{
		LV_ITEM lvItem;
		lvItem.iItem = mList_ARPCacheTable.GetItemCount();
		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 0;

		int time = get<2>(m_ARP->arp_table[i]);
		if(time > 0) {

			unsigned char* currentIP = get<1>(m_ARP->arp_table[i]);
			CString ip;
			ip.Format("%d.%d.%d.%d", currentIP,currentIP+1,currentIP+2,currentIP+3);
			mList_ARPCacheTable.SetItemText(lvItem.iItem, 0, (LPSTR)(LPCTSTR)ip);


			unsigned char* currentMAC = get<0>(m_ARP->arp_table[i]);
			CString mac;
			mac.Format("%d:%d:%d:%d:%d:%d",currentMAC,currentMAC+1,currentMAC+2
										,currentMAC+3,currentMAC+4,currentMAC+5);
			mList_ARPCacheTable.SetItemText(lvItem.iItem, 1, (LPSTR)(LPCTSTR)mac);


			CString timer;
			timer.Format("%d",time);
			mList_ARPCacheTable.SetItemText(lvItem.iItem, 2, (LPSTR)(LPCTSTR)timer);

			CString status; 
			status.Format("%s",get<3>(m_ARP->arp_table[i])? "complete":"incomplete");
			mList_ARPCacheTable.SetItemText(lvItem.iItem, 3, (LPSTR)(LPCTSTR)status);

		} else {
			m_ARP->arp_table.erase(m_ARP->arp_table.begin() + i);
			continue;
		}

		// 1초 줄이기
		get<2>(m_ARP->arp_table[i]) -= 1;
	}
}