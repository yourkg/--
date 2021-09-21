// Demo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo1.h"
#include "Demo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg dialog

CDemo1Dlg::CDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemo1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemo1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDB_BTN_PROCESS, OnBtnProcess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg message handlers

BOOL CDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemo1Dlg::OnPaint() 
{
	CPaintDC dc(this); 

	m_dib.Draw(&dc,CPoint(0,0),CSize(m_dib.GetDimensions()));

	CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemo1Dlg::OnBtnLoad() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Bitmap Files(*.bmp)|*.bmp|",NULL);
	
	if(dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();
		CFile file;
		if( !file.Open( strFilePath, CFile::modeRead) )
		{
			file.Close();
			return ;
		}
		m_dib.Read(&file);
	
		file.Close();
		Invalidate();
	}
	
}

void CDemo1Dlg::OnBtnSave() 
{
	CString strSavePath;
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Bitmap Files(*.bmp)|*.bmp|",NULL);
	
	if(dlg.DoModal() == IDOK)
	{
		strSavePath = dlg.GetPathName();
		strSavePath+=".bmp";
		CFile file;
		file.Open(strSavePath,CFile::modeCreate|CFile::modeWrite);
		m_dib.Write(&file);
		file.Close();
	}
}


void CDemo1Dlg::OnBtnProcess() 
{
	CSize size = m_dib.GetDimensions();
	int nWidth = size.cx;
	int nHeight = size.cy;
	//图像坐标原点位于左下角，X正向向右，Y正向向上
	//m_dib.m_lpImage 为图像的左下角第一个像素的指针。
	//图像格式为灰度图像,灰度值0～255。
	int kg=0;
	for(int i=0;i<nHeight;i++){
		
		for(int j=0;j<nWidth;j++){
			
			if(*(m_dib.m_lpImage+i*nWidth+j)==0&&kg==0){

				for(int x=0;x<nWidth;x++){
					*(m_dib.m_lpImage+i*nWidth+x)=255;
					int hh=0;
					for(int oo=i;oo<nHeight;oo++){
						if(*(m_dib.m_lpImage+oo*nWidth+x)==0){
							hh++;
						}
					}
					if(hh==0){
						for(int oo=i;oo<nHeight;oo++){
						*(m_dib.m_lpImage+oo*nWidth+x)=255;
						int mm=0;
						for(int pp=j;pp<nWidth;pp++){
							if(*(m_dib.m_lpImage+oo*nWidth+pp)==0)mm++;				
						}
						if(mm==0){
							for(int pp=j;pp<nWidth;pp++){
							*(m_dib.m_lpImage+oo*nWidth+pp)=255;				
						}
						}
					}
					}
				}
				kg=1;
			}
			
			
		
		}
	}
	Invalidate();
}
