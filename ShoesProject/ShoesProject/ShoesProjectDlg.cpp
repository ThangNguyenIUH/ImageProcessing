
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

	GetDlgItem(IDC_PICCTRL1)->GetClientRect(&m_ClientRectImage);
	GetDlgItem(IDC_PICCTRL1)->ClientToScreen(&m_ClientRectImage);
	ScreenToClient(&m_ClientRectImage);

	m_CtrlImage = (CStatic*)(GetDlgItem(IDC_PICCTRL1));

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

BOOL CShoesProjectDlg::PreTranslateMessage(MSG* pMSG)
{
	if (pMSG->message == WM_MOUSEMOVE) {
		// Lay vi tri chuot dang di chuyen
		m_mouseMOVE = CPoint(GET_X_LPARAM(pMSG->lParam), GET_Y_LPARAM(pMSG->lParam));
		// Hien thi vi tri len dialog
		CString xy;
		xy.Format((CString)"(%d, %d)", m_mouseMOVE.x, m_mouseMOVE.y);
		SetDlgItemText(IDC_STATIC_XY, xy);

		// Neu nhu dang nhan chuot trai va new nhu chuot dang nam trong picture box
		if (m_ClientRectImage.PtInRect(m_mouseMOVE)) {
			if (on_Translate)
			{
				moveImage();
			}
			else if (on_Rotate) 
			{
				//UpdateData(1);
				rotate();
			}
		}
	}

	else if(pMSG->message == WM_LBUTTONUP){
		on_Translate = FALSE;
		m_mouseUP = CPoint(GET_X_LPARAM(pMSG->lParam), GET_Y_LPARAM(pMSG->lParam));
		saveTranslate();
	}

	else if (pMSG->message == WM_LBUTTONDOWN) {
		on_Translate = TRUE;
		m_mouseDOWN = CPoint(GET_X_LPARAM(pMSG->lParam), GET_Y_LPARAM(pMSG->lParam));
	}

	else if (pMSG->message == WM_RBUTTONDOWN) {
		on_Rotate = TRUE;
		m_mouseDOWN = CPoint(GET_X_LPARAM(pMSG->lParam), GET_Y_LPARAM(pMSG->lParam));
	}

	else if (pMSG->message == WM_RBUTTONUP) {
		on_Rotate = FALSE;
		m_mouseUP = CPoint(GET_X_LPARAM(pMSG->lParam), GET_Y_LPARAM(pMSG->lParam));
		saveRotater();
	}

	else if(pMSG->message == WM_MOUSEWHEEL)
	{
		float z = GET_WHEEL_DELTA_WPARAM(pMSG->wParam) / 100.0;
		if (z < 0)
		{
			z = max(0.01, z + 2.0);
		}
		if (m_ClientRectImage.PtInRect(m_mouseMOVE))
		{
			zoom(z);
		}
	}

	return FALSE;
}

void CShoesProjectDlg::translateImage(Mat& image, int dx, int dy)
{
	// image vua la input vua la output. Chinh sua truc tiep tren image
	// dx dy la do lech cua anh
	Mat translateMat = (Mat_<double>(2, 3) << 1, 0, dx, 0, 1, dy);
	warpAffine(image, image, translateMat, image.size());
}

void CShoesProjectDlg::zoomImage(Mat& image, float zoomLevel)
{
	int oriWidth = image.size().width; //lay width anh goc
	int oriHeight = image.size().height; // lay height anh goc
	resize(image, image, Size(), zoomLevel, zoomLevel, INTER_LINEAR); // ham resize

	//lay width height anh moi
	int newWidth = int(image.cols * 1.2);
	int newHeight = int(image.rows * 1.2);

	if (image.cols < oriWidth || image.rows < oriHeight)
	{
		newWidth = oriWidth;
		newHeight = oriHeight;
	}

	Mat background = Mat(newHeight, newWidth, CV_8UC3, Scalar(0, 0, 0));
	image.copyTo(background(cv::Rect((newWidth - image.cols) / 2, (newHeight - image.rows) / 2,
		image.cols, image.rows)));
	image = background;

	if (image.cols > oriWidth && image.rows > oriHeight)
	{
		const int offsetWidth = (image.cols - oriWidth) / 2;
		const int offsetHeight = (image.rows - oriHeight) / 2;
		const Rect roi(offsetWidth, offsetHeight, oriWidth, oriHeight);
		image = image(roi).clone();
	}
}

