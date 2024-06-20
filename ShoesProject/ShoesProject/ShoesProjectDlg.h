
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

struct ImageSetting
{
	// Dung de dieu chinh pixel
	float alpha = 1.0; //contrast
	int beta = 0; //brightness
	int sizeofKernel = 1; // blur

	// Dung de affine
	CPoint translate = CPoint(0.0 , 0.0);
	float zoom_level = 1.0;
	float rotateAngle = 0.0;

	// Dung de luu tru thong so
	CPoint translateD = CPoint(0.0, 0.0);
	float rotateAngleD = 0.0;
};

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
	afx_msg void OnNMCustomdrawSliDempixel(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_file_dir1;
	CListBox m_list_file1;
	CString m_folder1;
	CListBox m_list_folder1;
	CString m_FolderPath;
	Mat m_original_img1;
	ImageSetting imgSetting;
	BOOL on_Translate = false;
	BOOL on_Rotate = false;
	CStatic* m_CtrlImage;
	CPoint m_mouseUP, m_mouseDOWN, m_mouseMOVE;
	BOOL PreTranslateMessage(MSG* pMSG);
	CRect m_ClientRectImage;
	CSliderCtrl m_slider_dempixelsang;
	void translateImage(Mat& image, int dx, int dy);
	void zoomImage(Mat& image, float zoomLevel);
	void rotateImage(Mat& image, float angle);
	void setImage(CStatic*& picturbox, Mat& image);
	void saveTranslate();
	void saveRotater();
	//void saveZoom();
	void applyTransition(CStatic*& picturebox, Mat& image, ImageSetting imgsetting);
	void moveImage();
	void rotate();
	void zoom(float z);
	float calRotateImage(CPoint pt1, CPoint pt2);
	int demSoLuongPixelSang(BYTE* pData8BitsIn, int width, int height, int threshold);
};

