
// ChangePictures.h : ChangePictures 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CChangePicturesApp:
// 有关此类的实现，请参阅 ChangePictures.cpp
//

class CChangePicturesApp : public CWinApp
{
public:
	CChangePicturesApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
public:
	afx_msg void OnAppAbout();
//	afx_msg void OnMMX();
//	afx_msg void OnUMXX();
	DECLARE_MESSAGE_MAP()
};

extern CChangePicturesApp theApp;
