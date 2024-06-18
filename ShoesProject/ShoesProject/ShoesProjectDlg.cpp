
// ShoesProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ShoesProject.h"
#include "ShoesProjectDlg.h"
#include "afxdialogex.h"
#include <cstring>
#include <string>
#include <filesystem>


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
	DDX_Control(pDX, IDC_LIST1, m_list_file1);
	DDX_Control(pDX, IDC_LIST2, m_list_folder1);
}

BEGIN_MESSAGE_MAP(CShoesProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CShoesProjectDlg::OnBnClickedBtnBrowser)
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

void GetImageLists(CString path2Folder, vector<CString>& listImagePath) {
	// Neu khong phai la empty folder
	string path = CT2A(path2Folder);
	vector<string> listImgPath;

	if (PathIsDirectoryEmpty(path2Folder) == FALSE) {
		string pattern(path);
		pattern.append("\\*");
		WIN32_FIND_DATA data;
		HANDLE hFind;
		std::wstring wstr(pattern.begin(), pattern.end());
		if ((hFind = FindFirstFile(wstr.c_str(), &data)) != INVALID_HANDLE_VALUE)
		{
			do {
				int bufferSize = WideCharToMultiByte(CP_UTF8, 0, data.cFileName, -1, NULL, 0, NULL, NULL);
				// Tạo buffer để chứa chuỗi đã chuyển đổi
				std::string str_data(bufferSize, 0);
				// Thực hiện chuyển đổi
				WideCharToMultiByte(CP_UTF8, 0, data.cFileName, -1, &str_data[0], bufferSize, NULL, NULL);
				listImgPath.push_back(str_data);
			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
		for (const auto& cstr : listImgPath)
		{
			listImagePath.push_back(CString(cstr.c_str()));
		}
	}
	else {
		return;
	}
}

void GetFolderLists(CString strDir, CStringArray& arrOut, BOOL fullPath, BOOL addRoot, BOOL isRescue)
{
	BOOL success;
	CString tempFoldername;
	WIN32_FIND_DATA FindFileData;
	HANDLE  hFind;
	hFind = FindFirstFile(CString(strDir) + _T("\\*.*"), &FindFileData);

	if (addRoot)
		arrOut.Add(CString(strDir));

	do
	{
		success = FALSE;
		if (hFind != INVALID_HANDLE_VALUE)
		{
			tempFoldername = FindFileData.cFileName;
			if (tempFoldername.CompareNoCase(_T(".")) && tempFoldername.CompareNoCase(_T("..")))
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (!fullPath)
						arrOut.Add(tempFoldername);
					else
						arrOut.Add(CString(strDir) + '\\' + tempFoldername);

					if (isRescue)
					{
						CString strFullPathDir;
						strFullPathDir.Format(_T("%s\\%s"), strDir, tempFoldername.GetBuffer(0));
						GetFolderLists(strFullPathDir.GetBuffer(0), arrOut, fullPath, FALSE, TRUE);
					}
				}
			success = FindNextFile(hFind, &FindFileData);//tim ket thuc 	
		}

	} while (success);

	FindClose(hFind);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShoesProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShoesProjectDlg::OnBnClickedBtnBrowser()
{
	//CFolderPickerDialog folderPicker;
	//folderPicker.m_ofn.lpstrInitialDir = _T("D:\ImageTest");
	//if (folderPicker.DoModal() == IDOK)
	//{
	//	m_folder1 = folderPicker.GetPathName();
	//	m_file_dir1.SetWindowText(m_folder1);
	//	vector <CString> listPath;
	//	GetImageLists(m_folder1, listPath);
	//	for (int i = 0; i < listPath.size(); i++)
	//	{
	//		m_list_file1.AddString(listPath[i]);
	//	}
	//}

	LPCTSTR lpszTitle = _T("");
	UINT	uFlags = BIF_RETURNONLYFSDIRS;// | BIF_USENEWUI;
	CFolderDialog	dlg(lpszTitle, m_FolderPath, this, uFlags);

	if (dlg.DoModal() == IDOK)
	{
		m_FolderPath = dlg.GetFolderPath();
		SetDlgItemText(IDC_BROWSE_FOLDER, m_FolderPath);
		CStringArray listPath;

		GetFolderLists(m_FolderPath, listPath, false, false, false);
		for (int i = 0; i < listPath.GetSize(); i++)
		{
			m_list_file1.AddString(listPath[i]);
		}
	}
}