void CShoesProjectDlg::rotateImage(Mat& image, float angle)
{
	Point2f pt(image.cols / 2, image.rows / 2);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(image, image, r, Size(image.cols, image.rows));
}

void CShoesProjectDlg::setImage(CStatic*& picturbox, Mat& image)
{
	CRect rect;
	picturbox->GetClientRect(rect);
	CClientDC dc(picturbox);

	CImage cimage;
	Mat2CImage(image, cimage);

	CBitmap m_bitmap;
	m_bitmap.Attach(cimage.Detach());

	CDC memoryDC;
	memoryDC.CreateCompatibleDC(&dc);
	memoryDC.SelectObject(m_bitmap);

	BITMAP bmp;
	m_bitmap.GetBitmap(&bmp);
	dc.SetStretchBltMode(COLORONCOLOR);

	dc.StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memoryDC, 0, 0, bmp.bmWidth,
		bmp.bmHeight, SRCCOPY);
}

void CShoesProjectDlg::saveTranslate()
{
	imgSetting.translateD.x += m_mouseUP.x - m_mouseDOWN.x;
	imgSetting.translateD.y += m_mouseUP.y - m_mouseDOWN.y;
}

void CShoesProjectDlg::saveRotater()
{
	float a = calRotateImage(m_mouseDOWN, m_mouseUP);
	imgSetting.rotateAngleD += fmod(a, 360);
}

void CShoesProjectDlg::applyTransition(CStatic*& picturebox, Mat& image, ImageSetting imgsetting)
{
	if (!image.empty())
	{
		//Mat tmpMat = paddingImage(image.clone(), 1000, 1000);
		Mat tmpMat = image.clone();
		rotateImage(tmpMat, imgSetting.rotateAngle);

		if (imgSetting.zoom_level >= 1.0)
		{
			translateImage(tmpMat, imgSetting.translate.x, imgSetting.translate.y);
			zoomImage(tmpMat, imgSetting.zoom_level);
		}
		else
		{
			zoomImage(tmpMat, imgSetting.zoom_level);
			translateImage(tmpMat, imgSetting.translate.x, imgSetting.translate.y);
		}
		CImage cimage;
		Mat2CImage(tmpMat, cimage);
		displayImage(picturebox, cimage);
		tmpMat.release();
		UpdateData(0);
	}
}

void CShoesProjectDlg::moveImage()
{
	imgSetting.translate.x = m_mouseMOVE.x - m_mouseDOWN.x + imgSetting.translateD.x;
	imgSetting.translate.y = m_mouseMOVE.y - m_mouseDOWN.y + imgSetting.translateD.y;
	applyTransition(m_CtrlImage, m_original_img1, imgSetting);
}

void CShoesProjectDlg::rotate()
{
	float a = calRotateImage(m_mouseDOWN, m_mouseMOVE);
	imgSetting.rotateAngle = fmod(a + imgSetting.rotateAngleD, 360);
	applyTransition(m_CtrlImage, m_original_img1, imgSetting);
}

void CShoesProjectDlg::zoom(float z)
{
	imgSetting.zoom_level = max(0.5f, min(10.0f, imgSetting.zoom_level * z));
	applyTransition(m_CtrlImage, m_original_img1, imgSetting);
}

float CShoesProjectDlg::calRotateImage(CPoint pt1, CPoint pt2)
{
	float pStartX = pt1.x - (m_ClientRectImage.CenterPoint().x - imgSetting.translateD.x);
	float pStartY = pt2.y - (m_ClientRectImage.CenterPoint().y - imgSetting.translateD.y);
	float a1 = atan2(pStartY, pStartX);

	float pMoveX = pt2.x - (m_ClientRectImage.CenterPoint().x - imgSetting.translateD.x);
	float pMoveY = pt2.y - (m_ClientRectImage.CenterPoint().y - imgSetting.translateD.y);
	float a2 = atan2(pMoveY, pMoveX);

	float a = (a1 - a2) * 180.0 / 3.1416;
	return a;
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
