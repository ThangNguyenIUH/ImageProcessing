#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "FolderDlg.h"

using namespace std;
using namespace cv;


void GetImageLists(CString path2Folder, vector<CString>& listImagePath);
void GetFolderLists(CString strDir, CStringArray& arrOut, BOOL fullPath, BOOL addRoot, BOOL isRescue);
std::string CStringToString(const CString& cString);
void Mat2CImage(const Mat& srcImage, CImage& img);
void displayImage(CStatic* picturebox, CImage& image);
