
// ShoesProjectDlg.h : header file
//

#pragma once
#include <iostream>
#include "framework.h"
#include "ShoesProjectDlg.h"
#include "afxdialogex.h"
#include <cstring>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <string>
#include "FolderDlg.h"
#include "SupportFunctions.h"

using namespace std;
using namespace cv;


// CShoesProjectDlg dialog
class CShoesProjectDlg : public CDialogEx
{
// Construction
public:
	CShoesProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOESPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBrowser();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList1();
	CEdit m_file_dir1;
	CListBox m_list_file1;
	CString m_folder1;
	CListBox m_list_folder1;
	CString m_FolderPath;
	Mat m_original_img1;
};

