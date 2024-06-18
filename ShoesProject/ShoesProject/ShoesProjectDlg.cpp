
// ShoesProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "ShoesProject.h"
#include "ShoesProjectDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShoesProjectDlg dialog



CShoesProjectDlg::CShoesProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOESPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShoesProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSE_FOLDER, m_file_dir1);
	DDX_Control(pDX, IDC_LIST1,  m_list_folder1);
	DDX_Control(pDX, IDC_LIST2, m_list_file1);
}

BEGIN_MESSAGE_MAP(CShoesProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CShoesProjectDlg::OnBnClickedBtnBrowser)
	ON_LBN_SELCHANGE(IDC_LIST2, &CShoesProjectDlg::OnLbnSelchangeList2)
	ON_LBN_SELCHANGE(IDC_LIST1, &CShoesProjectDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()

// CShoesProjectDlg message handlers

BOOL CShoesProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShoesProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShoesProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShoesProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShoesProjectDlg::OnBnClickedBtnBrowser()
{
	LPCTSTR lpszTitle = _T("");
	UINT	uFlags = BIF_RETURNONLYFSDIRS;// | BIF_USENEWUI;
	CFolderDialog	dlg(lpszTitle, m_FolderPath, this, uFlags);

	if (dlg.DoModal() == IDOK)
	{
		m_FolderPath = dlg.GetFolderPath();
		SetDlgItemText(IDC_BROWSE_FOLDER, m_FolderPath);
		CStringArray listFolderPath;

		GetFolderLists(m_FolderPath, listFolderPath, false, false, false);
		for (int i = 0; i < listFolderPath.GetSize(); i++)
		{
			m_list_folder1.AddString(listFolderPath[i]);
		}
	}

}

void CShoesProjectDlg::OnLbnSelchangeList1()
{
	int indexSelected = m_list_folder1.GetCurSel();
	if (indexSelected == -1) return;
	CString FolderSelected;
	m_list_folder1.GetText(indexSelected, FolderSelected);

	/// <summary>
	/// lay danh sach cac anh trong folder va them vao list file
	/// </summary>
	string folderPath = CStringToString(FolderSelected);
	vector <CString> listImagePath;
	GetImageLists(m_FolderPath + "\\" + FolderSelected, listImagePath);
	m_list_file1.ResetContent();
	for (int i = 0; i < listImagePath.size(); i++)
	{
		if (listImagePath[i] == "." || listImagePath[i] == "..") continue;
		m_list_file1.AddString(listImagePath[i]);
	}
}

void CShoesProjectDlg::OnLbnSelchangeList2()
{
	//Lay file duoc chon
	int indexFile = m_list_file1.GetCurSel();
	CString fileSelected;
	m_list_file1.GetText(indexFile, fileSelected);

	// Tim duong dan truc tiep toi file duoc chon
	int indexSelected = m_list_folder1.GetCurSel();
	CString FolderSelected;
	m_list_folder1.GetText(indexSelected, FolderSelected);

	CString path2Image;
	path2Image = m_FolderPath + "\\" + FolderSelected + "\\" + fileSelected;
	// Load anh len 
	m_original_img1 = imread(CStringToString(path2Image));
	if (m_original_img1.data == nullptr)return;
	// View image
	CImage cimage;
	Mat2CImage(m_original_img1, cimage);
	CStatic* picturebox = (CStatic*)(GetDlgItem(IDC_PICCTRL1));
	displayImage(picturebox, cimage);

}